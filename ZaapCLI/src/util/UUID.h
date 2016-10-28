#pragma once

#include <ZaapCLI.h>

#include <util/UUID.h>

namespace ZaapCLI {

	public ref class UUID : public ManagedClass<zaap::UUID>
	{
	private:
	public:
		//init
		UUID();
		UUID(UUID^ uuid);

		//Generate a random UUID
		void generate();

		//setter / getter
		char getByte(uint index);
		void setByte(uint index, char byte);
		void set(UUID^ uuid);

		//operators
		static bool operator==(UUID^ a, UUID^ b);
		static bool operator!=(UUID^ a, UUID^ b);

		//String format UUID(xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx)
		virtual System::String^ ToString() override;
	};
}
