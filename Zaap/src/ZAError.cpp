#include "ZAError.h"

#include <util/Console.h>

namespace zaap
{
	void SubmitZAResult(ZA_RESULT result)
	{
		ZAAP_ERROR(std::to_string(result));
	}
}