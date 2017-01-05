#include "UUID.h"

namespace ZaapCLI {

	//
	// Init
	//
	UUID::UUID()
		: ManagedClass(new zaap::UUID())
	{
	}
	UUID::UUID(zaap::UUID* instance)
		: ManagedClass(instance)
	{
	}
	UUID::UUID(UUID^ uuid)
		: ManagedClass(new zaap::UUID())
	{
		set(uuid);
	}
	void UUID::generate()
	{
		zaap::RandomUUID(m_Instance);
	}

	//
	// Setter / Getter
	//
	char UUID::getByte(uint index)
	{
		if (index < 16) 
			return m_Instance->Data[index];
		else 
			return 0;
	}
	void UUID::setByte(uint index, char byte)
	{
		if (index < 16)
			m_Instance->Data[index] = byte;
	}
	void UUID::set(UUID^ uuid) {
		memcpy(&m_Instance->Data[0], &uuid->getHandle()->Data[0], sizeof(zaap::UUID));
	}

	//
	//operators
	//
	bool UUID::operator==(UUID^ a, UUID^ b)
	{
		return Equal(*a->getHandle(), *b->getHandle());
	}
	bool UUID::operator!=(UUID^ a, UUID^ b)
	{
		return !Equal(*a->getHandle(), *b->getHandle());
	}

	System::String^ UUID::ToString()
	{
		return to_CLI_String(m_Instance->toString());
	}

}
