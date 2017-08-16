#pragma once

#include "Za.h"
#include <iostream>


namespace zaap
{
	namespace system
	{
		class MemoryManager;
		struct ZA_MEM_LOCATION_;
	}
}

namespace zaap
{
	template <typename T>
	class ZAPtrWrapper;


	class ZAAP_API ZAPtrWrapperBase
	{
	private:
		template <typename T>
		friend class ZAPtrWrapper;

		ZAPtrWrapperBase() {};
	};

	template <typename T>
	class ZAAP_API ZAPtrWrapper : public ZAPtrWrapperBase
	{
	private:
		//template <typename U>
		//zaap::system::ZA_MEM_LOCATION* zanewA(uint length);

		//ZAPtrWrapper(bool initialize)
		//	: ZAPtrWrapperBase(),
		//	m_ObjectLoc(nullptr)
		//{
		//}

	private:
		system::ZA_MEM_LOCATION_* m_ObjectLoc;
		
	public:
		typedef T Type;
		
		ZAPtrWrapper(system::ZA_MEM_LOCATION_* tLoc)
			: ZAPtrWrapperBase(),
			m_ObjectLoc(tLoc)
		{
			if (!m_ObjectLoc)
			{
				m_ObjectLoc = system::MemoryManager::GetStaticInstance().getNewMemLocation();
				m_ObjectLoc->MEM_BLOCK = nullptr;
				m_ObjectLoc->OBJECT_ORIGIN = 0;
			}

			m_ObjectLoc->REFERENCE_COUNT = 1;
			std::cout << "ZAPtrWrapper(system::ZA_MEM_LOCATION_* tLoc)                  REFERENCE_COUNT:" << m_ObjectLoc->REFERENCE_COUNT << " this " << this << std::endl;
		}
		ZAPtrWrapper(T* t = nullptr)
			: ZAPtrWrapperBase()
		{
			m_ObjectLoc = system::MemoryManager::GetStaticInstance().getNewMemLocation();
			m_ObjectLoc->MEM_BLOCK = t;
			m_ObjectLoc->REFERENCE_COUNT = 1;
			m_ObjectLoc->OBJECT_ORIGIN = 0;

			std::cout << "ZAPtrWrapper(T* t = nullptr)                                  REFERENCE_COUNT:" << m_ObjectLoc->REFERENCE_COUNT << " this " << this << std::endl;
		}

		ZAPtrWrapper(const ZAPtrWrapper<T>& other)
			: ZAPtrWrapperBase(),
			m_ObjectLoc(other.m_ObjectLoc)
		{
			m_ObjectLoc->REFERENCE_COUNT++;

			std::cout << "ZAPtrWrapper(const ZAPtrWrapper<T>& ptr)                      REFERENCE_COUNT:" << m_ObjectLoc->REFERENCE_COUNT << " this " << this << std::endl;
		}
		ZAPtrWrapper<T>& operator=(const ZAPtrWrapper<T>& other) {

			m_ObjectLoc = other.m_ObjectLoc;
			m_ObjectLoc->REFERENCE_COUNT++;

			std::cout << "ZAPtrWrapper<T>& operator=(const ZAPtrWrapper<T>& other)      REFERENCE_COUNT:" << m_ObjectLoc->REFERENCE_COUNT << " this " << this << std::endl;
			
			return *this;
		}

		~ZAPtrWrapper()
		{
			std::cout << "~ZAPtrWrapper();                                              REFERENCE_COUNT:" << m_ObjectLoc->REFERENCE_COUNT << " this " << this << std::endl;
			m_ObjectLoc->REFERENCE_COUNT--;
			if (!m_ObjectLoc->REFERENCE_COUNT)
			{
				std::cout << "~ZAPtrWrapper() delete       x_x     X_X     X_X     x_x                       " << " this " << this << std::endl;
				if (m_ObjectLoc->OBJECT_ORIGIN == 0) //ZA_MEM_OBJECT_ORIGIN_UNKNOWN
					delete m_ObjectLoc->MEM_BLOCK;
				else
					zadel((T*)m_ObjectLoc->MEM_BLOCK);
			}
		}

