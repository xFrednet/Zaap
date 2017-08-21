#pragma once

#include "Za.h"

#include <thread>
#include <type_traits>

#pragma region Option Macros
#ifndef ZA_MEM_FIRST_ALLOC_SIZE
#	define ZA_MEM_FIRST_CHUNK_SIZE      (256 * 1024 * 1024) //256MB
#endif

#ifndef ZA_MEM_CHUNK_SIZE
#	define ZA_MEM_CHUNK_SIZE            (16 * 1024 * 1024) //16MB
#endif

#ifndef ZA_MEM_PAGE_LOCATION_COUNT
#	 define ZA_MEM_PAGE_LOCATION_COUNT  (64 - 1) // -1 for the NEXT pointer
#endif

#ifndef ZA_MEM_BLOCK_MIN_SPLIT_SIZE
#	define ZA_MEM_BLOCK_MIN_SPLIT_SIZE  16 // plus the size of the MEM_BLOCK_HEADER
#endif

#define ZA_MEM_DEBUG_PATTERN            0xee

#pragma endregion 

//TODO implement suggestScan
//TODO move m_AllocIndex back
//TODO align the allocation. maybe surely

namespace zaap
{
	class za_ptr_base;

	template <typename T>
	class za_ptr_;
}

namespace zaap { namespace system {

	// these types are the same as the ones mentioned in "Types.h"
	typedef unsigned char       mm_byte;
	typedef unsigned int        mm_uint;

	typedef enum ZAAP_API ZA_MEM_OBJECT_ORIGIN_ : short {
		ZA_MEM_OBJECT_ORIGIN_UNKNOWN     = 0,
		ZA_MEM_OBJECT_ORIGIN_MEMMGR      = 1
	} ZA_MEM_OBJECT_ORIGIN;

	typedef enum ZAAP_API ZA_MEM_BLOCK_STATE_ { //this is 4 bytes wide to keep/help with the memory alignment
		ZA_MEM_BLOCK_STATE_OCCUPIED = 0,
		ZA_MEM_BLOCK_STATE_FREE     = 1
	} ZA_MEM_BLOCK_STATE;

	/* //////////////////////////////////////////////////////////////////////////////// */
	// // ZA_MEM_LOCATION //
	/* //////////////////////////////////////////////////////////////////////////////// */
	typedef struct ZAAP_API ZA_MEM_LOCATION_ {
		union { //This has to be at the start of this struct
			ZA_MEM_LOCATION_* NEXT;
			void*             MEM_BLOCK;
		};

		short REFERENCE_COUNT;
		ZA_MEM_OBJECT_ORIGIN OBJECT_ORIGIN; //ZA_MEM_OBJECT_ORIGIN_MEMMGR or ZA_MEM_OBJECT_ORIGIN_UNKNOWN
	} ZA_MEM_LOCATION;

	/* //////////////////////////////////////////////////////////////////////////////// */
	// // ZA_MEM_PAGE //
	/* //////////////////////////////////////////////////////////////////////////////// */
	typedef struct ZAAP_API ZA_MEM_PAGE_ {
		ZA_MEM_LOCATION LOCATIONS[ZA_MEM_PAGE_LOCATION_COUNT];
		ZA_MEM_PAGE_*   NEXT;
		//TODO test performance with a PREV reference
	} ZA_MEM_PAGE;

