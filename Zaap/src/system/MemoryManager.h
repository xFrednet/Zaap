#pragma once

#include "Za.h"
#include "Types.h"                //types
#include "util/Log.h"

#include <thread>
#include <type_traits>

#pragma region Option Macros
#ifndef ZA_MEM_FIRST_ALLOC_SIZE
#	define ZA_MEM_FIRST_CHUNK_SIZE      (256 * 1024 * 1024) //256MB
#endif

#ifndef ZA_MEM_CHUNK_SIZE
#	define ZA_MEM_CHUNK_SIZE            (16 * 1024 * 1024) //16MB
#endif

#ifndef ZA_MEM_PAGE_LOCATION_COUNT
#	 define ZA_MEM_PAGE_LOCATION_COUNT  (64 - 1) // -1 for the NEXT pointer
#endif

#ifndef ZA_MEM_BLOCK_MIN_SPLIT_SIZE
#	define ZA_MEM_BLOCK_MIN_SPLIT_SIZE  16 // plus the size of the MEM_BLOCK_HEADER
#endif

#define ZA_MEM_DEBUG_PATTERN            0xee

#pragma endregion 

//TODO implement suggestScan
//TODO move m_AllocIndex back

namespace zaap
{
	class ZAPtrWrapperBase;

	template <typename T>
	class ZAPtrWrapper;
}

namespace zaap { namespace system {

	typedef enum ZAAP_API ZA_MEM_OBJECT_ORIGIN_ : short {
		ZA_MEM_OBJECT_ORIGIN_UNKNOWN     = 0,
		ZA_MEM_OBJECT_ORIGIN_MEMMGR      = 1
	} ZA_MEM_OBJECT_ORIGIN;

	typedef enum ZAAP_API ZA_MEM_BLOCK_STATE_ {
		ZA_MEM_BLOCK_STATE_OCCUPIED = 0,
		ZA_MEM_BLOCK_STATE_FREE     = 1
	} ZA_MEM_BLOCK_STATE;

	/* //////////////////////////////////////////////////////////////////////////////// */
	// // ZA_MEM_LOCATION //
	/* //////////////////////////////////////////////////////////////////////////////// */
	typedef struct ZAAP_API ZA_MEM_LOCATION_ {
		union { //This has to be at the start of this struct
			ZA_MEM_LOCATION_* NEXT;
			void*             MEM_BLOCK;
		};

		short REFERENCE_COUNT;
		short OBJECT_ORIGIN; //ZA_MEM_OBJECT_ORIGIN_MEMMGR or ZA_MEM_OBJECT_ORIGIN_UNKNOWN
	} ZA_MEM_LOCATION;

	/* //////////////////////////////////////////////////////////////////////////////// */
	// // ZA_MEM_PAGE //
	/* //////////////////////////////////////////////////////////////////////////////// */
	typedef struct ZAAP_API ZA_MEM_PAGE_ {
		ZA_MEM_PAGE_*   NEXT;
		ZA_MEM_LOCATION LOCATIONS[ZA_MEM_PAGE_LOCATION_COUNT];
		//TODO test performance with a PREV reference
	} ZA_MEM_PAGE;

	/* //////////////////////////////////////////////////////////////////////////////// */
	// // ZA_MEM_BLOCK_HEADER //
	/* //////////////////////////////////////////////////////////////////////////////// */
	// The header that is placed in front of 
	// allocated memory blocks.
	//
	// 32 BIT 
	//     => 4 bytes per pointer 
	//
	//  Bytes 
	//  0 0 0 0 0 0 0 0 0 1 1 1 1 1 1 1 1 1 1 2
	//  1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0
	// +-------+-------+-------+-------+-+-----+
	// | PREV  | NEXT  |  LOC  | SIZE  |S|  R  |
	// +-------+-------+-------+-------+-+-----+
	//
	// PREV          :: The pointer to the previous memory block.
	// NEXT          :: The pointer to the next memory block.
	// LOC->LOCATION :: The pointer to the location.
	// SIZE          :: The size of this memory block. (without the header)
	// S->STATE      :: The state of this memory block.
	// R->RESERVED   :: This memory is reserved for the scan process(It is mostly used to align the data after this header).
	//
	typedef struct ZAAP_API ZA_MEM_BLOCK_HEADER_ {
		ZA_MEM_BLOCK_HEADER_* PREV;
		ZA_MEM_BLOCK_HEADER_* NEXT;
		ZA_MEM_LOCATION_*     LOCATION;
		uint32                SIZE;
		ZA_MEM_BLOCK_STATE    STATE; // ZA_MEM_BLOCK_STATE_OCCUPIED or ZA_MEM_BLOCK_STATE_FREE
		byte                  RESERVED[3]; //0: internal references found, 1: external references found, 2: IDK
	} ZA_MEM_BLOCK_HEADER;

