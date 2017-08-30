#include "za_ptr.h"

namespace zaap
{
	ZA_PTR_OBJECT_INFO_PAGE*     ZaPtrHelper::s_PageList             = nullptr;
	ZA_PTR_OBJECT_INFO*          ZaPtrHelper::s_FreeObjectInfoList   = nullptr;


	void ZaPtrHelper::AllocateNewObjectInfoPage()
	{
		ZA_PTR_OBJECT_INFO_PAGE* page = new ZA_PTR_OBJECT_INFO_PAGE;
		memset(page, 0, sizeof(ZA_PTR_OBJECT_INFO_PAGE));

		for (unsigned i = 0; i < ZA_MEM_PTR_USE_COUNT_PER_PAGE - 1; i++) {
			page->ObjectInfoList[i].Next = &page->ObjectInfoList[i + 1];
		}

		page->ObjectInfoList[ZA_MEM_PTR_USE_COUNT_PER_PAGE - 1].Next = s_FreeObjectInfoList;
		s_FreeObjectInfoList = page->ObjectInfoList;

		page->Next = s_PageList;
		s_PageList = page;
	}
	void ZaPtrHelper::FreeObjectInfoPage(ZA_PTR_OBJECT_INFO_PAGE* page)
	{
		delete page;
	}

	ZA_PTR_OBJECT_INFO* ZaPtrHelper::GetFreeObjectInfo()
	{
		if (!s_FreeObjectInfoList)
			AllocateNewObjectInfoPage();

		ZA_PTR_OBJECT_INFO* counter = s_FreeObjectInfoList;
		s_FreeObjectInfoList = s_FreeObjectInfoList->Next;

		return counter;
	}
	void ZaPtrHelper::ReturneObjectInfo(ZA_PTR_OBJECT_INFO* info)
	{
		if (info->UseCount != 0)
			std::cout << "Hey, who wants to kill me?" << std::endl;
		info->UseCount = 0;

		//returning it to the pool
		info->Next = s_FreeObjectInfoList;
		s_FreeObjectInfoList = info;
	}
}