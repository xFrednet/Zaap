#include "MemoryManager.h"

#include "util/Log.h"

//#define ZAAP_MEM_DEBUG
//#define ZAAP_MEM_LOG_TO_MUCH

/* //////////////////////////////////////////////////////////////////////////////// */
// // Macros //
/* //////////////////////////////////////////////////////////////////////////////// */

/* ********************************************************* */
// * Debug and logging macros *
/* ********************************************************* */
#ifdef ZAAP_MEM_DEBUG
#	define ZA_MEM_INFO(...)                 ZA_INFO(__VA_ARGS__)
#	define ZA_MEM_ALERT(...)                ZA_ALERT(__VA_ARGS__)
#	define ZA_MEM_ERROR(...)                ZA_ERROR(__VA_ARGS__)

#	define ZA_MEM_EXASSERT(...)             ZA_ASSERT(__VA_ARGS__)
#	define ZA_MEM_DEBUG_FILL(header)        memset((void*)((uintptr_t)header + sizeof(ZA_MEM_BLOCK_HEADER)), ZA_MEM_DEBUG_PATTERN, header->SIZE)
#else
#	define ZA_MEM_INFO(...)
#	define ZA_MEM_ALERT(...)
#	define ZA_MEM_ERROR(...)

#	define ZA_MEM_EXASSERT(...)
#	define ZA_MEM_DEBUG_FILL(ptr, size)
#endif

//extra checks, these will slow down the process. They are only used for debugging.
#ifdef ZAAP_MEM_LOG_TO_MUCH
#	define ZA_MEM_EXINFO(...)       ZA_MEM_INFO(__VA_ARGS__)
#else
#	define ZA_MEM_EXINFO(...)
#endif

/* ********************************************************* */
// * Util macros *
/* ********************************************************* */
#define ZA_MEM_FILL_ZERO(header)     memset((void*)((uintptr_t)header + sizeof(ZA_MEM_BLOCK_HEADER)), 0x00, header->SIZE)


/* //////////////////////////////////////////////////////////////////////////////// */
// // definitions //
/* //////////////////////////////////////////////////////////////////////////////// */
using namespace std;
namespace zaap { namespace system
{

	//MemoryManager* MemoryManager::s_Instance = new MemoryManager();
	byte* MemoryManager::m_AllocMem = AllocMem();
	uint MemoryManager::m_Size = ZA_MEM_FIRST_CHUNK_SIZE;
	ZA_MEM_BLOCK_HEADER* MemoryManager::m_AllocHeader = (ZA_MEM_BLOCK_HEADER*)&m_AllocMem[0];

	byte* MemoryManager::AllocMem(size_t chunkSize)
	{
		ZA_ASSERT(!m_AllocMem, "Why is this not null");
		//ZA_ASSERT(m_Size == 0, "Why is this not null.. it should be null");
		//ZA_ASSERT(!m_AllocHeader, "Why is this not null... what did I Fuck up");
		
		//
		//data block
		//
		m_AllocMem = (byte*)malloc(chunkSize);
		ZA_ASSERT(m_AllocMem);
		if (!m_AllocMem)
			return nullptr;
		
		m_Size = chunkSize;

		m_AllocHeader = (ZA_MEM_BLOCK_HEADER*)m_AllocMem;
		memset(m_AllocHeader, 0, sizeof(ZA_MEM_BLOCK_HEADER));
		m_AllocHeader->SIZE = (chunkSize - sizeof(ZA_MEM_BLOCK_HEADER));
		m_AllocHeader->STATE = ZA_MEM_BSTATE_FREE;
		ZA_MEM_DEBUG_FILL(m_AllocHeader);

		ZA_MEM_INFO("Allocated the first memory chunk. with the size: ", chunkSize);

		return m_AllocMem;
	}
	bool MemoryManager::AllocMoreMem(size_t chunkSize)
	{
		size_t oldSize = m_Size;
		size_t newSize = m_Size + chunkSize;
		m_Size = 0;
		byte* oldAlloc = m_AllocMem;
		byte* newAlloc = (byte*)realloc(m_AllocMem, oldSize + chunkSize);
		ZA_ASSERT(newAlloc);
		if (!newAlloc)
		{
			m_Size = oldSize;
			m_AllocMem = oldAlloc;
			return false;
		}
		if (newAlloc != oldAlloc)
		{
			//TODO move ptrs because the alloc location has changed
		}
		m_AllocMem = newAlloc;
		m_Size = oldSize + chunkSize;
		
		ZA_ASSERT(m_AllocHeader, "I'm not depressed...but this just isn't possible");
		ZA_MEM_BLOCK_HEADER* memHeader = m_AllocHeader;
		while (memHeader->NEXT)
			memHeader = memHeader->NEXT;
		if (memHeader->STATE == ZA_MEM_BSTATE_FREE)
		{
			memHeader->SIZE += chunkSize;
			ZA_MEM_DEBUG_FILL(memHeader);
		}
		else
		{
			ZA_MEM_BLOCK_HEADER* newHeader = memHeader + sizeof(ZA_MEM_BLOCK_HEADER) + memHeader->SIZE;
			newHeader->PREV = memHeader;
			newHeader->NEXT = nullptr;
			newHeader->SIZE = &m_AllocMem[m_Size - 1] - (void*)newHeader - sizeof(ZA_MEM_BLOCK_HEADER);
			newHeader->STATE = ZA_MEM_BSTATE_FREE;

			memHeader->NEXT = newHeader;
			ZA_MEM_DEBUG_FILL(newHeader);
		}

		ZA_MEM_INFO("Allocated a new Memory chunk. The size was: ", chunkSize);

		return true;
	}
	void MemoryManager::freeAllMem()
	{
		//TODO nullptr all smart ptrs
		m_Size = 0;
		::free(m_AllocMem);

		ZA_MEM_INFO("Freed all memory. Bye bye");
	}

