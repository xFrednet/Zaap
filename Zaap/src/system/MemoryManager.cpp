#include "MemoryManager.h"

#include "util/Log.h"

#ifdef ZA_OS_WINDOWS
#	include <malloc.h>
#elif ZA_OS_LINUX
#	include <stdlib.h>
#endif


/* //////////////////////////////////////////////////////////////////////////////// */
// // Macros //
/* //////////////////////////////////////////////////////////////////////////////// */

/* ********************************************************* */
// * patterns *
/* ********************************************************* */
#define ZAAP_MEM_CLEAR_TEST_BUFFER_PATTERN       0x00
#define ZAAP_MEM_TEST_BUFFER_PATTERN             0xdd
#define ZAAP_MEM_ALIGN_PATTERN                   0xee
#define ZAAP_MEM_END_PATTERN                     0xff

/* ********************************************************* */
// * Util macros *
/* ********************************************************* */
#define ZAAP_MEM_FILL_ZERO(header)               memset((void*)((uintptr_t)header + sizeof(ZA_MEM_BLOCK_HEADER)), 0x00, header->Size)
#define ZAAP_MEM_FILL_TEST_BUFFER(header)        memset(header->TestBuffer, ZAAP_MEM_TEST_BUFFER_PATTERN, ZAAP_MEM_TEST_BUFFER_SIZE)
#define ZAAP_MEM_CLEAR_TEST_BUFFER(header)       memset(header->TestBuffer, ZAAP_MEM_CLEAR_TEST_BUFFER_PATTERN, ZAAP_MEM_TEST_BUFFER_SIZE)
#define ZAAP_MEM_ALIGN_VALUE(value)              if (value % ZAAP_MEM_BLOCK_HEADER_ALIGNMENT) {value += ZAAP_MEM_BLOCK_HEADER_ALIGNMENT - (value % ZAAP_MEM_BLOCK_HEADER_ALIGNMENT);}

#define intptr(x)                                ((intptr_t)x)
#define uintptr(x)                               ((uintptr_t)x)

/* ********************************************************* */
// * end buffer *
/* ********************************************************* */
#ifdef ZA_DEBUG_BUILD
#	define ZAAP_MEM_END_BUFFER_SIZE          (ZAAP_MEM_BLOCK_HEADER_ALIGNMENT * 4)
#	define ZAAP_MEM_FILL_END_BUFFER(header)  memset(/*pointer = end position - end buffer size*/\
	(void*)((intptr(header) + sizeof(ZA_MEM_BLOCK_HEADER) + header->Size) - ZAAP_MEM_END_BUFFER_SIZE), \
	ZAAP_MEM_END_PATTERN, ZAAP_MEM_END_BUFFER_SIZE)//Trust me this should work ;P
#	define ZAAP_MEM_IS_END_BUFFER_INTACT(header)  (memcmp(/*pointer = end position - end buffer size*/\
	(void*)((intptr(header) + sizeof(ZA_MEM_BLOCK_HEADER) + header->Size) - ZAAP_MEM_END_BUFFER_SIZE), \
	end_test_buffer, ZAAP_MEM_END_BUFFER_SIZE) == 0)
#else
#	define ZAAP_MEM_END_BUFFER_SIZE                  0
#	define ZAAP_MEM_FILL_END_BUFFER(header)          
#	define ZAAP_MEM_IS_END_BUFFER_INTACT(header)     true
#endif

/* ********************************************************* */
// * Debug and logging macros *
/* ********************************************************* */
#ifdef ZAAP_MEM_DEBUG
#	define ZA_MEM_INFO(...)                      ZA_INFO(__VA_ARGS__)
#	define ZA_MEM_ALERT(...)                     ZA_ALERT(__VA_ARGS__)
#	define ZA_MEM_ERROR(...)                     ZA_ERROR(__VA_ARGS__)

#	define ZAAP_MEM_DEBUG_CODE(x)                x
#	define ZA_MEM_EXASSERT(...)                  ZA_ASSERT(__VA_ARGS__)
#else
#	define ZA_MEM_INFO(...)
#	define ZA_MEM_ALERT(...)
#	define ZA_MEM_ERROR(...)

#	define ZAAP_MEM_DEBUG_CODE(x)
#	define ZA_MEM_EXASSERT(...)
#endif

