#include "MemoryManager.h"

#include "util/Log.h"

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
	MemoryManager* MemoryManager::s_Instance = new MemoryManager();

	/* //////////////////////////////////////////////////////////////////////////////// */
	// // Actual memory allocation //
	/* //////////////////////////////////////////////////////////////////////////////// */
	bool MemoryManager::allocMem(size_t chunkSize)
	{
		ZA_ASSERT(!m_AllocMem, "Why is this not null");
		ZA_ASSERT(m_Size == 0, "Why is this not null.. it should be null");
		ZA_ASSERT(!m_AllocHeader, "Why is this not null... what did I Fuck up");
		
		//
		//data block
		//
		m_AllocMem = (byte*)malloc(chunkSize);
		ZA_ASSERT(m_AllocMem);
		if (!m_AllocMem)
			return false;
		
		m_Size = chunkSize;

		m_AllocHeader = (ZA_MEM_BLOCK_HEADER*)m_AllocMem;
		memset(m_AllocHeader, 0, sizeof(ZA_MEM_BLOCK_HEADER));
		m_AllocHeader->SIZE = (chunkSize - sizeof(ZA_MEM_BLOCK_HEADER));
		m_AllocHeader->STATE = ZA_MEM_BSTATE_FREE;
		ZA_MEM_DEBUG_FILL(m_AllocHeader);

		ZA_MEM_INFO("Allocated the first memory chunk. with the size: ", chunkSize);
		return true;
	}
	bool MemoryManager::allocMoreMem(size_t chunkSize)
	{
		ZA_ASSERT(m_AllocMem && m_Size != 0 && m_AllocHeader, "This message should never be visible.");

		size_t oldSize = m_Size;
		m_Size = 0;
		byte* oldAlloc = m_AllocMem;
		byte* newAlloc = (byte*)realloc(m_AllocMem, oldSize + chunkSize);
		ZA_MEM_EXASSERT(newAlloc);
		if (!newAlloc)
		{
			m_Size = oldSize;
			m_AllocMem = oldAlloc;
			return false;
		}
		if (newAlloc != oldAlloc)
		{
			ZA_ASSERT(false, "this isn't implemented jet. kill the developer");
			//TODO move ptrs because the alloc location has changed
		}
		m_AllocMem = newAlloc;
		m_Size = oldSize + chunkSize;
		
		ZA_MEM_EXASSERT(m_AllocHeader, "I'm not depressed...but this just isn't possible");
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
			newHeader->SIZE = (uint32)((uintptr_t)&m_AllocMem[m_Size - 1] - (uintptr_t)newHeader - sizeof(ZA_MEM_BLOCK_HEADER));
			newHeader->STATE = ZA_MEM_BSTATE_FREE;

			memHeader->NEXT = newHeader;
			ZA_MEM_DEBUG_FILL(newHeader);
		}

		ZA_MEM_INFO("Allocated a new Memory chunk. The size was: ", chunkSize);

		return true;
	}
	void MemoryManager::freeAllMem()
	{
		ZA_ASSERT(m_AllocMem && m_Size != 0 && m_AllocHeader, "This message should never be visible.");
		
		//TODO nullptr all smart ptrs
		m_Size = 0;
		::free(m_AllocMem);

		ZA_MEM_INFO("Freed all memory. Bye bye");
	}

	/* //////////////////////////////////////////////////////////////////////////////// */
	// // Initialization && Deconstruction //
	/* //////////////////////////////////////////////////////////////////////////////// */
	void* MemoryManager::operator new(size_t sz)
	{
		return (MemoryManager*)malloc(sz);
	}
	void MemoryManager::operator delete(void* ptr)
	{
		::free(ptr);
	}

	MemoryManager::MemoryManager()
		: m_AllocMem(nullptr),
		m_Size(0),
		m_AllocHeader(nullptr)
	{
		ZA_MEM_EXASSERT(!s_Instance);

		if (!allocMem(ZA_MEM_FIRST_CHUNK_SIZE))
		{
			ZA_ASSERT(false, "AllocNewMemBlock(ZA_MEM_FIRST_CHUNK_SIZE) failed");
			exit(ZA_ERROR_MEM_ALLOCATION_ERROR);
		}
		ZA_INFO("The initialization was successful ");
	}
	MemoryManager::~MemoryManager()
	{
		//
		// Freeing memory
		//
		freeAllMem();
		ZA_LOG_CLEANUP();
	}

	/* //////////////////////////////////////////////////////////////////////////////// */
	// // Memory Block manipulation //
	/* //////////////////////////////////////////////////////////////////////////////// */
	bool MemoryManager::contains(void* block) const
	{
		return (block && (uintptr_t)block >= (uintptr_t)m_AllocMem && (uintptr_t)block < (uintptr_t)&m_AllocMem[m_Size - 1]);
	}
	ZA_MEM_BLOCK_HEADER* MemoryManager::getBlockHeader(void* block)
	{
		ZA_MEM_EXASSERT(contains((void*)((uintptr_t)block - sizeof(ZA_MEM_BLOCK_HEADER))), "block: ", (uintptr_t)block, ", m_AllocMem: ", (uintptr_t)m_AllocMem, ", &m_AllocMem[m_Size - 1]", (uintptr_t)&m_AllocMem[m_Size - 1])

		if (!contains((void*)((uintptr_t)block - sizeof(ZA_MEM_BLOCK_HEADER))))
			return nullptr;

		return (ZA_MEM_BLOCK_HEADER*) ((uintptr_t)block - sizeof(ZA_MEM_BLOCK_HEADER));
	}

	void MemoryManager::split(ZA_MEM_BLOCK_HEADER* header, uint32 minBlockSize)
	{
		ZA_MEM_EXASSERT(contains(header), "<insert a funny and depressed debug message>");
		ZA_MEM_EXASSERT(header->SIZE > minBlockSize, "WTF you can't make it bigger by splitting it");
		ZA_MEM_EXASSERT(((uintptr_t)header + header->SIZE) >= (uintptr_t)&m_AllocMem[m_Size - 1], "HOW?? HOW should the memBlock extend over the allocated memory");
		
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

			joinFree(splitHeader);
			ZA_MEM_EXINFO("I split a MemHeader. The new size is: ", header->SIZE, ". The other split header has a size of: ", splitHeader->SIZE, "(header: ", (uintptr_t)header, ")");
		}
	}
	void MemoryManager::joinFree(ZA_MEM_BLOCK_HEADER* header)
	{
		ZA_MEM_EXASSERT(contains(header), "Off with his not existing head.");
		ZA_MEM_EXASSERT(header->STATE == ZA_MEM_BSTATE_FREE, "The state should be free!! Who did this");
		
		uint8 positions = 0;
		if (header->PREV)
			positions |= header->PREV->STATE << 4; //0000 0000 => 000S 0000 (S = STATE)
		if (header->NEXT)
			positions |= header->NEXT->STATE;      //0000 0000 => 0000 000S (S = STATE)
		//TODO test if m_AllocHeader is destroyd by this
		
		ZA_MEM_BLOCK_HEADER* prevHeader;
		ZA_MEM_BLOCK_HEADER* nextHeader;
		switch (positions)
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

	/* //////////////////////////////////////////////////////////////////////////////// */
	// // Allocation and deallocation of memory //
	/* //////////////////////////////////////////////////////////////////////////////// */
	void* MemoryManager::allocate(size_t blockSize)
	{
		ZA_MEM_EXASSERT(m_AllocMem && m_Size != 0 && m_AllocHeader, "OKAY.............. Kill your self");

		if (blockSize >= ZA_MEM_CHUNK_SIZE)
		{
			//TODO alloc outside m_AllocMem
			ZA_ASSERT(blockSize < ZA_MEM_CHUNK_SIZE, "TODO alloc outside m_AllocMem");
			return nullptr;
		}

		//
		// Find free Memory
		//
		ZA_MEM_BLOCK_HEADER* memHeader = m_AllocHeader;
		while (memHeader)
		{
			if (memHeader->STATE == ZA_MEM_BSTATE_FREE || memHeader->SIZE >= blockSize)
			{
				memHeader->STATE = ZA_MEM_BSTATE_OCCUPIED;
				split(memHeader, blockSize);
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
		if (!allocMoreMem(ZA_MEM_CHUNK_SIZE))
		{
			//TODO deal with error
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
			split(memHeader, blockSize);
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
	void MemoryManager::free(void* block)
	{
		ZA_MEM_EXASSERT(block, "Null why would you give me a nullptr?? What have I done to you");
		ZA_MEM_EXASSERT(contains(block));
		if (!contains(block))
			return;

		ZA_MEM_BLOCK_HEADER* header = getBlockHeader(block);
		ZA_MEM_EXASSERT(header->STATE == ZA_MEM_BSTATE_OCCUPIED, "Stop just stop!!!")
		header->STATE = ZA_MEM_BSTATE_FREE;
		
		ZA_MEM_DEBUG_FILL(header);
		joinFree(header);
	}
	void MemoryManager::suggestScan()
	{
		//TODO scan the memory
	}

	/* //////////////////////////////////////////////////////////////////////////////// */
	// // Static methods //
	/* //////////////////////////////////////////////////////////////////////////////// */
	ZA_MEM_BLOCK_HEADER* MemoryManager::GetBlockHeader(void* block)
	{
		ZA_MEM_EXASSERT(block);
		ZA_ASSERT(s_Instance);
		return s_Instance->getBlockHeader(block);
	}
	bool MemoryManager::Contains(void* block)
	{
		ZA_MEM_EXASSERT(block);
		ZA_ASSERT(s_Instance);
		return s_Instance->contains(block);
	}

	void* MemoryManager::Allocate(size_t blockSize)
	{
		ZA_MEM_EXASSERT(s_Instance);
		return s_Instance->allocate(blockSize);
	}
	void MemoryManager::Free(void* block)
	{
		ZA_MEM_EXASSERT(block);
		ZA_MEM_EXASSERT(s_Instance);
		s_Instance->free(block);
	}
	void MemoryManager::SuggestScan()
	{
		ZA_MEM_EXASSERT(s_Instance);
		s_Instance->suggestScan();
	}
}}
