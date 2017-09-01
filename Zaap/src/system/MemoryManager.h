#pragma once

#include "Za.h"
#include <cstdint>

#pragma region Option Macros
#ifndef ZA_MEM_FIRST_POOL_SIZE //256MB
#	define ZA_MEM_FIRST_POOL_SIZE                (256 * 1024 * 1024) 
#endif

#ifndef ZA_MEM_DEFAULT_POOL_SIZE
#	define ZA_MEM_DEFAULT_POOL_SIZE              (16 * 1024 * 1024) //16MB
#endif

#ifndef ZA_MEM_BLOCK_MIN_SPLIT_SIZE
#	define ZA_MEM_BLOCK_MIN_SPLIT_SIZE           32 // plus the size of the ZA_MEM_BLOCK_HEADER
#endif

#ifdef ZA_32BIT
#	define ZAAP_MEM_TEST_BUFFER_SIZE             2
#elif ZA_64BIT
#	define ZAAP_MEM_TEST_BUFFER_SIZE             6
#endif

#define ZAAP_MEM_BLOCK_HEADER_ALIGNMENT          sizeof(ZA_MEM_BLOCK_HEADER)

#pragma endregion 

//TODO move m_AllocIndex back
//TODO Okay so following problem ZA_ASSERT uses the new and delete keywords... this means that an error message it self use the methods that cause the error. (Not good)

namespace zaap { namespace system {

	// these types are the same as the ones mentioned in "Types.h"
	typedef unsigned char       mm_byte;
	typedef short               mm_int16;
	typedef unsigned int        mm_uint;

	typedef enum ZAAP_API ZA_MEM_BLOCK_STATE_ : mm_int16 {
		ZA_MEM_BLOCK_STATE_OCCUPIED = 0,
		ZA_MEM_BLOCK_STATE_FREE     = 1
	} ZA_MEM_BLOCK_STATE;

	/* //////////////////////////////////////////////////////////////////////////////// */
	// // ZA_MEM_BLOCK_HEADER //
	/* //////////////////////////////////////////////////////////////////////////////// */
	// This header is in front of every allocation from this MemeoryManager.
	//
	// 32 BIT => 4 bytes per pointer 
	//  Bytes 
	//  0 0 0 0 0 0 0 0 0 1 1 1 1 1 1 1
	//  1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6
	// +---+---+-------+-------+-------+
	// |TB | S | Prev  | Next  | Size  |
	// +---+---+-------+-------+-------+
	//
	// 64 BIT => 8 bytes per pointer 
	//  Bytes 
	//  0 0 0 0 0 0 0 0 0 1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2 2 2 2 3 3 3 
	//  1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2
	// +-----------+---+---------------+---------------+---------------+
	// |TestBuffer | S |   Previous    |      Next     |     Size      |
	// +-----------+---+---------------+---------------+---------------+
	//
	// TestBuffer    :: A buffer that is filled with ZA_MEM_TEST_BUFFER_PATTERN. This buffer is used to find the
	//                  header and to align the following memory.
	// State         :: The state of this memory block.
	// Previous      :: The pointer to the previous memory block.
	// Next          :: The pointer to the next memory block.
	// Size          :: The size of this memory block. (without the header)
	//
	typedef struct ZAAP_API ZA_MEM_BLOCK_HEADER_ {
		// 1 - 4 bytes
		mm_byte               TestBuffer[ZAAP_MEM_TEST_BUFFER_SIZE];
		ZA_MEM_BLOCK_STATE    State; // ZA_MEM_BLOCK_STATE_OCCUPIED or ZA_MEM_BLOCK_STATE_FREE
		// 5 - 8 bytes
		ZA_MEM_BLOCK_HEADER_* Previous;
		// 8 - 12 bytes
		ZA_MEM_BLOCK_HEADER_* Next;
		// 13 - 16 bytes
		size_t                Size;
	} ZA_MEM_BLOCK_HEADER;

	/* //////////////////////////////////////////////////////////////////////////////// */
	// // ZA_MEM_MEMORY_POOL //
	/* //////////////////////////////////////////////////////////////////////////////// */
	/**
	 * \brief This struct is used to keep the information about a memory pool.
	 */
	typedef struct ZAAP_API ZA_MEM_MEMORY_POOL_ {
		ZA_MEM_MEMORY_POOL_* Next;
		void*                Memory;
		size_t               Size;
		size_t               SizeUsed;

		inline bool isMember(void const* block) const
		{
			return (block &&                                         // block != nullptr
				(uintptr_t)block >= (uintptr_t)Memory &&               // Memory <= block < (Memory + Size)
				(uintptr_t)block < (uintptr_t)Memory + Size);
		}

	} ZA_MEM_MEMORY_POOL;

	/* //////////////////////////////////////////////////////////////////////////////// */
	// // MemoryManager //
	/* //////////////////////////////////////////////////////////////////////////////// */
	class ZAAP_API MemoryManager
	{
	private:
	public:
		static MemoryManager* GetStaticInstance()
		{
			//TODO this works I don't know why... well I do know but still. I should change / manipulate the static initialization order and make sure this is created first and therefor destroyed last. 

			static MemoryManager* manager = new MemoryManager();

			return manager;
		}
	private:
		ZA_MEM_MEMORY_POOL* m_PartialFilledPools;
		ZA_MEM_MEMORY_POOL* m_FilledPools;

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
		static ZA_MEM_MEMORY_POOL* CreatePool(size_t size = ZA_MEM_DEFAULT_POOL_SIZE);
		static void DestroyPool(ZA_MEM_MEMORY_POOL* pool);

		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Utilities //
		/* //////////////////////////////////////////////////////////////////////////////// */
	public:
		/**
		* \brief This method tests if the given pointer is inside a memory pool of this MemoryManager
		* \param block The pointer that should be tested.
		* \return This returns the memory pool for the object if it is inside one.
		*/
		ZA_MEM_MEMORY_POOL* getContainingPool(void const* block);
		/**
		* \brief This method tests if the given pointer is inside a memory pool of this MemoryManager
		* \param block The pointer that should be tested.
		* \return This returns the memory pool for the object if it is inside one.
		*/
		ZA_MEM_MEMORY_POOL const* getContainingPool(void const* block) const;
		/**
		* \brief This method tests if the given pointer is inside the bounds of this MemoryManager
		* \param block The pointer that should be tested.
		* \return This returns whether the given pointer is inside or outside of the managed memory.
		*/
		inline bool contains(void const* block) const
		{
			return (getContainingPool(block)) ? true : false;
		}
		/**
		 * \brief This tries to find the ZA_MEM_BLOCK_HEADER for the given block
		 * \param block The block for the requested header.
		 * \return The found header or a null pointer.
		 */
		ZA_MEM_BLOCK_HEADER* getBlockHeader(void const* block);
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
		void split(ZA_MEM_BLOCK_HEADER* header, size_t minBlockSize);
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
		 *      +---+---+---+    +---+---+---+
		 *      | F | F | F | => | F         |
		 *      +---+---+---+    +---+---+---+
		 *
		 * \param header The header that should be joined with his neighbors.
		 */
		void joinFree(ZA_MEM_BLOCK_HEADER* header);

		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Allocation and deallocation of memory //
		/* //////////////////////////////////////////////////////////////////////////////// */
	public:
		void* allocateSinglePool(size_t blockSize);
		void* allocate(size_t blockSize);
		void free(void* block);
	};

}}
