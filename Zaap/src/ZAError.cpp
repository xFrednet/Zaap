#include "ZAError.h"

#include <util/Console.h>
#include "maths/Maths.h"

/* //////////////////////////////////////////////////////////////////////////////// */
// // ZA_MULTI_RESULT //
/* //////////////////////////////////////////////////////////////////////////////// */
namespace zaap {
	ZA_MULTI_RESULT_::ZA_MULTI_RESULT_()
	{
		for (uint i = 0; i < ZA_MULTI_RESULT_SIZE; i++)
			Results[i] = ZA_OK;
	}

	ZA_MULTI_RESULT_::ZA_MULTI_RESULT_(ZA_RESULT result)
	{
		for (uint i = 0; i < ZA_MULTI_RESULT_SIZE; i++)
			Results[i] = ZA_OK;

		*this += result;
	}

	ZA_RESULT& ZA_MULTI_RESULT_::operator[](int index)
	{
		if (index >= 0 || index < ZA_MULTI_RESULT_SIZE)
			return Results[index];

		if (index < 0)
			return Results[0];
		else
			return Results[ZA_MULTI_RESULT_SIZE - 1];
	}
	const ZA_RESULT& ZA_MULTI_RESULT_::operator[](const int index) const
	{
		if (index >= 0 || index < ZA_MULTI_RESULT_SIZE)
			return Results[index];

		if (index < 0)
			return Results[0];
		else
			return Results[ZA_MULTI_RESULT_SIZE - 1];
	}

	ZA_MULTI_RESULT_& ZA_MULTI_RESULT_::operator+=(const ZA_RESULT& other)
	{
		*this = zaap::AddZAResult(*this, other);
		return *this;
	}
	ZA_MULTI_RESULT_& ZA_MULTI_RESULT_::operator+=(const ZA_MULTI_RESULT_& other)
	{
		*this = zaap::CombineZAResults(*this, other);
		return *this;
	}

	ZA_MULTI_RESULT_ ZA_MULTI_RESULT_::operator+(const ZA_RESULT& other) const
	{
		return zaap::AddZAResult(*this, other);
	}
	ZA_MULTI_RESULT_ ZA_MULTI_RESULT_::operator+(const ZA_MULTI_RESULT_& other) const
	{
		return zaap::CombineZAResults(*this, other);
	}

	bool ZA_MULTI_RESULT_::operator==(const ZA_RESULT& other) const
	{
		return (this->Results[0] == other);
	}
	bool ZA_MULTI_RESULT_::operator!=(const ZA_RESULT& other) const
	{
		return (this->Results[0] != other);
	}
	bool ZA_MULTI_RESULT_::operator<(const ZA_RESULT& other) const
	{
		return (this->Results[0] < other);
	}
	bool ZA_MULTI_RESULT_::operator>(const ZA_RESULT& other) const
	{
		return (this->Results[0] > other);
	}
	bool ZA_MULTI_RESULT_::operator<=(const ZA_RESULT& other) const
	{
		return (this->Results[0] <= other);
	}
	bool ZA_MULTI_RESULT_::operator>=(const ZA_RESULT& other) const
	{
		return (this->Results[0] >= other);
	}
}

/* //////////////////////////////////////////////////////////////////////////////// */
// // ZA_RESULT util //
/* //////////////////////////////////////////////////////////////////////////////// */
namespace zaap
{
	void SubmitZAResult(ZA_RESULT result)
	{
		ZAAP_ERROR(std::to_string(result));
	}


	void SubmitZAResult(const ZA_RESULT& result, const String& file, const uint& line)
	{
		console::Println(file, line, ZA_CON_MESSAGE_ERROR, std::to_string(result));
	}

