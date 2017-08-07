#pragma once

#include "Za.h"

namespace zaap
{
	template <typename T>
	class ZAPtrWrapper;

	template <typename T>
	inline ZAPtrWrapper<T>** zanewZaPtr(ZAPtrWrapper<T>* ptr);

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
		template <typename T>
		friend ZAPtrWrapper<T>** zanewZaPtr(ZAPtrWrapper<T>* ptr);
		
	private:
		T** m_Object;
		
	public:
		typedef T Type;
		
		ZAPtrWrapper(T** t = nullptr)
			: ZAPtrWrapperBase(),
			m_Object(t)
		{
			
		}
		ZAPtrWrapper(ZAPtrWrapper<T>** tWraped)
			: ZAPtrWrapper((*(*tWraped)).getLoc())
		{

		}

		inline operator bool() const 
		{
			return (m_Object != nullptr);
		}
		bool operator!() const 
		{
			return (m_Object == nullptr);
		}


		/**
		 * \brief This returns the location pointer for the wrapped object. It can be casted to a struct called 
		 *        ZA_MEM_LOCATION it is defined in the MemoryManager file.
		 *        
		 *        Note: These methods don't check if the pointer or object is valid.
		 * \return This returns the location pointer for the wrapped object.
		 */
		inline T** getLoc()
		{
			return m_Object;
		}
		/**
		 * \brief This returns the location pointer for the wrapped object. It can be casted to a struct called
		 *        ZA_MEM_LOCATION it is defined in the MemoryManager file.
		 *        
		 *        Note: These methods don't check if the pointer or object is valid.
		 * \return This returns the location pointer for the wrapped object.
		 */
		inline T const* const* getLoc() const
		{
			return m_Object;
		}
		
		/**
		 * \brief This resolves the current location of the object and returns a pointer to it.
		 * 
		 * Note: These methods don't check if the pointer or object is valid.
		 * \return The requested object.
		 */
		inline T* get()
		{
			return (m_Object) ? *m_Object : nullptr;
		}
		/**
		 * \brief This resolves the current location of the object and returns a pointer to it.
		 * 
		 * Note: These methods don't check if the pointer or object is valid.
		 * \return The requested object.
		 */
		inline T const* get() const
		{
			return (m_Object) ? *m_Object : nullptr;
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
