#include "MaterialManager.h"

namespace ZaapCLI
{
	void MaterialManager::LoadMTLFile(System::String^ filePath)
	{
		zaap::graphics::MaterialManager::LoadMTLFile(to_CPP_String(filePath));
	}

	void MaterialManager::Add(System::String^ name, Material^ material)
	{
		zaap::graphics::MaterialManager::Add(to_CPP_String(name), *material->getHandle());
	}

	Material^ MaterialManager::Get(System::String^ name)
	{
		return gcnew Material(&zaap::graphics::MaterialManager::Get(to_CPP_String(name)));
	}

	bool MaterialManager::Contains(System::String^ name)
	{
		return zaap::graphics::MaterialManager::Contains(to_CPP_String(name));
	}

	void MaterialManager::Cleanup()
	{
		zaap::graphics::MaterialManager::Cleanup();
	}
}