	ZA_MULTI_RESULT CombineZAResults(std::initializer_list<ZA_RESULT> results)
	{
		uint index = 0;
		ZA_MULTI_RESULT result;
		
		if (results.size() == 0)
			return result;

		for (ZA_RESULT subResult : results)
		{
			//test if the index is still inside the bounds
			if (index < ZA_MULTI_RESULT_SIZE)
			{
				result[index++] = subResult;
			} else // add the information error and break
			{
				result[ZA_MULTI_RESULT_SIZE - 1] = ZA_ERROR_TO_MANY_RESULTS_FOR_MULTIRESULT;
				break;
			}
		}

		return result;
	}

	ZA_MULTI_RESULT AddZAResult(ZA_MULTI_RESULT srcResult, ZA_RESULT addResult)
	{
		ZA_MULTI_RESULT result;
		bool enoughSpace = srcResult[ZA_MULTI_RESULT_SIZE - 1] == 0x0000;

		//moves all results one back (- 1 to stay inbounds)
		memcpy(&result[1], &srcResult[0], sizeof(ZA_RESULT) * (ZA_MULTI_RESULT_SIZE - 1));

		result[0] = addResult;

		if (!enoughSpace)
			result[ZA_MULTI_RESULT_SIZE - 1] = ZA_ERROR_TO_MANY_RESULTS_FOR_MULTIRESULT;


		return result;
	}

	ZA_MULTI_RESULT AddZAResults(ZA_MULTI_RESULT srcResult, std::initializer_list<ZA_RESULT> list)
	{
		if (list.size() == 0)
			return srcResult;

		ZA_MULTI_RESULT result;
		bool enoughSpace;
		uint size = ZA_MIN(list.size(), ZA_MULTI_RESULT_SIZE);

		if (list.size() <= ZA_MULTI_RESULT_SIZE)
			enoughSpace = srcResult[ZA_MULTI_RESULT_SIZE - list.size()] == 0x0000;
		else
			enoughSpace = false;

		//move back
		if (size != ZA_MULTI_RESULT_SIZE)
			memcpy(&result[size], &srcResult[0], sizeof(ZA_RESULT) * (ZA_MULTI_RESULT_SIZE - size));

		//add new results
		uint i = 0;
		for (ZA_RESULT subResult : list)
		{
			if (i < size) //yes awesome for loop
				i++;
			else 
				break;

			result[i] = subResult;
		}

		if (!enoughSpace)
			result[ZA_MULTI_RESULT_SIZE - 1] = ZA_ERROR_TO_MANY_RESULTS_FOR_MULTIRESULT;

		return result;
	}

	ZA_MULTI_RESULT CombineZAResults(ZA_MULTI_RESULT mResult1, ZA_MULTI_RESULT mResult2)
	{
		std::initializer_list<ZA_RESULT> list;
		ZA_MULTI_RESULT result;
		bool enoughSpace;
		
		//size
		uint size = 0;
		for (uint i = 0; i < ZA_MULTI_RESULT_SIZE; i++)
			if (mResult2[i] != 0x0000)
				size++;
			else
				break;

		if (size == 0)
			return mResult1;

		//enoughSpace
		enoughSpace = mResult1[ZA_MULTI_RESULT_SIZE - size] == 0x0000;
		
		//move back
		if (size != ZA_MULTI_RESULT_SIZE)
			memcpy(&result[size], &mResult1[0], sizeof(ZA_RESULT) * (ZA_MULTI_RESULT_SIZE - size));

		//add new results
		for (uint i = 0; i < size; i++)
		{
			result[i] = mResult2[i];
		}

		if (!enoughSpace)
			result[ZA_MULTI_RESULT_SIZE - 1] = ZA_ERROR_TO_MANY_RESULTS_FOR_MULTIRESULT;

		return result;
	}
}

/* //////////////////////////////////////////////////////////////////////////////// */
// // ZA_RESULT messages //
/* //////////////////////////////////////////////////////////////////////////////// */
namespace zaap
{
	ZA_RESULT GetResultSource(const ZA_RESULT& result)
	{
		// 16 bits
		return;
	}

	String GetResultMessage(ZA_RESULT result)
	{
	}
	
}
