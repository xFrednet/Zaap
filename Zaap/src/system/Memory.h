#pragma once

#include "Za.h"
#include "MemoryManager.h"

#pragma warning(push)
#pragma warning(disable: 4595)

#pragma region global new operator
inline void* operator new(size_t size) 
{
	return malloc(size);
}
inline void* operator new[](size_t size)
{
	return malloc(size);
}

#pragma endregion 
#pragma region global delete operator 
inline void operator delete(void* block) 
{
	free(block);
}
inline void operator delete[](void* block)
{
	free(block);
}
#pragma endregion 

#include "za_ptr.h"

#pragma region zanew
/* //////////////////////////////////////////////////////////////////////////////// */
// // zanew //
/* //////////////////////////////////////////////////////////////////////////////// */

/* ********************************************************* */
// * zanew for za_ptr  *
/* ********************************************************* */

/**
 * \brief This values is casted into a za_ptr to assist with object generation
 */
static void* _za_ptr_buffer = malloc(sizeof(zaap::system::ZA_MEM_LOCATION*));

/**
* \brief This is a dummy function that is needed but should never be used. If you are reading this
*        you are either very interested in the inner working or something went wrong.
* \return a nullptr.
*/
template <typename T, typename... Args>
ZAAP_API inline zaap::system::ZA_MEM_LOCATION* zanew(T* za_ptr, Args&&... args)
{
	return nullptr;
}
/**
* \brief This is a dummy function that is needed however it should never be used. If you are reading this
*        you are either very interested in the inner working or something went wrong.
* \return a nullptr.
*/
template <typename T>
ZAAP_API inline zaap::system::ZA_MEM_LOCATION* zanew(T* za_ptr)
{
	return nullptr;
}

/**
* \brief This function allocates memory for an object T array and initializes every object with the given arguments.
* 
*        The added arguments after the za_ptr are put into the constructor of every array member.
*
*        The returned pointer should be passed into a za_ptr for easy access.
*
*        This returns a null if the requested length is 0. 
*
* \tparam T        This is the type of the wrapped object.
* \tparam Args     These are the extra arguments that will be passed into the constructors of objects.
*
* \param za_ptr    A util argument to get the object T from the smart pointer.
* \param length    The length of the array that should be allocated.
* \param args      These are the extra arguments that will be passed into the constructor of object T.
*
* \return          This returns a pointer to a ZA_MEM_LOCATION it should/can be passed into a za_ptr for easy access.
*/
template <typename T, typename... Args>
ZAAP_API inline zaap::system::ZA_MEM_LOCATION* zanewA(zaap::za_ptr_<T>* za_ptr, unsigned length, Args&&... args)
{
	if (length == 0)
		return nullptr;

	zaap::system::ZA_MEM_LOCATION* tLoc = zaap::system::MemoryManager::Allocate(sizeof(T) * length);

	for (unsigned i = 0; i < length; i++) {
		new(tLoc->MEM_BLOCK) T(args...);
	}
	return tLoc;
}

/**
* \brief This function allocates memory for an object T array and initializes every object without any arguments.
*
*        The returned pointer should be passed into a za_ptr for easy access.
*
*        This returns a null if the requested length is 0. 
*
* \tparam T        This is the type of the wrapped object.
*
* \param za_ptr    A util argument to get the object T from the smart pointer.
* \param length    The length of the array that should be allocated.
*
* \return          This returns a pointer to a ZA_MEM_LOCATION it should/can be passed into a za_ptr for easy access.
*/
template <typename T>
ZAAP_API inline zaap::system::ZA_MEM_LOCATION* zanewA(zaap::za_ptr_<T>* za_ptr, unsigned length)
{
	if (length == 0)
		return nullptr;

	zaap::system::ZA_MEM_LOCATION* tLoc = zaap::system::MemoryManager::Allocate(sizeof(T) * length);

	for (unsigned i = 0; i < length; i++) {
		new(tLoc->MEM_BLOCK) T();
	}
	return tLoc;
}

/**
* \brief This function allocates memory for object T and initializes the object.
*
*        The added arguments after the za_ptr are put into the constructor of the wrapped object T.
*
*        The returned pointer should be passed into a za_ptr for easy access.
*
* \tparam T        This is the type of the wrapped object.
* \tparam Args     These are the extra arguments that will be passed into the constructor of object T.
*
* \param za_ptr    A util argument to get the object T from the smart pointer.
* \param args      These are the arguments that will be passed into the constructor of object T.
*
* \return          This returns a pointer to a ZA_MEM_LOCATION it should/can be passed into a za_ptr for easy access.
*/
template <typename T, typename... Args>
ZAAP_API inline zaap::system::ZA_MEM_LOCATION* zanew(zaap::za_ptr_<T>* za_ptr, Args&&... args)
{
	return zanewA(za_ptr, 1, args...);
}
/**
* \brief This function allocates memory for object T and initializes the object with it's default constructor.
*
*        The returned pointer should be passed into a za_ptr for easy access.
*
* \tparam T        This is the type of the wrapped object.
*
* \param za_ptr    A util argument to get the object T from the smart pointer.
*
* \return          This returns a pointer to a ZA_MEM_LOCATION it should/can be passed into a za_ptr for easy access.
*/
template <typename T>
ZAAP_API inline zaap::system::ZA_MEM_LOCATION* zanew(zaap::za_ptr_<T>* za_ptr)
{
	return zanewA(za_ptr, 1);
}