		/*void* operator new (size_t size) = delete;
		void operator delete (void* obj) = delete;*/

		/**
		 * \brief This returns the location pointer for the wrapped object. It can be casted to a struct called 
		 *        ZA_MEM_LOCATION it is defined in the MemoryManager file.
		 *        
		 *        Note: These methods don't check if the pointer or object is valid.
		 * \return This returns the location pointer for the wrapped object.
		 */
		inline system::ZA_MEM_LOCATION_* getLoc()
		{
			return m_ObjectLoc;
		}
		/**
		 * \brief This returns the location pointer for the wrapped object. It can be casted to a struct called
		 *        ZA_MEM_LOCATION it is defined in the MemoryManager file.
		 *        
		 *        Note: These methods don't check if the pointer or object is valid.
		 * \return This returns the location pointer for the wrapped object.
		 */
		inline system::ZA_MEM_LOCATION_ const* getLoc() const
		{
			return m_ObjectLoc;
		}
		/**
		 * \brief This resolves the current location of the object and returns a pointer to it.
		 * 
		 * Note: These methods don't check if the pointer or object is valid.
		 * \return The requested object.
		 */
		inline T* get()
		{
			return (m_ObjectLoc) ? (T*)m_ObjectLoc->MEM_BLOCK : nullptr;
		}
		/**
		 * \brief This resolves the current location of the object and returns a pointer to it.
		 * 
		 * Note: These methods don't check if the pointer or object is valid.
		 * \return The requested object.
		 */
		inline T const* get() const
		{
			return (m_ObjectLoc) ? (T*)m_ObjectLoc->MEM_BLOCK : nullptr;
		}
		
		
		inline operator bool() const 
		{
			return (get() != nullptr);
		}
		bool operator!() const 
		{
			return (get() == nullptr);
		}
		
		
		/**
		 * \brief This returns the wrapped resolved object. This is the preferred way to access the object and it values. 
		 *        Simply use the pointer add a "->" and use the desired function.
		 *        
		 *        Note: These methods don't check if the pointer or object is valid.
		 * \return This return the wrapped object pointer.
		 */
		inline T* operator->() 
		{
			return get();
		}
		/**
		 * \brief This returns the wrapped resolved object. This is the preferred way to access the object and it values.
		 *        Simply use the pointer add a "->" and use the desired function.
		 *        
		 *        Note: These methods don't check if the pointer or object is valid.
		 * \return This return the wrapped object pointer.
		 */
		inline T const* operator->() const
		{
			return get();
		}

		/**
		 * \brief This treads the wrapped object as a array and returns the object that is stored under the requested index.
		 *        
		 *        Note: These methods don't check if the pointer or object is valid.
		 * \param index The index of the requested object.
		 * \return The object that is stored under the entered index.
		 */
		inline T operator[](unsigned index) {
			return get()[index];
		}
		/**
		 * \brief This treads the wrapped object as a array and returns the object that is stored under the requested index.
		 *        
		 *        Note: These methods don't check if the pointer or object is valid.
		 * \param index The index of the requested object.
		 * \return The object that is stored under the entered index.
		 */
		inline T operator[](unsigned index) const
		{
			return get()[index];
		}
		/**
		 * \brief This treads the wrapped object as a array and returns the object that is stored under the requested index.
		 *        
		 *        Note: These methods don't check if the pointer or object is valid.
		 * \param index The index of the requested object.
		 * \return The object that is stored under the entered index.
		 */
		inline T operator[](int index)
		{
			return get()[index];
		}
		/**
		 * \brief This treads the wrapped object as a array and returns the object that is stored under the requested index.
		 *        
		 *        Note: These methods don't check if the pointer or object is valid.
		 * \param index The index of the requested object.
		 * \return The object that is stored under the entered index.
		 */
		inline T operator[](int index) const
		{
			return get()[index];
		}

	};
}