//extra checks, these will slow down the process. They are only used for debugging.
#ifdef ZAAP_MEM_LOG_TO_MUCH
#	define ZA_MEM_EXINFO(...)                    ZA_MEM_INFO(__VA_ARGS__)
#else
#	define ZA_MEM_EXINFO(...)
#endif

/* //////////////////////////////////////////////////////////////////////////////// */
// // definitions //
/* //////////////////////////////////////////////////////////////////////////////// */
using namespace std;
namespace zaap { namespace system {

	static mm_byte head_test_buffer[ZAAP_MEM_TEST_BUFFER_SIZE] = { ZAAP_MEM_TEST_BUFFER_PATTERN };
	static mm_byte end_test_buffer[ZAAP_MEM_TEST_BUFFER_SIZE] = { ZAAP_MEM_TEST_BUFFER_PATTERN };

	/* //////////////////////////////////////////////////////////////////////////////// */
	// // aligned_malloc //
	/* //////////////////////////////////////////////////////////////////////////////// */
#ifdef ZA_OS_WINDOWS
	void* za_aligned_malloc(size_t size, size_t alignment)
	{
		return _aligned_malloc(size, alignment);
	}
	void za_aligned_free(void* block)
	{
		_aligned_free(block);
	}
#elif ZA_OS_LINUX
	void* za_aligned_malloc(size_t size, size_t alignment)
	{
		ZA_MEM_ALIGN_ALIGNMENT(alignment);
		ZA_MEM_ALIGN_INT(size, alignment);
		
		void* ptr;
		if (posix_memalign(&ptr, alignment, size) != 0)
			return nullptr;

		return ptr;
	}
	void za_aligned_free(void* block)
	{
		free(block);
	}
#else
#	error Zaap ERROR : "za_aligned_malloc" and "za_aligned_free" aren't implemented for the current compiler!!
	void* za_aligned_malloc(size_t size, size_t alignment) {return nullptr;}
	void za_aligned_free(void* block) {}
#endif

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
		: m_PartialFilledPools(nullptr),
		m_FilledPools(nullptr),
		m_AllocHeader(nullptr)
	{
		memset(head_test_buffer, ZAAP_MEM_TEST_BUFFER_PATTERN, ZAAP_MEM_TEST_BUFFER_SIZE);
		memset(end_test_buffer, ZAAP_MEM_END_PATTERN, ZAAP_MEM_END_BUFFER_SIZE);

		m_PartialFilledPools = CreatePool(ZA_MEM_FIRST_POOL_SIZE);
		if (!m_PartialFilledPools)
		{
			ZA_ASSERT(false, "The memory pool allocation failed!!!");
			exit(ZA_ERROR_MEM_ALLOCATION_ERROR);
		}

		//ZA_INFO("The initialization was successful ");
		cout << "lol" << endl;
	}
	MemoryManager::~MemoryManager()
	{
		ZA_MEM_MEMORY_POOL* nextPool;

		//
		// Freeing m_PartialFilledPools
		//
		ZA_MEM_MEMORY_POOL* pool = m_PartialFilledPools;
		m_PartialFilledPools = nullptr;
		while (pool)
		{
			nextPool = pool->Next;
			DestroyPool(pool);
			pool = nextPool;
		}

		//
		// Freeing m_FilledPools
		//
		pool = m_FilledPools;
		m_FilledPools = nullptr;
		while (pool) {
			nextPool = pool->Next;
			DestroyPool(pool);
			pool = nextPool;
		}

		ZA_MEM_EXASSERT(!m_PartialFilledPools, "A new allocation was done!");
		ZA_MEM_EXASSERT(!m_FilledPools, "A new LARGE allocation was done!");

		ZA_LOG_CLEANUP();
	}