/* ********************************************************* */
// * zanew general  *
/* ********************************************************* */

//TODO look and correct the rest of the documentation

/**
* \brief This function allocates memory for object T array and initializes the objects with the given arguments. The
*        allocated and initialized memory is returned in the form of a double pointer.
*
*        Use za_del and the reference to call the destructor.
*
*        The double pointer should be keep this way or it should be wrapped in to a za_ptr for easy access.
*
*        If the function used to create a za_ptr it will crate the wrapped objects and initialize them with the given arguments.
*        It will return a double pointer to the za_ptr. The pointer location will be overridden so it should be passed into a normal za_ptr
*        immediately it'll deal with it.
*
* \tparam T        The object type of the array.
* \tparam Args     The types of the arguments for the object constructor.
*
* \param length    The length of the object array.
* \param args      These arguments are passed into every constructor in the array. The arguments can be left empty.
*
* \return          The double pointer for the object. (If the object is a za_ptr it passed into a normal za_ptr immediately)
*/
template <typename T, typename... Args>
ZAAP_API inline zaap::system::ZA_MEM_LOCATION* zanewA(unsigned length, Args&&... args)
{
	if (length == 0)
		return nullptr;

	if (std::is_base_of<zaap::za_ptr_base, T>::value) {
		return zanewA((T*)&_za_ptr_buffer, length, args...);
	}
	zaap::system::ZA_MEM_LOCATION* tLoc = zaap::system::MemoryManager::Allocate(sizeof(T) * length);

	for (unsigned i = 0; i < length; i++) {
		new(tLoc->MEM_BLOCK) T(args...);
	}
	return tLoc;
}
template <typename T>
ZAAP_API inline zaap::system::ZA_MEM_LOCATION* zanewA(unsigned length)
{
	if (length == 0)
		return nullptr;

	if (std::is_base_of<zaap::za_ptr_base, T>::value) {
		return zanewA((T*)&_za_ptr_buffer, length);
	}
	zaap::system::ZA_MEM_LOCATION* tLoc = zaap::system::MemoryManager::Allocate(sizeof(T) * length);

	for (uint i = 0; i < length; i++) {
		new(tLoc->MEM_BLOCK) T();
	}
	return tLoc;
}

/**
* \brief This function allocates memory for object T and initializes the object with the given arguments. The
*        allocated and initialized memory is returned in the form of a double pointer.
*
*        Use za_del and the reference to call the destructor.
*
*        The double pointer should be keep this way or it should be wrapped in to a za_ptr for easy access.
*
*        If the function used to create a za_ptr it will crate the wrapped object and initialize it with the given arguments.
*        It will return a double pointer to the za_ptr. The pointer location will be overridden so it should be passed into a normal za_ptr
*        immediately it'll deal with it.
*
* \tparam T        The object type.
* \tparam Args     The types of the arguments for the object constructor.
*
* \param args      These arguments are passed into the constructor. The arguments can be left empty.
*
* \return          The double pointer for the object. (If the object is a za_ptr it passed into a normal za_ptr immediately)
*/
template <typename T, typename... Args>
ZAAP_API inline zaap::system::ZA_MEM_LOCATION* zanew(Args&&... args)
{
	return zanewA<T>(1, args...);
}
template <typename T>
ZAAP_API inline zaap::system::ZA_MEM_LOCATION* zanew()
{
	return zanewA<T>(1);
}

#pragma endregion 
#pragma region zadel
/* //////////////////////////////////////////////////////////////////////////////// */
// // zadel //
/* //////////////////////////////////////////////////////////////////////////////// */
template <typename T>
ZAAP_API inline void zadel(T* t)
{
	zaap::system::ZA_MEM_BLOCK_HEADER* header = zaap::system::MemoryManager::GetBlockHeader(t);
	for (unsigned i = 0; i < header->SIZE / sizeof(T); i++)
		delete (T*)(&t[i]), 0;

	zaap::system::MemoryManager::Free(t);
}
template <typename T>
ZAAP_API inline void zadel(zaap::za_ptr_<T> t)
{
	zadel(t.get());
}
#pragma endregion 

#pragma warning(pop)
