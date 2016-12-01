#include "MemoryManager.h"
#include <maths/Vec4.h>

namespace zaap
{
	// totally not copping from
	//https://www.ibm.com/developerworks/aix/tutorials/au-memorymanager/#N10203
	
	//
	// Static trash
	//
	MemoryManager* MemoryManager::s_Instance = new MemoryManager();

	void* MemoryManager::Allocate(size_t size)
	{
		return s_Instance->allocate(size);
	}
	void MemoryManager::Free(void* pointer)
	{
		s_Instance->free(pointer);
	}

	//
	// Constructor
	//
	MemoryManager::MemoryManager()
		: m_FreeStoreHead(nullptr)
	{
	}

	//
	// Private util methods
	//
	void MemoryManager::expandPoolSize()
	{
		size_t size = (sizeof(Vec4) > sizeof(ZA_FreeStore*)) ? 
			sizeof(Vec4) : sizeof(ZA_FreeStore*);

		ZA_FreeStore* head = reinterpret_cast<ZA_FreeStore*>(new char[size]);
		m_FreeStoreHead = head;

		for (int i = 0; i < ZA_MEMORY_POOLSIZE; i++)
		{
			head->next = reinterpret_cast <ZA_FreeStore*> (new char[size]);
			head = head->next;
		}

		head->next = 0;
	}
	void MemoryManager::cleanUp()
	{
		ZA_FreeStore* nextPtr = m_FreeStoreHead;

		for (; nextPtr; nextPtr = m_FreeStoreHead)
		{
			m_FreeStoreHead = m_FreeStoreHead->next;
			delete[] nextPtr;
		}
	}

	void* MemoryManager::allocate(const size_t& size)
	{
		if (!m_FreeStoreHead)
			expandPoolSize();

		ZA_FreeStore* head = m_FreeStoreHead;
		m_FreeStoreHead = head->next;
		return head;
	}
	void MemoryManager::free(void* pointer)
	{
		ZA_FreeStore* head = static_cast<ZA_FreeStore*>(pointer);
		head->next = m_FreeStoreHead;
		m_FreeStoreHead = head;
	}
}