	/* //////////////////////////////////////////////////////////////////////////////// */
	// // MemoryManager //
	/* //////////////////////////////////////////////////////////////////////////////// */
	class ZAAP_API MemoryManager
	{
	private:
		template <typename T>
		friend class ZAPtrWrapper;
	public:
		static MemoryManager& GetStaticInstance()
		{
			static MemoryManager instance;
			return instance;
		}
	private:
		byte* m_AllocMem;
		uint m_Size;

		//Location List
		ZA_MEM_PAGE*     m_PageList;
		ZA_MEM_LOCATION* m_FreeMemLocations;

		//This is the position the next allocation will start searching from
		ZA_MEM_BLOCK_HEADER* m_AllocHeader;

		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Initialization && Deconstruction //
		/* //////////////////////////////////////////////////////////////////////////////// */
	public:
		void* operator new(size_t sz);
		void operator delete(void* ptr);

		MemoryManager::MemoryManager();
		MemoryManager::~MemoryManager();
	
		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Actual memory allocation //
		/* //////////////////////////////////////////////////////////////////////////////// */
	private:
		bool allocMem(size_t chunkSize = ZA_MEM_FIRST_CHUNK_SIZE);
		bool allocMoreMem(size_t chunkSize = ZA_MEM_CHUNK_SIZE);
		void freeAllMem();

		void allocNewLocations();
		bool isPageUsed(ZA_MEM_PAGE* page) const;
		void freePage(ZA_MEM_PAGE* page);

		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Utilities //
		/* //////////////////////////////////////////////////////////////////////////////// */
	public:
		/**
		* \brief This method tests if the given pointer is inside the bounds of this MemoryManager
		* \param block The pointer that should be tested.
		* \return This returns whether the given pointer is inside or outside of the managed memory.
		*/
		inline bool contains(void* block) const;
		/**
		 * \brief This tries to find the ZA_MEM_BLOCK_HEADER for the given block
		 * \param block The block for the requested header.
		 * \return The found header or a nullptr.
		 */
		inline ZA_MEM_BLOCK_HEADER* getBlockHeader(void* block);
	private:
		/**
		 * \brief 
		 * This test if the given block can be split and will do this if it is possible.
		 * 
		 * Splitting:
		 *      H     = Header
		 *      BLOCK = the allocated memory.
		 *      FREE  = free memory that isn't used.
		 *
		 * case 1:
		 *      The block will be split if the leftover memory is large enough
		 *      to fit a ZA_MEM_BLOCK_HEADER with the minimal size of
		 *      ZA_MEM_BLOCK_MIN_SPLIT_SIZE.
		 *
		 *      +---+------------------+    +---+-------+---+------+
		 *      | H | BLOCK : FREE     | => | H | BLOCK | H | FREE |
		 *      +---+------------------+    +---+-------+---+------+
		 *      |<H>|<-MBS->|<--oMem-->|
		 *                  |<H>|<BMSZ>|
		 *
		 *      H    = ZA_MEM_BLOCK_HEADER, the header for the following memory block.
		 *      MBS  = minBlockSize, the minimal size of this block.
		 *      oMem = The memory that is over and can be used differently.
		 *      BMSZ = The minimal size of the split block (ZA_MEM_BLOCK_MIN_SPLIT_SIZE).
		 *
		 * case 2:
		 *      The block won't be split if the leftover memory is too small for
		 *      the ZA_MEM_BLOCK_HEADER and ZA_MEM_BLOCK_MIN_SPLIT_SIZE.
		 *
		 *      +---+--------------+    +---+--------------+
		 *      | H | BLOCK : FREE | => | H | BLOCK : FREE |
		 *      +---+--------------+    +---+--------------+
		 *      |<H>|<-MBS->|<oMem>|
		 *                  |<H>|<BMSZ>|
		 *
		 *      H    = ZA_MEM_BLOCK_HEADER, the header for the following memory block.
		 *      MBS  = minBlockSize, the minimal size of this block.
		 *      oMem = The memory that is over and can be used differently.
		 *      
		 *      |<H>|<BMSZ>| = are the minimal size of the for splitting. The free memory
		 *                     isn't large enough to fit them so the block isn't split.
		 *
		 * \param header The header that should be checked and split.
		 * \param minBlockSize The minimal size the header has to have after splitting.
		 */
		inline void split(ZA_MEM_BLOCK_HEADER* header, uint32 minBlockSize);
		/**
		 * \brief Possibilities
		 *      F = Free
		 *      O = Occupied
		 *
		 *  case 1:
		 *      +---+---+---+    +---+---+---+
		 *      | O | F | O | => | O | F | O |
		 *      +---+---+---+    +---+---+---+
		 *  case 2:
		 *      +---+---+---+    +---+---+---+
		 *      | O | F | F | => | O | F     |
		 *      +---+---+---+    +---+---+---+
		 *  case 3:
		 *      +---+---+---+    +---+---+---+
		 *      | F | F | O | => | F     | O |
		 *      +---+---+---+    +---+---+---+
		 *  case 4:
		 *       +---+---+---+    +---+---+---+
		 *      | F | F | F | => | F         |
		 *      +---+---+---+    +---+---+---+
		 *
		 * \param header The header that should be joined with his neighbors.
		 */
		inline void joinFree(ZA_MEM_BLOCK_HEADER* header);