	//MemoryManager::MemoryManager()
	//	: m_AllocMem(nullptr),
	//	m_Size(0),
	//	m_AllocHeader(nullptr)
	//{
	//	if (!AllocMem(ZA_MEM_FIRST_CHUNK_SIZE))
	//	{
	//		ZA_ASSERT(false, "AllocNewMemBlock(ZA_MEM_FIRST_CHUNK_SIZE) failed");
	//		exit(ZA_ERROR_MEM_ALLOCATION_ERROR);
	//	}
	//	ZA_INFO("The initialization was successful ");
	//}
	//MemoryManager::~MemoryManager()
	//{
	//	//
	//	// Freeing memory
	//	//
	//	freeAllMem();
	//	ZA_LOG_CLEANUP();
	//}
	void* MemoryManager::operator new(size_t sz)
	{
		MemoryManager* mgr = (MemoryManager*)malloc(sz);
		return mgr;
	}
	void MemoryManager::operator delete(void* ptr)
	{
		::free(ptr);
	}

	void MemoryManager::Split(ZA_MEM_BLOCK_HEADER* header, uint32 minBlockSize)
	{
		ZA_ASSERT(header->SIZE > minBlockSize, "WTF you can't make it bigger by splitting it");
		ZA_ASSERT((void*)((uintptr_t)header + minBlockSize) < &m_AllocMem[m_Size - 1], "HOW?? HOW should the memBlock extend over the allocated memory");
		
		if (header->SIZE > (minBlockSize + sizeof(ZA_MEM_BLOCK_HEADER) + ZA_MEM_BLOCK_MIN_SPLIT_SIZE))
		{
			ZA_MEM_BLOCK_HEADER* splitHeader = (ZA_MEM_BLOCK_HEADER*)((uintptr_t)header + sizeof(ZA_MEM_BLOCK_HEADER) + minBlockSize);
			splitHeader->PREV = header;
			splitHeader->NEXT = header->NEXT;
			splitHeader->STATE = ZA_MEM_BSTATE_FREE;
			splitHeader->SIZE = header->SIZE - (minBlockSize + sizeof(ZA_MEM_BLOCK_HEADER));
			ZA_MEM_DEBUG_FILL(splitHeader);

			header->SIZE = minBlockSize;
			header->NEXT = splitHeader;
			//TODO check if the new block should be merged with the next one
			ZA_MEM_EXINFO("I split a MemHeader. The new size is: ", header->SIZE, ". The other split header has a size of: ", splitHeader->SIZE, "(header: ", (uintptr_t)header, ", splitHeader", (uintptr_t)splitHeader ,")");
		}
	}
	void MemoryManager::JoinFree(ZA_MEM_BLOCK_HEADER* header)
	{
		ZA_ASSERT(header->STATE == ZA_MEM_BSTATE_FREE, "The state should be free!! Who did this");
		uint8 positions = 0;
		
		if (header->PREV)
			positions |= header->PREV->STATE << 4; //0000 0000 => 000S 0000 (S = STATE)
		if (header->NEXT)
			positions |= header->NEXT->STATE;      //0000 0000 => 0000 000S (S = STATE)
		//TODO test if m_AllocHeader is destroyd by this
		ZA_MEM_BLOCK_HEADER* prevHeader;
		ZA_MEM_BLOCK_HEADER* nextHeader;
		switch (positions) //assembly
		{
		// |O|F|F| => |O|F--|
		case 0x01: 
			nextHeader = header->NEXT;

			header->NEXT = nextHeader->NEXT;
			header->SIZE = header->SIZE + sizeof(ZA_MEM_BLOCK_HEADER) + nextHeader->SIZE;

			ZA_MEM_DEBUG_FILL(header);
			ZA_MEM_EXINFO("joinFree: joined |O|F|F| => |O|F--|");
			break;
		// |F|F|O| => |F--|O|
		case 0x10:
			prevHeader = header->PREV;

			prevHeader->NEXT = header->NEXT;
			prevHeader->SIZE = prevHeader->SIZE + sizeof(ZA_MEM_BLOCK_HEADER) + header->SIZE;

			ZA_MEM_DEBUG_FILL(prevHeader);
			ZA_MEM_EXINFO("joinFree: joined |F|F|O| => |F--|O|");
			break;
		// |F|F|F| => |F----|
		case 0x11:
			prevHeader = header->PREV;
			nextHeader = header->NEXT;

			prevHeader->NEXT = nextHeader->NEXT + 
				sizeof(ZA_MEM_BLOCK_HEADER) + header->SIZE + 
				sizeof(ZA_MEM_BLOCK_HEADER) + nextHeader->SIZE;

			ZA_MEM_DEBUG_FILL(prevHeader);
			ZA_MEM_EXINFO("joinFree: joined |F|F|F| => |F----|");
			break;
		default:
			return;
		}
	}

