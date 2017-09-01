#pragma once

#include "Za.h"
#include "Memory.h"
#include <iostream>
#include <memory>

#ifndef ZA_MEM_PTR_USE_COUNT_PER_PAGE
#	define ZA_MEM_PTR_USE_COUNT_PER_PAGE 128
#endif

#ifndef ZA_MEM_PTR_KEEP_PTR_LOCAL
#endif

namespace zaap {

	typedef struct ZA_PTR_OBJECT_INFO_ {
		union
		{
			int                       UseCount;
			ZA_PTR_OBJECT_INFO_*  Next;
		};
	} ZA_PTR_OBJECT_INFO;
	
	typedef struct ZA_PTR_OBJECT_INFO_PAGE_ {
		ZA_PTR_OBJECT_INFO_PAGE_* Next;
		ZA_PTR_OBJECT_INFO        ObjectInfoList[ZA_MEM_PTR_USE_COUNT_PER_PAGE];
	} ZA_PTR_OBJECT_INFO_PAGE;

	template <typename T>
	class ZAAP_API za_ptr;
	class ZAAP_API ZaPtrHelper
	{
	private:
		template <typename T>
		friend class za_ptr;

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
	class ZAAP_API za_ptr {
	private:
		template <typename U>
		friend class za_ptr;
		
		//this can / should never be null
		mutable ZA_PTR_OBJECT_INFO* m_ObjectInfo;
		//having a object reference in every za_ptr is a tiny little bit faster than keeping it inside the Object info
		mutable T* m_Object;
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
				if (m_Object)
					delete (T*)m_Object;

				ZaPtrHelper::ReturneObjectInfo(m_ObjectInfo);

				std::cout << "za_ptr destructObject       x_x     X_X     X_X     x_x                       " << " this " << this << std::endl;
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
		inline ~za_ptr()
		{
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
			m_Object = t;
		}
		inline void reset()
		{
			reset<void>(nullptr);
		}

		template <typename TSub>
		inline void reset(const za_ptr<TSub>& other)
		{
			static_assert(is_same_type<TSub, T>::value || std::is_base_of<T, TSub>::value || is_same_type<TSub, void>::value,
				"za_ptr::reset: The entered za_ptr type must be <T>, a <subclass of T> or <void>");
			
			decreaseUseCounter();

			m_ObjectInfo = other.m_ObjectInfo; // m_ObjectInfo of other should never be null
			m_Object = (T*)other.m_Object;
			m_ObjectInfo->UseCount++;
		}
		
		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Constructors //
		/* //////////////////////////////////////////////////////////////////////////////// */
		inline za_ptr(T* t)
			: m_ObjectInfo(nullptr)
		{
			reset(t);
		}
		inline za_ptr()
			: za_ptr((T*)nullptr)
		{
		}

		inline za_ptr(const za_ptr<T>& other)
			: m_ObjectInfo(nullptr)
		{
			reset(other);
		}
		inline za_ptr<T>& operator=(const za_ptr<T>& other)
		{
			reset(other);
			
			return *this;
		}

		template <typename TSub>
		inline za_ptr(const za_ptr<TSub>& other)
		{
			static_assert(is_same_type<TSub, T>::value || std::is_base_of<T, TSub>::value || is_same_type<TSub, void>::value,
				"za_ptr::constructor: The type of the entered za_ptr has to be <T>, a <subclass of T> or <void>");

			reset(other);
		}
		template <typename TSub>
		inline za_ptr<T>& operator=(const za_ptr<TSub>& other) {
			static_assert(is_same_type<TSub, T>::value || std::is_base_of<T, TSub>::value || is_same_type<TSub, void>::value,
				"za_ptr::operator=: The type of the entered za_ptr has to be <T>, a <subclass of T> or <void>");

			reset(other);

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
			return m_Object;
		}
		/**
		* \brief This resolves the current location of the object and returns a pointer to it.
		*
		* Note: These methods don't check if the pointer or object is valid.
		* \return The requested object.
		*/
		inline T const* get() const
		{
			return (T const*)m_Object;
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

		inline bool operator==(void const* other) const
		{
			return m_Object == other;
		}
		inline bool operator!=(void const* other) const
		{
			return m_Object != other;
		}
		
		template <typename U>
		inline bool operator==(const za_ptr<U>& ptr)
		{
			return m_ObjectInfo == ptr.m_ObjectInfo &&
				m_Object == ptr.m_Object;
		}
		template <typename U>
		inline bool operator!=(const za_ptr<U>& ptr)
		{
			return m_ObjectInfo != ptr.m_ObjectInfo &&
				m_Object == ptr.m_Object;
		}
	};

}
