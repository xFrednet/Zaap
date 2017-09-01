#pragma once

#include "Za.h"
#include "Memory.h"
#include <iostream>

#ifndef ZA_MEM_PTR_USE_COUNT_PER_PAGE
#	define ZA_MEM_PTR_USE_COUNT_PER_PAGE 128
#endif

#ifndef ZA_MEM_PTR_KEEP_PTR_LOCAL
#endif

namespace zaap {

	typedef struct ZA_PTR_OBJECT_INFO_ {
		int                            UseCount;
		union
		{
			ZA_PTR_OBJECT_INFO_*   Next;
			void*                      Object;
		};
	} ZA_PTR_OBJECT_INFO;
	
	typedef struct ZA_PTR_OBJECT_INFO_PAGE_ {
		ZA_PTR_OBJECT_INFO_PAGE_* Next;
		ZA_PTR_OBJECT_INFO      ObjectInfoList[ZA_MEM_PTR_USE_COUNT_PER_PAGE];
	} ZA_PTR_OBJECT_INFO_PAGE;

	template <typename T>
	class ZAAP_API za_ptr_;
	class ZAAP_API ZaPtrHelper
	{
	private:
		template <typename T>
		friend class za_ptr_;

		ZaPtrHelper() = delete;
		
		static ZA_PTR_OBJECT_INFO_PAGE*     s_PageList;
		static ZA_PTR_OBJECT_INFO*          s_FreeObjectInfoList;

		//TODO free unused pages.
		static void AllocateNewObjectInfoPage();
		static void FreeObjectInfoPage(ZA_PTR_OBJECT_INFO_PAGE* page);
		
		static ZA_PTR_OBJECT_INFO* GetFreeObjectInfo();
		static void ReturneObjectInfo(ZA_PTR_OBJECT_INFO* info);

	};

	template <typename T>
	class ZAAP_API za_ptr_ {
	private:
	private:
		//this can / should never be null
		mutable ZA_PTR_OBJECT_INFO* m_ObjectInfo;
	public:
		typedef T Type;

		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Destructor //
		/* //////////////////////////////////////////////////////////////////////////////// */
	private:
		inline void destructObject()
		{
			if (m_ObjectInfo)
			{
				delete (T*)m_ObjectInfo->Object;

				ZaPtrHelper::ReturneObjectInfo(m_ObjectInfo);

				std::cout << "za_ptr_ destructObject       x_x     X_X     X_X     x_x                       " << " this " << this << std::endl;
			}
			
		}
		inline void decreaseUseCounter()
		{
			if (m_ObjectInfo) {
				m_ObjectInfo->UseCount--;
				if (m_ObjectInfo->UseCount == 0) {
					destructObject();
				}
			}
		}
	public:
		inline ~za_ptr_()
		{
			std::cout << "~za_ptr_();                                              REFERENCE_COUNT:" << ((m_ObjectInfo) ? m_ObjectInfo->UseCount : -1) << " this " << this << std::endl;

			decreaseUseCounter();
		}

		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Reset methods //
		/* //////////////////////////////////////////////////////////////////////////////// */
		inline void reset(T* t)
		{
			decreaseUseCounter();

			m_ObjectInfo = ZaPtrHelper::GetFreeObjectInfo();
			m_ObjectInfo->UseCount = 1; 
			m_ObjectInfo->Object = t;
		}
		inline void reset()
		{
			reset<void>(nullptr);
		}

		template <typename TSub>
		inline void reset(const za_ptr_<TSub>& other)
		{
			static_assert(is_same_type<TSub, T>::value || std::is_base_of<T, TSub>::value || is_same_type<TSub, void>::value,
				"za_ptr::reset: The entered za_ptr type must be <T>, a <subclass of T> or <void>");
			
			decreaseUseCounter();

			m_ObjectInfo = other.m_ObjectInfo; // m_ObjectInfo of other should never be null
			m_ObjectInfo->UseCount++;
		}
		
		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Constructors //
		/* //////////////////////////////////////////////////////////////////////////////// */
		inline za_ptr_(T* t)
			: m_ObjectInfo(nullptr)
		{
			reset(t);
		}
		inline za_ptr_()
			: za_ptr_((void*)nullptr)
		{
		}

		inline za_ptr_(const za_ptr_<T>& other)
			: m_ObjectInfo(nullptr)
		{
			reset(other);

			std::cout << "za_ptr_(const za_ptr_<T>& ptr)                      REFERENCE_COUNT:" << m_ObjectInfo->UseCount << " this " << this << std::endl;
		}
		inline za_ptr_<T>& operator=(const za_ptr_<T>& other)
		{
			reset(other);
			
			std::cout << "za_ptr_<T>& operator=(const za_ptr_<T>& other)      REFERENCE_COUNT:" << m_ObjectInfo->REFERENCE_COUNT << " this " << this << std::endl;

			return *this;
		}

		template <typename TSub>
		inline za_ptr_(const za_ptr_<TSub>& other)
		{
			static_assert(is_same_type<TSub, T>::value || std::is_base_of<T, TSub>::value || is_same_type<TSub, void>::value,
				"za_ptr::constructor: The type of the entered za_ptr has to be <T>, a <subclass of T> or <void>");

			reset(other);
		}
		template <typename TSub>
		inline za_ptr_<T>& operator=(const za_ptr_<TSub>& other) {
			static_assert(is_same_type<TSub, T>::value || std::is_base_of<T, TSub>::value || is_same_type<TSub, void>::value,
				"za_ptr::operator=: The type of the entered za_ptr has to be <T>, a <subclass of T> or <void>");

			reset(other);

			std::cout << "za_ptr_<TSub>& operator=(const za_ptr_<TSub>& other)      REFERENCE_COUNT:" << m_ObjectInfo->REFERENCE_COUNT << " this " << this << std::endl;

			return *this;
		}

		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Access methods //
		/* //////////////////////////////////////////////////////////////////////////////// */
		/**
		* \brief This resolves the current location of the object and returns a pointer to it.
		*
		* Note: These methods don't check if the pointer or object is valid.
		* \return The requested object.
		*/
		inline T* get()
		{
			return (T*)m_ObjectInfo->Object;
		}
		/**
		* \brief This resolves the current location of the object and returns a pointer to it.
		*
		* Note: These methods don't check if the pointer or object is valid.
		* \return The requested object.
		*/
		inline T const* get() const
		{
			return (T const*)m_ObjectInfo->Object;
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
		inline T& operator*()
		{
			return *get();
		}
		inline const T& operator*() const
		{
			return *get();
		}

		/**
		* \brief This treads the wrapped object as a array and returns the object that is stored under the requested index.
		*
		*        Note: These methods don't check if the pointer or object is valid.
		* \param index The index of the requested object.
		* \return The object that is stored under the entered index.
		*/
		inline T& operator[](unsigned index)
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
		inline const T& operator[](unsigned index) const
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
		inline T& operator[](int index)
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
		inline const T& operator[](int index) const
		{
			return get()[index];
		}

		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Operators //
		/* //////////////////////////////////////////////////////////////////////////////// */
		inline operator bool() const
		{
			return (get() != nullptr);
		}
		inline bool operator!() const
		{
			return (get() == nullptr);
		}
	};

}