	/* //////////////////////////////////////////////////////////////////////////////// */
	// // Actual memory allocation //
	/* //////////////////////////////////////////////////////////////////////////////// */
	ZA_MEM_MEMORY_POOL* MemoryManager::CreatePool(size_t size)
	{
		//memory allocation
		ZA_MEM_MEMORY_POOL* pool = (ZA_MEM_MEMORY_POOL*)za_aligned_malloc(sizeof(ZA_MEM_MEMORY_POOL), alignof(ZA_MEM_MEMORY_POOL));
		ZA_MEM_EXASSERT(pool, "Who did this?? Oh it was you C++... If I'll ever read this I'll start hating you (even more)!!!");
		if (!pool)
			return nullptr;
		memset(pool, 0, sizeof(ZA_MEM_MEMORY_POOL));
		
		//pool memory allocation
		pool->Memory = za_aligned_malloc(size, ZAAP_MEM_BLOCK_HEADER_ALIGNMENT);
		ZA_MEM_EXASSERT(pool->Memory, "Okay, malloc we have to talk about this. HOW THE F**k?!? (size: ", size);
		if (!pool->Memory)
		{
			za_aligned_free(pool);
			return nullptr;
		}
		pool->Size = size;
		
		//inserting the first header
		ZA_MEM_BLOCK_HEADER* header = (ZA_MEM_BLOCK_HEADER*)pool->Memory;
		ZAAP_MEM_FILL_TEST_BUFFER(header);
		header->Next       = nullptr;
		header->Previous   = nullptr;
		header->State      = ZA_MEM_BLOCK_STATE_FREE;
		header->Size       = pool->Size - sizeof(ZA_MEM_BLOCK_HEADER);

		ZA_MEM_EXINFO("A new memory pool was created at: ", pool, " the memory is at: ", pool->Memory, " and has the size of: ", pool->Size);
		return pool;
	}
	void MemoryManager::DestroyPool(ZA_MEM_MEMORY_POOL* pool)
	{
		ZA_MEM_EXASSERT(pool, "Hello let me just delete this nullptr... Done :)... kys");
		if (!pool)
			return;

		if (pool->Memory)
			za_aligned_free(pool->Memory);

		za_aligned_free(pool);

		ZA_MEM_EXINFO("A memory pool was killed, the crime scene is: ", pool);
	}

	/* //////////////////////////////////////////////////////////////////////////////// */
	// // Utilities //
	/* //////////////////////////////////////////////////////////////////////////////// */
	ZA_MEM_MEMORY_POOL* MemoryManager::getContainingPool(void const* block)
	{
		//m_PartialFilledPools
		ZA_MEM_MEMORY_POOL* pool = m_PartialFilledPools;
		for (; pool && !pool->isMember(block); pool = pool->Next) {}
		if (pool)
			return pool;

		//m_FilledPools
		pool = m_FilledPools;
		for (; pool && !pool->isMember(block); pool = pool->Next) {}

		return pool;
	}
	ZA_MEM_MEMORY_POOL const* MemoryManager::getContainingPool(void const* block) const
	{
		//m_PartialFilledPools
		ZA_MEM_MEMORY_POOL* pool = m_PartialFilledPools;
		for (; pool && !pool->isMember(block); pool = pool->Next) {}
		if (pool)
			return pool;

		//m_FilledPools
		pool = m_FilledPools;
		for (; pool && !pool->isMember(block); pool = pool->Next) {}

		return pool;
	}
	
	ZA_MEM_BLOCK_HEADER* MemoryManager::getBlockHeader(void const* block)
	{
		ZA_MEM_EXASSERT(contains(block), ":) just smile. It's all you've got left when you read this");

		ZA_MEM_MEMORY_POOL* pool = getContainingPool(block);

		//general test
		if (!pool)
			return nullptr;

		//default header location
		intptr_t searchPos = intptr(block) - sizeof(ZA_MEM_BLOCK_HEADER);
		
		if (searchPos % ZAAP_MEM_BLOCK_HEADER_ALIGNMENT)
			searchPos += ZAAP_MEM_BLOCK_HEADER_ALIGNMENT - searchPos % ZAAP_MEM_BLOCK_HEADER_ALIGNMENT;

		for (; searchPos >= intptr(pool->Memory); searchPos -= ZAAP_MEM_BLOCK_HEADER_ALIGNMENT) {
			if (memcmp((void*)searchPos, head_test_buffer, ZAAP_MEM_TEST_BUFFER_SIZE) == 0)
			{
#ifdef ZA_DEBUG_BUILD
				ZA_MEM_BLOCK_HEADER* head = (ZA_MEM_BLOCK_HEADER*)searchPos;
				if (uintptr(block) >= uintptr(head) + sizeof(ZA_MEM_BLOCK_HEADER) + head->Size)
				{
					cout << "The test buffer of the block seams to be damaged!!!" << endl;
					ZA_ASSERT_BREAK;
				}
#endif
				return (ZA_MEM_BLOCK_HEADER*)searchPos;
			}
		}

		return nullptr;
	}