	void* MemoryManager::Allocate(size_t blockSize)
	{
		if (blockSize >= ZA_MEM_CHUNK_SIZE)
		{
			//TODO alloc outside m_AllocMem
			ZA_ASSERT(blockSize < ZA_MEM_CHUNK_SIZE, "TODO alloc outside m_AllocMem");
			return nullptr;
		}

		//
		// Find free Memory
		//
		ZA_ASSERT(m_AllocHeader, "OKAY.............. Kill your self");
		ZA_MEM_BLOCK_HEADER* memHeader = m_AllocHeader;
		while (memHeader)
		{
			if (memHeader->STATE == ZA_MEM_BSTATE_FREE || memHeader->SIZE >= blockSize)
			{
				memHeader->STATE = ZA_MEM_BSTATE_OCCUPIED;
				Split(memHeader, blockSize);
				if (memHeader->NEXT)
					m_AllocHeader = memHeader->NEXT;
				else
					m_AllocHeader = memHeader;
				
				ZA_MEM_FILL_ZERO(memHeader);
				ZA_MEM_EXINFO("Allocated a new memory block at: ", (uintptr_t)(memHeader + sizeof(ZA_MEM_BLOCK_HEADER)), ", with the size: ", memHeader->SIZE);
				return (void*)((uintptr_t)memHeader + sizeof(ZA_MEM_BLOCK_HEADER));
			}
			if (memHeader->NEXT)
				memHeader = memHeader->NEXT;
			else
				break;
		}

		//
		// Allocate new Memory
		//
		// memHeader->NEXT => nullptr => alloc new Memory
		ZA_MEM_EXINFO("Failed to find a fitting memory block => allocating a new memory chunk");
		if (!AllocMoreMem(ZA_MEM_CHUNK_SIZE))
		{
			ZA_ASSERT(false, "AllocMoreMem failed");
			return nullptr;
		}
		
		//
		// Find free Memory
		//
		if (memHeader->NEXT)
			memHeader = memHeader->NEXT;
		if (memHeader->STATE == ZA_MEM_BSTATE_FREE)
		{
			//TODO maybe recall this method it should work this time 
			memHeader->STATE = ZA_MEM_BSTATE_OCCUPIED;
			Split(memHeader, blockSize);
			if (memHeader->NEXT)
				m_AllocHeader = memHeader->NEXT;
			else
				m_AllocHeader = memHeader;

			ZA_MEM_FILL_ZERO(memHeader);
			ZA_MEM_EXINFO("Allocated a new memory block at: ", (uintptr_t)(memHeader + sizeof(ZA_MEM_BLOCK_HEADER)), ", with the size: ", memHeader->SIZE);
			return (void*)((uintptr_t)memHeader + sizeof(ZA_MEM_BLOCK_HEADER));
		}
		return nullptr;
		
		//Fuck my life... I thought that would be easy
	}
	void MemoryManager::Free(void* block)
	{
		ZA_MEM_EXASSERT(block, "Null why would you give me a nullptr?? What have I done to you")
		ZA_ASSERT(block >= m_AllocMem + sizeof(ZA_MEM_BLOCK_HEADER) && block < &m_AllocMem[m_Size - 1]);
		if (!block || block < m_AllocMem + sizeof(ZA_MEM_BLOCK_HEADER) || block > &m_AllocMem[m_Size - 1])
			return;

		ZA_MEM_BLOCK_HEADER* header = (ZA_MEM_BLOCK_HEADER*)((uintptr_t)block - sizeof(ZA_MEM_BLOCK_HEADER));
		ZA_MEM_EXASSERT(header->STATE == ZA_MEM_BSTATE_OCCUPIED, "Stop just stop!!!")
		header->STATE = ZA_MEM_BSTATE_FREE;
		
		ZA_MEM_DEBUG_FILL(header);
		JoinFree(header);
	}
}}