	/* //////////////////////////////////////////////////////////////////////////////// */
	// // ZA_MEM_BLOCK_HEADER //
	/* //////////////////////////////////////////////////////////////////////////////// */
	// The header that is placed in front of 
	// allocated memory blocks.
	//
	// 32 BIT 
	//     => 4 bytes per pointer 
	//
	//  Bytes 
	//  0 0 0 0 0 0 0 0 0 1 1 1 1 1 1 1 1 1 1 2
	//  1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0
	// +-------+-------+-------+-------+-------+
	// | PREV  | NEXT  |  LOC  | SIZE  | STATE |
	// +-------+-------+-------+-------+-------+
	//
	// PREV          :: The pointer to the previous memory block.
	// NEXT          :: The pointer to the next memory block.
	// LOC->LOCATION :: The pointer to the location.
	// SIZE          :: The size of this memory block. (without the header)
	// STATE         :: The state of this memory block. (this is 4 bytes wide to keep the memory alignment)
	//
	typedef struct ZAAP_API ZA_MEM_BLOCK_HEADER_ {
		ZA_MEM_BLOCK_HEADER_* PREV;
		ZA_MEM_BLOCK_HEADER_* NEXT;
		ZA_MEM_LOCATION_*     LOCATION;
		size_t                SIZE;
		ZA_MEM_BLOCK_STATE    STATE; // ZA_MEM_BLOCK_STATE_OCCUPIED or ZA_MEM_BLOCK_STATE_FREE
	} ZA_MEM_BLOCK_HEADER;

	/* //////////////////////////////////////////////////////////////////////////////// */
	// // MemoryManager //
	/* //////////////////////////////////////////////////////////////////////////////// */
	class ZAAP_API MemoryManager
	{
	private:
		template <typename T>
		friend class za_ptr_;
	public:
		static MemoryManager& GetStaticInstance()
		{
			static MemoryManager instance;
			return instance;
		}
	private:
		mm_byte* m_AllocMem;
		mm_uint m_Size;

		//Location List
		ZA_MEM_PAGE*     m_PageList;
		ZA_MEM_LOCATION* m_FreeMemLocations;

		//This is the position the next allocation will start searching from
		ZA_MEM_BLOCK_HEADER* m_AllocHeader;

		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Initialization && Deconstruction //
		/* //////////////////////////////////////////////////////////////////////////////// */
	public:
		void* operator new(size_t sz);
		void operator delete(void* ptr);

		MemoryManager::MemoryManager();
		MemoryManager::~MemoryManager();
	
		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Actual memory allocation //
		/* //////////////////////////////////////////////////////////////////////////////// */
	private:
		bool allocMem(size_t chunkSize = ZA_MEM_FIRST_CHUNK_SIZE);
		bool allocMoreMem(size_t chunkSize = ZA_MEM_CHUNK_SIZE);
		void freeAllMem();

