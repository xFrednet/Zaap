#include "Memory.h"
#include "MemoryManager.h"

void* operator new(size_t size)
{
	return zaap::system::MemoryManager::GetStaticInstance()->allocate(size);
}
void* operator new[](size_t size)
{
	return zaap::system::MemoryManager::GetStaticInstance()->allocate(size);
}


void operator delete(void* block)
{
	zaap::system::MemoryManager::GetStaticInstance()->free(block);
}
void operator delete[](void* block)
{
	zaap::system::MemoryManager::GetStaticInstance()->free(block);
}
