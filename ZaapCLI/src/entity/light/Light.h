#pragma once

#include <ZaapCLI.h>

#include <entity\light\Light.h>

#include "..\..\graphics\Color.h"
#include <maths\Vector3.h>

namespace ZaapCLI {

	public ref class Light {
	private:
	protected:
		zaap::Light* m_Instance;
	public:
		Light(zaap::Light* instance);

		Light();
		Light(Vector3^ position, Color^ color);

		virtual ~Light();
		!Light();

		//color
		void setColor(Color^ color);
		Color^ getColor();

		//position
		void setPosition(Vector3^ position);
		void increasePosition(Vector3^ position);
		Vector3^ getPosition();

		static bool operator==(Light^ left, Light^ right);
		static bool operator!=(Light^ left, Light^ right);

		zaap::Light* getHandle();
	};
}
