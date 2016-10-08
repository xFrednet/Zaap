#include "UUID.h"
#include <sstream>

namespace zaap
{

	//
	// Operators
	//
	bool UUID::operator==(const UUID& other) const
	{
		for (uint i = 0; i < 16; i++)
		{
			if (Data[i] != other.Data[i])
				return false;
		}
		return true;
	}
	bool UUID::operator!=(const UUID& other) const
	{
		return !(*this == other);
	}

	//
	//To String
	//
	String UUID::toString() const
	{
		return ToString(*this);
	}
	String ToString(const UUID& uuid)
	{
		using namespace std;
		//type            = x bytes
		//uint            = 4

		//first segment
		uint hexValue;
		stringstream ss;
		for (uint i = 0; i < 4; i++)
		{
			memcpy(&hexValue, &uuid.Data[i * 4], sizeof(byte) * 4);
			ss << hex << hexValue;
		}
		String s = ss.str();
		s.insert(20, "-");
		s.insert(16, "-");
		s.insert(12, "-");
		s.insert( 8, "-");
		return s;
	}
}


//RandomUUID
#ifdef ZA_OS_WIN 
#include <windows.h>

void zaap::RandomUUID(UUID* uuid)
	{
		_GUID guid;
		CoCreateGuid(&guid);

		memcpy(uuid, &guid, sizeof(UUID));

	}


#else // not ZA_OS_WIN
	void zaap::RandomUUID(UUID* uuid)
	{
		ZAAP_ERROR("RandomUUID: could not create a random UUID because no supported OS was specified");
	}
#endif // ZA_OS_WIN
