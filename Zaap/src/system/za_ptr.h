#pragma once

#include "Za.h"
#include "Types.h"                //types
#include "util/Log.h"

#include "MemoryManager.h"

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

//TODO add a release method and a linked to the next ptr

namespace zaap { namespace system {

	template<typename T>
	class ZAAP_API ZASmartPointer {
	private:
		//management
		ZA_MEM_BLOCK_HEADER* m_MemHeader;

		//the wrapped object
		T*                   m_Object; // the memory after m_MemHeader
	
	public:
		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Le constructors et le deconstructors //
		/* //////////////////////////////////////////////////////////////////////////////// */
		ZASmartPointer(T* object)
		{
			ZA_MEM_EXINFO("ZASmartPointer<T>::ZASmartPointer(T* object) was called.");

			if (m_Object)
				decreaseUseCount(); // decrease previously held use count

			//
			// new object
			//
			if (object)
			{
				m_Object = object;
				m_MemHeader = MemoryManager::GetBlockHeader(m_Object);
				
				increaseUseCount();

				ZA_MEM_EXINFO(">Object location: ", (uintptr_t)m_Object, ", ZA_MEM_BLOCK_HEADER: ", (uintptr_t)m_MemHeader);
			}
			else
			{
				m_Object = nullptr;
				m_MemHeader = nullptr;

				ZA_MEM_EXINFO(">The given object is null");
			}
		}
		ZASmartPointer(ZASmartPointer<T>& other)
		{
			ZA_MEM_EXINFO("ZASmartPointer(ZASmartPointer<T>& other) was called.");
			
			if (m_Object)
				decreaseUseCount(); // decrease previously held use count

			m_Object = other.m_Object;
			m_MemHeader = other.m_MemHeader;

			increaseUseCount();
		}
		~ZASmartPointer()
		{
			ZA_MEM_EXINFO("ZASmartPointer<T>::~ZASmartPointer() was called. {");
			if (m_MemHeader) {
				decreaseUseCount();
				ZA_MEM_EXINFO("    USE_COUNT = ", m_MemHeader->USE_COUNT);

				if (m_MemHeader->USE_COUNT == 0) {
					MemoryManager::Free(m_Object);
					ZA_MEM_EXINFO("    The object was freed");
				}
			}
		}

		/*operator bool() const;
		bool operator!() const;
		T* operator[](int index);
		T const* operator[](int index) const;*/
		
		/* //////////////////////////////////////////////////////////////////////////////// */
		// // accessing the wrapped object //
		/* //////////////////////////////////////////////////////////////////////////////// */
		inline T* get()
		{
			return m_Object;
		}
		inline T const* get() const
		{
			return m_Object;
		}

		inline T* operator->() {
			return this->get();
		}
		inline T const* operator->() const
		{
			return this->get();
		}
		
		inline T& operator*() {
			return *this->get();
		}
		inline const T& operator*() const
		{
			return *this->get();
		}

		/* //////////////////////////////////////////////////////////////////////////////// */
		// // UseCount //
		/* //////////////////////////////////////////////////////////////////////////////// */
		uint16 getUseCount() const
		{
			if (m_MemHeader)
				return m_MemHeader->USE_COUNT;
			else
				return 0;
		}

	private:
		inline void increaseUseCount()
		{
			ZA_ASSERT(!m_MemHeader || m_MemHeader->USE_COUNT != 0xffff);
			
			if (m_MemHeader)
				m_MemHeader->USE_COUNT++;
		}
		inline void decreaseUseCount()
		{
			ZA_ASSERT(!m_MemHeader || m_MemHeader->USE_COUNT != 0);
			
			if (m_MemHeader && m_MemHeader->USE_COUNT)
			{
				m_MemHeader->USE_COUNT--;
				
				if (m_MemHeader->USE_COUNT == 0)
					MemoryManager::SuggestScan(m_Object);
			}
		}
	};
}}


#undef ZA_MEM_EXINFO
#undef ZA_MEM_INFO
#undef ZA_MEM_ALERT
#undef ZA_MEM_ERROR

#undef ZA_MEM_EXASSERT
#undef ZA_MEM_DEBUG_FILL