		inline ZA_MEM_LOCATION* getNewMemLocation();
		inline void returnMemLocation(ZA_MEM_LOCATION* location);
		
		/* ********************************************************* */
		// * Scan the memory *
		/* ********************************************************* */
		/*void reportLiveAllocations();
		void scanForLifeObjects();
		void scanBlock(void* mem, size_t size);
		bool scanIsValidPointer(void* pointer);*/

		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Allocation and deallocation of memory //
		/* //////////////////////////////////////////////////////////////////////////////// */
	public:
		ZA_MEM_LOCATION* allocate(size_t blockSize);
		void free(void* block);
		void free(void** block);
		void suggestScan();
	
		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Static methods //
		/* //////////////////////////////////////////////////////////////////////////////// */
		/**
		* \brief This tries to find the ZA_MEM_BLOCK_HEADER for the given block
		* \param block The block for the requested header.
		* \return The found header or a nullptr.
		*/
		static inline ZA_MEM_BLOCK_HEADER* GetBlockHeader(void* block)
		{
			return GetStaticInstance().getBlockHeader(block);
		}
		/**
		 * \brief This method tests if the given pointer is inside the bounds of this MemoryManager.
		 * \param block The pointer that should be tested.
		 * \return This returns whether the given pointer is inside or outside of the managed memory.
		 */
		static inline bool Contains(void* block)
		{
			return GetStaticInstance().contains(block);
		}
		
		static inline ZA_MEM_LOCATION* Allocate(size_t blockSize)
		{
			return GetStaticInstance().allocate(blockSize);
		}
		static inline void Free(void* block)
		{
			GetStaticInstance().free(block);
		}
		static inline void Free(void** block)
		{
			GetStaticInstance().free(block);
		}
	};

}}

#pragma region zanew
/* //////////////////////////////////////////////////////////////////////////////// */
// // zanew //
/* //////////////////////////////////////////////////////////////////////////////// */

/* ********************************************************* */
// * zanew for za_ptr  *
/* ********************************************************* */

//TODO add documentation

static void* _za_ptr_buffer = malloc(sizeof(za_ptr_<int>));

/**
 * \brief This is a dummy function that is needed but should never be used. If you are reading this 
 *        you are either very interested in the inner working or something went wrong.
 * \return a nullptr.
 */
template <typename T, typename... Args>
ZAAP_API inline zaap::system::ZA_MEM_LOCATION* zanew(T* za_ptr, Args&&... args)
{
	ZA_ASSERT(false, "zanew was called by ",  typeid(T).name());
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
	ZA_ASSERT(false, "zanew was called by ", typeid(T).name());
	return nullptr;
}

