#pragma once

#include "Za.h"
#include <iostream>


namespace zaap {
	namespace system {
		class MemoryManager;
		struct ZA_MEM_LOCATION_;
	}
}

namespace zaap {
	template <typename T>
	class ZAPtrWrapper;


	class ZAAP_API ZAPtrWrapperBase {
	private:
		template <typename T>
		friend class ZAPtrWrapper;

		ZAPtrWrapperBase() {};
	};

	template <typename T>
	class ZAAP_API ZAPtrWrapper : public ZAPtrWrapperBase {
	private:
		system::ZA_MEM_LOCATION_* m_ObjectLoc;

	public:
		typedef T Type;

		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Destructor //
		/* //////////////////////////////////////////////////////////////////////////////// */
	private:
		void destructObject()
		{
			if (m_ObjectLoc)
			{
				system::ZA_MEM_LOCATION_* obj = m_ObjectLoc;
				m_ObjectLoc = nullptr;

				if (m_ObjectLoc->OBJECT_ORIGIN == 0) //ZA_MEM_OBJECT_ORIGIN_UNKNOWN {
				{
					((T*)obj->MEM_BLOCK)->T::~T();
					delete m_ObjectLoc->MEM_BLOCK;
					system::MemoryManager::GetStaticInstance().returnMemLocation(obj);
				} else
				{
					zadel((T*)m_ObjectLoc->MEM_BLOCK);//zadel calls the destructor
				}

				std::cout << "ZAPtrWrapper destructObject       x_x     X_X     X_X     x_x                       " << " this " << this << std::endl;
				
			}
			
		}
	public:
		~ZAPtrWrapper()
		{
			std::cout << "~ZAPtrWrapper();                                              REFERENCE_COUNT:" << ((m_ObjectLoc) ? m_ObjectLoc->REFERENCE_COUNT : -1) << " this " << this << std::endl;

			if (m_ObjectLoc)
			{
				m_ObjectLoc->REFERENCE_COUNT--;
				if (!m_ObjectLoc->REFERENCE_COUNT) {
					destructObject();
				}
			}
		}

		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Reset methods //
		/* //////////////////////////////////////////////////////////////////////////////// */
		template <typename U>
		inline void reset(U* u)
		{
			static_assert(std::is_base_of<T, U>::value || is_same_type<U, void>::value,
				"za_ptr::reset: The entered type has to be ether <T>, a <subclass of T> or <void>");

			destructObject();

			m_ObjectLoc = system::MemoryManager::GetStaticInstance().getNewMemLocation();
			m_ObjectLoc->MEM_BLOCK = (T*)u;
			m_ObjectLoc->OBJECT_ORIGIN = 0;
			m_ObjectLoc->REFERENCE_COUNT = 1;
		}
		template <>
		inline void reset<system::ZA_MEM_LOCATION_>(system::ZA_MEM_LOCATION_* loc)
		{
			if (!loc)
				std::cout << "za_ptr::reset: This has to be on purpose. don't do this... I won't compile!!! (If this didn't happen on purpose contact me ~xFrednet)" << std::endl;

			destructObject();

			m_ObjectLoc = (system::ZA_MEM_LOCATION_*) loc;
			m_ObjectLoc->REFERENCE_COUNT = 1;
		}
		inline void reset()
		{
			reset<void>(nullptr);
		}

		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Constructors //
		/* //////////////////////////////////////////////////////////////////////////////// */
		template <typename U>
		ZAPtrWrapper(U* u)
			: ZAPtrWrapperBase()
		{
			static_assert(std::is_base_of<T, U>::value || is_same_type<U, system::ZA_MEM_LOCATION_>::value || is_same_type<U, void>::value,
				"za_ptr: The entered type has to be ether <T>, a <subclass of T>, a <ZA_MEM_LOCATION_> or <void>");

			reset<U>(u);
		}
		ZAPtrWrapper()
			: ZAPtrWrapper((void*)nullptr)
		{
		}

		ZAPtrWrapper(const ZAPtrWrapper<T>& other)
			: ZAPtrWrapperBase(),
			m_ObjectLoc(other.m_ObjectLoc)
		{
			m_ObjectLoc->REFERENCE_COUNT++;

			std::cout << "ZAPtrWrapper(const ZAPtrWrapper<T>& ptr)                      REFERENCE_COUNT:" << m_ObjectLoc->REFERENCE_COUNT << " this " << this << std::endl;
		}
		ZAPtrWrapper<T>& operator=(const ZAPtrWrapper<T>& other)
		{

			m_ObjectLoc = other.m_ObjectLoc;
			m_ObjectLoc->REFERENCE_COUNT++;

			std::cout << "ZAPtrWrapper<T>& operator=(const ZAPtrWrapper<T>& other)      REFERENCE_COUNT:" << m_ObjectLoc->REFERENCE_COUNT << " this " << this << std::endl;

			return *this;
		}


		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Access methods //
		/* //////////////////////////////////////////////////////////////////////////////// */
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
		inline T operator[](unsigned index)
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
