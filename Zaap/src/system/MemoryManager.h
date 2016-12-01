#pragma once

#include <Common.h>

#ifndef ZA_MEMORY_POOLSIZE
#	define ZA_MEMORY_POOLSIZE 32
#endif

namespace zaap {

	/*
	If the free-store hasn't been created yet, create the free-store,
	and then go to step 3.
    If the free-store has been exhausted, create a new free-store.
    Return the first element of the free-store and mark the next element of the free-store as the free-store head. 

The following is the pseudocode for the memory deletion:

    Make the next field in the deleted pointer point to the current free-store head.
    Mark the deleted pointer as the free-store head 
	*/

	class ZAAP_API MemoryManager
	{
	//
	// Static trash
	//
	private:
		static MemoryManager* s_Instance;
	public:
		static void* Allocate(size_t size);
		static void  Free(void* pointer);

	//
	// Class stuff
	//
	private:
		struct ZA_FreeStore
		{
			ZA_FreeStore* next;
		};

		ZA_FreeStore* m_FreeStoreHead;
	public:
		MemoryManager();

	private:
		void expandPoolSize();
		void cleanUp();
	private:
		void* allocate(const size_t& size);
		void  free(void* pointer);

	};

	inline ZAAP_API void* operator new (size_t size)
	{
		return MemoryManager::Allocate(size);
	}
	inline ZAAP_API void* operator new[](size_t size)
	{
		return MemoryManager::Allocate(size);
	}

	inline ZAAP_API void operator delete (void* pointerToDelete)
	{
		MemoryManager::Free(pointerToDelete);
	}
	inline ZAAP_API void operator delete[](void* arrayToDelete)
	{
		MemoryManager::Free(arrayToDelete);
	}
}