/**
* \brief This function allocates memory for an object T array and initializes every object with the given arguments. The
*        allocated and initialized memory is returned in the form of a za_ptr.
*
*        The added arguments after the za_ptr are put into the constructor of every array member.
*
*        The returned pointer should be passed to a za_ptr it will deal with it. The returned pointer can't be kept
*        as it is because it will be overridden.
*        
* \tparam T        This is the type of the wrapped object.
* \tparam Args     These are the extra arguments that will be passed into the constructors of objects.
*                  The arguments can be left empty.
*
* \param za_ptr    The wrapper of the object that should be initialized.
* \param length    The length of the array that should be allocated.
* \param args      These are the extra arguments that will be passed into the constructor of object T.
*                  The arguments can be left empty.
*
* \return          This returns a double ptr to a za_ptr<T> it should be passed into a normal za_ptr
*                  immediately.
*/
template <typename T, typename... Args>
ZAAP_API inline zaap::system::ZA_MEM_LOCATION* zanewA(za_ptr_<T>* za_ptr, uint length, Args&&... args)
{
	ZA_ASSERT(length != 0, "A array can't have a length of 0.");
	if (length == 0)
		return nullptr;

	zaap::system::ZA_MEM_LOCATION* tLoc = zaap::system::MemoryManager::Allocate(sizeof(T) * length);

	for (uint i = 0; i < length; i++) {
		new(tLoc->MEM_BLOCK) T(args...);
	}
	return tLoc;
}
template <typename T>
ZAAP_API inline zaap::system::ZA_MEM_LOCATION* zanewA(za_ptr_<T>* za_ptr, uint length)
{
	ZA_ASSERT(length != 0, "A array can't have a length of 0.");
	if (length == 0)
		return nullptr;

	zaap::system::ZA_MEM_LOCATION* tLoc = zaap::system::MemoryManager::Allocate(sizeof(T) * length);

	for (uint i = 0; i < length; i++) {
		new(tLoc->MEM_BLOCK) T();
	}
	return tLoc;
}

/**
 * \brief This function allocates memory for object T and initializes the object. The
 *        allocated and initialized memory is returned in the form of a za_ptr.
 *        
 *        The added arguments after the za_ptr are put into the constructor of the wrapped object T.
 *        
 *        The returned pointer should be passed to a za_ptr it will deal with it. The returned pointer can't be kept 
 *        as it is because it will be overridden. 
 *        
 * \tparam T        This is the type of the wrapped object.
 * \tparam Args     These are the extra arguments that will be passed into the constructor of object T. 
 *                  The objects can be left empty. 
 *                  
 * \param za_ptr    The wrapper of the object that should be initialized.
 * \param args      These are the extra arguments that will be passed into the constructor of object T. 
 *                  The arguments can be left empty.
 * 
 * \return          This returns a double pointer to a za_ptr<T> it should be passed into a normal za_ptr
 *                  immediately.
 */
template <typename T, typename... Args>
ZAAP_API inline zaap::system::ZA_MEM_LOCATION* zanew(za_ptr_<T>* za_ptr, Args&&... args)
{
	return zanewA(za_ptr, 1, args...);
}
template <typename T>
ZAAP_API inline zaap::system::ZA_MEM_LOCATION* zanew(za_ptr_<T>* za_ptr)
{
	return zanewA(za_ptr, 1);
}

/* ********************************************************* */
// * zanew general  *
/* ********************************************************* */

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
ZAAP_API inline zaap::system::ZA_MEM_LOCATION* zanewA(uint length, Args&&... args)
{
	ZA_ASSERT(length != 0, "A array can't have a length of 0.");
	if (length == 0)
		return nullptr;

	if (std::is_base_of<zaap::ZAPtrWrapperBase, T>::value) {
		return zanewA((T*)&_za_ptr_buffer, length, args...);
	}
	zaap::system::ZA_MEM_LOCATION* tLoc = zaap::system::MemoryManager::Allocate(sizeof(T) * length);
	
	for (uint i = 0; i < length; i++)
	{
		new(tLoc->MEM_BLOCK) T(args...);
	}
	return tLoc;
}
template <typename T>
ZAAP_API inline zaap::system::ZA_MEM_LOCATION* zanewA(uint length)
{
	ZA_ASSERT(length != 0, "A array can't have a length of 0.");
	if (length == 0)
		return nullptr;

	if (std::is_base_of<zaap::ZAPtrWrapperBase, T>::value) {
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
	for (uint i = 0; i < header->SIZE / sizeof(T); i++)
		(&t[i])->T::~T();

	zaap::system::MemoryManager::Free(t);
}
template <typename T>
ZAAP_API inline void zadel(T** t)
{
	zadel(*t);
}
template <typename T>
ZAAP_API inline void zadel(za_ptr_<T> t)
{
	zadel(t.get());
}
#pragma endregion 