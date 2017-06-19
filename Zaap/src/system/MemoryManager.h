#pragma once

#include "Za.h"

#include "Types.h"                //types

#ifndef ZA_MEM_FIRST_ALLOC_SIZE
#	define ZA_MEM_FIRST_CHUNK_SIZE      (256 * 1024 * 1024) //256MB
#endif

#ifndef ZA_MEM_CHUNK_SIZE
#	define ZA_MEM_CHUNK_SIZE            (16 * 1024 * 1024) //16MB
#endif

#define ZA_MEM_BSTATE_FREE              1
#define ZA_MEM_BSTATE_OCCUPIED          0
#define ZA_MEM_BLOCK_MIN_SPLIT_SIZE     16

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
		//static MemoryManager* s_Instance;
	private:
		friend void* zaap::newMalloc(size_t size);
		friend void zaap::newFree(void* t);

	private:
		static byte* m_AllocMem;
		static uint m_Size;
		static ZA_MEM_BLOCK_HEADER* m_AllocHeader;

		//TODO move m_AllocIndex back

		static byte* AllocMem(size_t chunkSize = ZA_MEM_FIRST_CHUNK_SIZE);
		static bool AllocMoreMem(size_t chunkSize = ZA_MEM_CHUNK_SIZE);
		static void freeAllMem();

		static void* operator new(size_t sz);
		static void operator delete(void* ptr);

	private:
		static inline void Split(ZA_MEM_BLOCK_HEADER* header, uint32 minBlockSize);
		
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
		static inline void JoinFree(ZA_MEM_BLOCK_HEADER* header);
	public:
		static void* Allocate(size_t blockSize);
		static void Free(void* block);
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