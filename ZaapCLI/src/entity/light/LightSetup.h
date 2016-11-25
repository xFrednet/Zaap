#pragma once

#include <ZaapCLI.h>

#include <entity/light/LightSetup.h>

#include "Light.h"

namespace ZaapCLI {

	public ref class LightSetup : public ManagedClass<zaap::LightSetup>
	{
	private:
	public:
		LightSetup();

		//util
		void add(Light^ light);
		void remove(Light^ light);

		void update();

		//Ambient lighting
		void setAmbientColor(Color^ color);
		Color^ getAmbientColor();

		//getters
		uint getSize();
		Light^ getLight(int index);
	};
}
