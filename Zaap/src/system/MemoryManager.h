#pragma once

#include "Za.h"

#include "Types.h"                //types

#ifndef ZA_MEM_FIRST_ALLOC_SIZE
#	define ZA_MEM_FIRST_CHUNK_SIZE      (256 * 1024 * 1024) //256MB
#endif

#ifndef ZA_MEM_CHUNK_SIZE
#	define ZA_MEM_CHUNK_SIZE            (16 * 1024 * 1024) //16MB
#endif

#ifndef ZA_MEM_BLOCK_MIN_SPLIT_SIZE
#	define ZA_MEM_BLOCK_MIN_SPLIT_SIZE     16
#endif
#define ZA_MEM_BSTATE_FREE              1
#define ZA_MEM_BSTATE_OCCUPIED          0

#define ZA_MEM_DEBUG_PATTERN            0xee

namespace zaap
{
	inline void* newMalloc(size_t size);
	inline void newFree(void* t);
}
namespace zaap { namespace system {

	// The header that is placed in front of 
	// allocated memory blocks.
	//
	// 32 BIT 
	//     => 4 byte per pointer 
	//
	//  Bits
	//  0 0 0 0 0 0 0 0 0 0 1 1 1
	//  0 1 2 3 4 5 6 7 8 9 0 1 2
	// +-------+-------+-------+-+
	// | PREV  | NEXT  | SIZE  |S|
	// +-------+-------+-------+-+
	//
	// PREV    :: The pointer to the previous memory block.
	// NEXT    :: The pointer to the next memory block.
	// SIZE    :: The size of this memory block. (without the header)
	// S->STATE:: The state of this memory block;
	//
	typedef struct ZAAP_API ZA_MEM_BLOCK_HEADER_ {
		ZA_MEM_BLOCK_HEADER_* PREV;
		ZA_MEM_BLOCK_HEADER_* NEXT;
		uint32 SIZE;
		byte STATE; // ZA_MEM_BSTATE_FREE or ZA_MEM_BSTATE_OCCUPIED
	} ZA_MEM_BLOCK_HEADER;

	class ZAAP_API MemoryManager
	{
	public:
		static MemoryManager* s_Instance;
	private:
		byte* m_AllocMem;
		uint m_Size;
		ZA_MEM_BLOCK_HEADER* m_AllocHeader;

		//TODO move m_AllocIndex back

		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Actual memory allocation //
		/* //////////////////////////////////////////////////////////////////////////////// */
		byte* allocMem(size_t chunkSize = ZA_MEM_FIRST_CHUNK_SIZE);
		bool allocMoreMem(size_t chunkSize = ZA_MEM_CHUNK_SIZE);
		void freeAllMem();

		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Initialization && Deconstruction //
		/* //////////////////////////////////////////////////////////////////////////////// */
		static void* operator new(size_t sz);
		static void operator delete(void* ptr);

		MemoryManager::MemoryManager();
		MemoryManager::~MemoryManager();

		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Memory Block manipulation //
		/* //////////////////////////////////////////////////////////////////////////////// */
		
		// Splitting:
		//      H     = Header
		//      BLOCK = the allocated memory.
		//      FREE  = free memory that isn't used.
		//
		// case 1:
		//      The block will be split if the leftover memory is large enough
		//      to fit a ZA_MEM_BLOCK_HEADER with the minimal size of
		//      ZA_MEM_BLOCK_MIN_SPLIT_SIZE.
		//
		//      +---+------------------+    +---+-------+---+------+
		//      | H | BLOCK : FREE     | => | H | BLOCK | H | FREE |
		//      +---+------------------+    +---+-------+---+------+
		//      |<H>|<-MBS->|<--oMem-->|
		//                  |<H>|<BMSZ>|
		//
		//      H    = ZA_MEM_BLOCK_HEADER, the header for the following memory block.
		//      MBS  = minBlockSize, the minimal size of this block.
		//      oMem = The memory that is over and can be used differently.
		//      BMSZ = The minimal size of the split block (ZA_MEM_BLOCK_MIN_SPLIT_SIZE).
		//
		// case 2:
		//      The block won't be split if the leftover memory is too small for
		//      the ZA_MEM_BLOCK_HEADER and ZA_MEM_BLOCK_MIN_SPLIT_SIZE.
		//
		//      +---+--------------+    +---+--------------+
		//      | H | BLOCK : FREE | => | H | BLOCK : FREE |
		//      +---+--------------+    +---+--------------+
		//      |<H>|<-MBS->|<oMem>|
		//                  |<H>|<BMSZ>|
		//
		//      H    = ZA_MEM_BLOCK_HEADER, the header for the following memory block.
		//      MBS  = minBlockSize, the minimal size of this block.
		//      oMem = The memory that is over and can be used differently.
		//      
		//      |<H>|<BMSZ>| = are the minimal size of the for splitting. The free memory
		//                     isn't large enough to fit them so the block isn't split.
		//
		inline void split(ZA_MEM_BLOCK_HEADER* header, uint32 minBlockSize);		
		// Possibilities
		//      F = Free
		//      O = Occupied
		//
		//  case 1:
		//      +---+---+---+    +---+---+---+
		//      | O | F | O | => | O | F | O |
		//      +---+---+---+    +---+---+---+
		//  case 2:
		//      +---+---+---+    +---+---+---+
		//      | O | F | F | => | O | F     |
		//      +---+---+---+    +---+---+---+
		//  case 3:
		//      +---+---+---+    +---+---+---+
		//      | F | F | O | => | F     | O |
		//      +---+---+---+    +---+---+---+
		//  case 4:
		//      +---+---+---+    +---+---+---+
		//      | F | F | F | => | F         |
		//      +---+---+---+    +---+---+---+
		//
		inline void joinFree(ZA_MEM_BLOCK_HEADER* header);

		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Allocation and deallocation of memory //
		/* //////////////////////////////////////////////////////////////////////////////// */
	public:
		static void* Allocate(size_t blockSize);
		static void Free(void* block);
	private:
		void* allocate(size_t blockSize);
		void free(void* block);
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

	inline void* newMalloc(size_t size)
	{
		return system::MemoryManager::Allocate(size);
		//return malloc(size);
	}
	inline void newFree(void* t)
	{
		system::MemoryManager::Free(t);
		//free(t);
	}
}