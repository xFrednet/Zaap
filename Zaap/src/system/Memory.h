#pragma once

#include "Za.h"

void* operator new(size_t size);
void* operator new[](size_t size);

void operator delete(void* block);
void operator delete[](void* block);


#include "MemoryManager.h"
#include "za_ptr.h"

