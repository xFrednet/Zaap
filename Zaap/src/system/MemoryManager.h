#pragma once

#include "Za.h"
#include "Types.h"                //types

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

#define ZA_MEM_BSTATE_FREE              1
#define ZA_MEM_BSTATE_OCCUPIED          0

#define ZA_MEM_DEBUG_PATTERN            0xee

//TODO add the option to track the use count or just use the default GarbageColector
//TODO implement suggestScan
//TODO move m_AllocIndex back

namespace zaap
{
	inline void* newMalloc(size_t size);
	inline void newFree(void* t);
}
namespace zaap { namespace system {

	/* //////////////////////////////////////////////////////////////////////////////// */
	// // ZA_MEM_LOCATION //
	/* //////////////////////////////////////////////////////////////////////////////// */
	typedef struct ZAAP_API ZA_MEM_LOCATION_ {
#ifdef ZA_MEM_NULL_DELETED_LOCATION
		union {
#endif
			ZA_MEM_LOCATION_* NEXT;
			void*             MEM_BLOCK;
#ifdef ZA_MEM_NULL_DELETED_LOCATION
		};
#endif
	} ZA_MEM_LOCATION;

	/* //////////////////////////////////////////////////////////////////////////////// */
	// // ZA_MEM_PAGE //
	/* //////////////////////////////////////////////////////////////////////////////// */
	typedef struct ZAAP_API ZA_MEM_PAGE_ {
		ZA_MEM_PAGE_*   NEXT;
		ZA_MEM_LOCATION LOCATIONS[ZA_MEM_PAGE_LOCATION_COUNT];
		//TODO test performance with a PREV reference

		ZA_MEM_PAGE_();
	} ZA_MEM_PAGE;

}}
namespace zaap { namespace system {

	// The header that is placed in front of 
	// allocated memory blocks.
	//
	// 32 BIT 
	//     => 4 bytes per pointer 
	//
	//  Bytes 
	//  0 0 0 0 0 0 0 0 0 1 1 1 1 1 1 1 1
	//  1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7
	// +-------+-------+-------+-+-------+
	// | PREV  | NEXT  | SIZE  |S|  LOC  |
	// +-------+-------+-------+-+-------+
	//
	// PREV          :: The pointer to the previous memory block.
	// NEXT          :: The pointer to the next memory block.
	// SIZE          :: The size of this memory block. (without the header)
	// S->STATE      :: The state of this memory block;
	// LOC->LOCATION :: The ID of the Location Page that includes .
	//
	typedef struct ZAAP_API ZA_MEM_BLOCK_HEADER_ {
		ZA_MEM_BLOCK_HEADER_* PREV;
		ZA_MEM_BLOCK_HEADER_* NEXT;
		uint32                SIZE;
		byte                  STATE; // ZA_MEM_BSTATE_FREE or ZA_MEM_BSTATE_OCCUPIED
		ZA_MEM_LOCATION_*     LOCATION;
	} ZA_MEM_BLOCK_HEADER;

	class ZAAP_API MemoryManager
	{
	public:
		static MemoryManager* s_Instance;
	private:
		byte* m_AllocMem;
		uint m_Size;

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
		inline void split(ZA_MEM_BLOCK_HEADER* header, uint32 minBlockSize);
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

		/* ********************************************************* */
		// * Scan the memory *
		/* ********************************************************* */
		void scan();
		void scanBlock(void* mem, size_t size);
		bool scanIsValidPointer(void* pointer);
		

		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Allocation and deallocation of memory //
		/* //////////////////////////////////////////////////////////////////////////////// */
	public:
		void** allocate(size_t blockSize);
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
		static ZA_MEM_BLOCK_HEADER* GetBlockHeader(void* block);
		/**
		 * \brief This method tests if the given pointer is inside the bounds of this MemoryManager.
		 * \param block The pointer that should be tested.
		 * \return This returns whether the given pointer is inside or outside of the managed memory.
		 */
		static bool Contains(void* block);
		
		static void** Allocate(size_t blockSize);
		static void Free(void* block);
		static void Free(void** block);
		static void SuggestScan();
	};

}}
namespace zaap
{
	/*template<typename T>
	T* operator new(size_t objSize) {
	}

	template<typename T>
	void operator delete(T obj)
	{
	}*/

	template<typename T>
	inline T** newMalloc(size_t size)
	{
		return (T**)system::MemoryManager::Allocate(size);
		//return malloc(size);
	}
	inline void newFree(void* t)
	{
		system::MemoryManager::Free(t);
		//free(t);
	}
}