		void allocNewLocations();
		bool isPageUsed(ZA_MEM_PAGE* page) const;
		void freePage(ZA_MEM_PAGE* page);

		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Utilities //
		/* //////////////////////////////////////////////////////////////////////////////// */
	public:
		/**
		* \brief This method tests if the given pointer is inside the bounds of this MemoryManager
		* \param block The pointer that should be tested.
		* \return This returns whether the given pointer is inside or outside of the managed memory.
		*/
		inline bool contains(void* block) const;
		/**
		 * \brief This tries to find the ZA_MEM_BLOCK_HEADER for the given block
		 * \param block The block for the requested header.
		 * \return The found header or a nullptr.
		 */
		inline ZA_MEM_BLOCK_HEADER* getBlockHeader(void* block);
	private:
		/**
		 * \brief 
		 * This test if the given block can be split and will do this if it is possible.
		 * 
		 * Splitting:
		 *      H     = Header
		 *      BLOCK = the allocated memory.
		 *      FREE  = free memory that isn't used.
		 *
		 * case 1:
		 *      The block will be split if the leftover memory is large enough
		 *      to fit a ZA_MEM_BLOCK_HEADER with the minimal size of
		 *      ZA_MEM_BLOCK_MIN_SPLIT_SIZE.
		 *
		 *      +---+------------------+    +---+-------+---+------+
		 *      | H | BLOCK : FREE     | => | H | BLOCK | H | FREE |
		 *      +---+------------------+    +---+-------+---+------+
		 *      |<H>|<-MBS->|<--oMem-->|
		 *                  |<H>|<BMSZ>|
		 *
		 *      H    = ZA_MEM_BLOCK_HEADER, the header for the following memory block.
		 *      MBS  = minBlockSize, the minimal size of this block.
		 *      oMem = The memory that is over and can be used differently.
		 *      BMSZ = The minimal size of the split block (ZA_MEM_BLOCK_MIN_SPLIT_SIZE).
		 *
		 * case 2:
		 *      The block won't be split if the leftover memory is too small for
		 *      the ZA_MEM_BLOCK_HEADER and ZA_MEM_BLOCK_MIN_SPLIT_SIZE.
		 *
		 *      +---+--------------+    +---+--------------+
		 *      | H | BLOCK : FREE | => | H | BLOCK : FREE |
		 *      +---+--------------+    +---+--------------+
		 *      |<H>|<-MBS->|<oMem>|
		 *                  |<H>|<BMSZ>|
		 *
		 *      H    = ZA_MEM_BLOCK_HEADER, the header for the following memory block.
		 *      MBS  = minBlockSize, the minimal size of this block.
		 *      oMem = The memory that is over and can be used differently.
		 *      
		 *      |<H>|<BMSZ>| = are the minimal size of the for splitting. The free memory
		 *                     isn't large enough to fit them so the block isn't split.
		 *
		 * \param header The header that should be checked and split.
		 * \param minBlockSize The minimal size the header has to have after splitting.
		 */
		inline void split(ZA_MEM_BLOCK_HEADER* header, size_t minBlockSize);
		/**
		 * \brief Possibilities
		 *      F = Free
		 *      O = Occupied
		 *
		 *  case 1:
		 *      +---+---+---+    +---+---+---+
		 *      | O | F | O | => | O | F | O |
		 *      +---+---+---+    +---+---+---+
		 *  case 2:
		 *      +---+---+---+    +---+---+---+
		 *      | O | F | F | => | O | F     |
		 *      +---+---+---+    +---+---+---+
		 *  case 3:
		 *      +---+---+---+    +---+---+---+
		 *      | F | F | O | => | F     | O |
		 *      +---+---+---+    +---+---+---+
		 *  case 4:
		 *       +---+---+---+    +---+---+---+
		 *      | F | F | F | => | F         |
		 *      +---+---+---+    +---+---+---+
		 *
		 * \param header The header that should be joined with his neighbors.
		 */
		inline void joinFree(ZA_MEM_BLOCK_HEADER* header);

		inline ZA_MEM_LOCATION* getNewMemLocation();
		inline void returnMemLocation(ZA_MEM_LOCATION* location);
		
		/* ********************************************************* */
		// * Scan the memory *
		/* ********************************************************* */
		/*void reportLiveAllocations();
		void scanForLifeObjects();
		void scanBlock(void* mem, size_t size);
		bool scanIsValidPointer(void* pointer);*/

		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Allocation and deallocation of memory //
		/* //////////////////////////////////////////////////////////////////////////////// */
	public:
		ZA_MEM_LOCATION* allocate(size_t blockSize);
		void free(void* block);
		void free(void** block);
		void suggestScan();
	
		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Static methods //
		/* //////////////////////////////////////////////////////////////////////////////// */
		/**
		* \brief This tries to find the ZA_MEM_BLOCK_HEADER for the given block
		* \param block The block for the requested header.
		* \return The found header or a nullptr.
		*/
		static inline ZA_MEM_BLOCK_HEADER* GetBlockHeader(void* block)
		{
			return GetStaticInstance().getBlockHeader(block);
		}
		/**
		 * \brief This method tests if the given pointer is inside the bounds of this MemoryManager.
		 * \param block The pointer that should be tested.
		 * \return This returns whether the given pointer is inside or outside of the managed memory.
		 */
		static inline bool Contains(void* block)
		{
			return GetStaticInstance().contains(block);
		}
		
		static inline ZA_MEM_LOCATION* Allocate(size_t blockSize)
		{
			return GetStaticInstance().allocate(blockSize);
		}
		static inline void Free(void* block)
		{
			GetStaticInstance().free(block);
		}
		static inline void Free(void** block)
		{
			GetStaticInstance().free(block);
		}
	};

}}