	void MemoryManager::split(ZA_MEM_BLOCK_HEADER* header, size_t minBlockSize)
	{
		ZA_MEM_EXASSERT(contains(header), "<insert a funny and depressed debug message>");
		ZA_MEM_EXASSERT(header->Size > minBlockSize, "WTF you can't make it bigger by splitting it");
		ZA_MEM_EXASSERT((minBlockSize % ZAAP_MEM_BLOCK_HEADER_ALIGNMENT) == 0, "You are fired!!! Please contact me to get you fired. (I hope I'll never get this message myself)");

		if (header->Size > (minBlockSize + sizeof(ZA_MEM_BLOCK_HEADER) + ZA_MEM_BLOCK_MIN_SPLIT_SIZE))
		{
			ZA_MEM_BLOCK_HEADER* splitHeader = (ZA_MEM_BLOCK_HEADER*)(uintptr(header) + sizeof(ZA_MEM_BLOCK_HEADER) + minBlockSize);
			ZA_MEM_EXASSERT((uintptr(header) % ZAAP_MEM_BLOCK_HEADER_ALIGNMENT) == 0, "//TODO remove this test message");
			ZAAP_MEM_FILL_TEST_BUFFER(splitHeader);
			splitHeader->Previous = header;
			splitHeader->Next = header->Next;
			splitHeader->State = ZA_MEM_BLOCK_STATE_FREE;
			splitHeader->Size = header->Size - (minBlockSize + sizeof(ZA_MEM_BLOCK_HEADER));

			header->Size = minBlockSize;
			header->Next = splitHeader;

			joinFree(splitHeader);
			ZA_MEM_EXINFO("I split a MemHeader. The new size is: ", header->SIZE, ". The other split header has a size of: ", splitHeader->SIZE, "(header: ", intptr(header), ")");
		}
	}
	void MemoryManager::joinFree(ZA_MEM_BLOCK_HEADER* header)
	{
		ZA_MEM_EXASSERT(contains(header), "Off with his not existing head.");
		ZA_MEM_EXASSERT(header->State == ZA_MEM_BLOCK_STATE_FREE, "The state should be free!! should is the important word here");

		mm_byte positions = 0;
		if (header->Previous)
			positions |= header->Previous->State << 4; //0000 0000 => 000S 0000 (S = State)
		if (header->Next)
			positions |= header->Next->State;          //0000 0000 => 0000 000S (S = State)
		
		//the test buffer of the joined headers aren't cleared but that shouldn't matter

		ZA_MEM_BLOCK_HEADER* prevHeader;
		ZA_MEM_BLOCK_HEADER* nextHeader;
		switch (positions)
		{
		// |O|F|F| => |O|F--|
		case 0x01: 
			nextHeader = header->Next;
			ZAAP_MEM_CLEAR_TEST_BUFFER(nextHeader);

			header->Next = nextHeader->Next;
			header->Size = header->Size + sizeof(ZA_MEM_BLOCK_HEADER) + nextHeader->Size;

			m_AllocHeader = header;
			ZA_MEM_EXINFO("joinFree: joined |O|F|F| => |O|F--|");
			break;
		// |F|F|O| => |F--|O|
		case 0x10:
			prevHeader = header->Previous;
			ZAAP_MEM_CLEAR_TEST_BUFFER(header);

			prevHeader->Next = header->Next;
			prevHeader->Size = prevHeader->Size + sizeof(ZA_MEM_BLOCK_HEADER) + header->Size;

			m_AllocHeader = prevHeader;
			ZA_MEM_EXINFO("joinFree: joined |F|F|O| => |F--|O|");
			break;
		// |F|F|F| => |F----|
		case 0x11:
			prevHeader = header->Previous;
			nextHeader = header->Next;
			ZAAP_MEM_CLEAR_TEST_BUFFER(header);
			ZAAP_MEM_CLEAR_TEST_BUFFER(nextHeader);

			prevHeader->Next = nextHeader->Next + 
				sizeof(ZA_MEM_BLOCK_HEADER) + header->Size + 
				sizeof(ZA_MEM_BLOCK_HEADER) + nextHeader->Size;

			m_AllocHeader = prevHeader;
			ZA_MEM_EXINFO("joinFree: joined |F|F|F| => |F----|");
			break;
		default:
			return;
		}
	}

