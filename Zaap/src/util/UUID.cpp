#include "UUID.h"

namespace zaap
{

	//
	// Operators
	//
	bool UUID::operator==(const UUID& other) const
	{
		return Equal(*this, other);
	}
	bool UUID::operator!=(const UUID& other) const
	{
		return !Equal(*this, other);
	}

	bool UUID::operator<(const UUID& other) const
	{
		return Less(*this, other);
	}
	bool UUID::operator>(const UUID& other) const
	{
		return Greater(*this, other);
	}

	bool UUID::operator<=(const UUID& other) const
	{
		return Less(*this, other) || Equal(*this, other);
	}
	bool UUID::operator>=(const UUID& other) const
	{
		return Greater(*this, other) || Equal(*this, other);
	}

	//
	//To String
	//
	bool Equal(const UUID& a, const UUID& b)
	{
		return (memcmp(&a, &b, sizeof(UUID)) == 0);
	}

	bool Less(const UUID& a, const UUID& b)
	{
		return Greater(b, a);
	}

	bool Greater(const UUID& a, const UUID& b)
	{
		return memcmp(&a, &b, sizeof(UUID)) > 0;
	}
}


//RandomUUID
#ifdef ZAAP_OS_WIN 
#include <windows.h>

	void zaap::RandomUUID(UUID* uuid)
	{
		_GUID guid;
		CoCreateGuid(&guid);

		memcpy(uuid, &guid, sizeof(UUID));
	}


#else // not ZAAP_OS_WIN
	void zaap::RandomUUID(UUID* uuid)
	{
		ZAAP_ERROR("RandomUUID: could not create a random UUID because no supported OS was specified");
	}
#endif // ZAAP_OS_WIN
