#pragma once

#include "Za.h"
#include "MemoryManager.h"

#pragma warning(push)
#pragma warning(disable : 4595)

//TODO Okay if you know how I can use the MemoryManager to allocate memory without getting an error please, PLEASE tell me!!!! 
//At this point I give up and wait for the feature that enables me to do this

/*inline void* operator new  (size_t size)
{
	return zaap::system::MemoryManager::GetStaticInstance()->allocate(size);
}
inline void* operator new[](size_t size)
{
	return zaap::system::MemoryManager::GetStaticInstance()->allocate(size);
}

inline void operator delete(void* block)
{
	zaap::system::MemoryManager::GetStaticInstance()->free(block);
}
inline void operator delete[](void* block)
{
	zaap::system::MemoryManager::GetStaticInstance()->free(block);
}*/

#pragma warning(pop)

#include "za_ptr.h"