	/* //////////////////////////////////////////////////////////////////////////////// */
	// // Allocation and deallocation of memory //
	/* //////////////////////////////////////////////////////////////////////////////// */
	void* MemoryManager::allocateSinglePool(size_t size)
	{
		size += ZAAP_MEM_END_BUFFER_SIZE;
		ZAAP_MEM_ALIGN_VALUE(size);
		size += sizeof(ZA_MEM_BLOCK_HEADER);       //add size for the ZA_MEM_BLOCK_HEADER


		ZA_MEM_MEMORY_POOL* pool = CreatePool(size);
		ZA_MEM_BLOCK_HEADER* header = (ZA_MEM_BLOCK_HEADER*)pool->Memory;
		ZA_MEM_EXASSERT((uintptr(header) % ZAAP_MEM_BLOCK_HEADER_ALIGNMENT) == 0, "//TODO remove this test message 2");
		header->State = ZA_MEM_BLOCK_STATE_OCCUPIED;

		pool->Next = m_FilledPools;
		m_FilledPools = pool;


		ZAAP_MEM_FILL_END_BUFFER(header);
		return (void*)(intptr(header) + sizeof(ZA_MEM_BLOCK_HEADER));
	}
	
	void* MemoryManager::allocate(size_t size)
	{
		ZAAP_MEM_ALIGN_VALUE(size);

		if (size >= ZA_MEM_DEFAULT_POOL_SIZE)
			return allocateSinglePool(size);
		
		size += ZAAP_MEM_END_BUFFER_SIZE;

		//scan the alloc header
		ZA_MEM_BLOCK_HEADER* header = m_AllocHeader;
		while (header)
		{
			if (header->State == ZA_MEM_BLOCK_STATE_FREE && header->Size >= size)
			{
				header->State = ZA_MEM_BLOCK_STATE_OCCUPIED;
				break;
			}

			header = header->Next;
		}
		
		//scan the pools
		if (!header)
		{
			ZA_MEM_MEMORY_POOL* pool = m_PartialFilledPools;
			while (pool && !header)
			{
				header = (ZA_MEM_BLOCK_HEADER*)pool->Memory;
				while (header)
				{
					if (header->State == ZA_MEM_BLOCK_STATE_FREE && header->Size >= size) {
						header->State = ZA_MEM_BLOCK_STATE_OCCUPIED;
						break;
					}
					header = header->Next;
				}
				pool = pool->Next;
			}
		}
		
		//allocate a new pool
		if (!header)
		{
			ZA_MEM_MEMORY_POOL* pool = CreatePool();
			if (!pool)
			{
				ZA_MEM_EXASSERT(pool, "NÜLL but why!!!");
				return nullptr;
			}
			header = (ZA_MEM_BLOCK_HEADER*)pool->Memory;

			//add the pool to the pool list
			ZA_MEM_MEMORY_POOL* poolList = m_PartialFilledPools;
			while (poolList->Next)
				poolList = poolList->Next;

			poolList->Next = pool;
		}

		split(header, size);
		m_AllocHeader = header->Next;
		ZAAP_MEM_FILL_END_BUFFER(header);

		return (void*)(intptr(header) + sizeof(ZA_MEM_BLOCK_HEADER));
		//Fuck my life... I thought that would be easy
		//now I rewrote it a second time...
	}
	void MemoryManager::free(void* block)
	{
		ZA_MEM_EXASSERT(block, "Null why would you give me a nullptr?? What have I done to you");
		ZA_MEM_EXASSERT(contains(block));

		//Block head
		ZA_MEM_BLOCK_HEADER* header = getBlockHeader(block);
		ZA_MEM_EXASSERT(header, "He has no head")
		if (header)
		{
			ZA_MEM_EXASSERT(header->State == ZA_MEM_BLOCK_STATE_OCCUPIED, "Stop just stop!!!")
			if (!ZAAP_MEM_IS_END_BUFFER_INTACT(header))
			{
				std::cout << "The memory outside this allocation was touched by something!" << std::endl;
				ZA_ASSERT_BREAK;
				exit(ZA_ERROR_MEM_ACCESS_VIOLATION);
			}

			header->State = ZA_MEM_BLOCK_STATE_FREE;

			joinFree(header);
		}

	}

}}
