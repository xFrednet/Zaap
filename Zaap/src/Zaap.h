#pragma once

/*
Macro names:
	1.	Macros that start with ZA_ are used to configure 
		the engine to the liking of the user.
		
	2.	ZAAP_* macros are used for the inner working of the engine.
		These macros shouldn't be changed or tempered with from outside of the engine.
		Just hope that everything works with ZA_ macros
*/

#pragma warning(push)
#pragma warning(disable: 4251)

#include <Common.h>
#include <ZAError.h>

#include <app/Application.h>

#include <util/Console.h>
#include <util/StringUtil.h>
#include <util/ImageLoader.h>
#include <util/UUID.h>

#include <scene/terrain/Terrain.h>

#include <graphics/Scene.h>
#include <graphics/Renderer.h>
#include <graphics/Bitmap.h>
#include <graphics/Color.h>
#include <graphics/Material.h>

#include <entity/light/LightSetup.h>
#include <entity/light/Light.h>

#include <graphics/camera/ControllableCamera.h>
#include <graphics/camera/Camera.h>

#include <graphics/mesh/TexturedMesh.h>
#include <graphics/mesh/MeshManager.h>
#include <graphics/TextureManager.h>
#include <graphics/MaterialManager.h>
#include <graphics/API/Context.h>

#include <events/Input.h>

#include <maths/Maths.h>

#pragma warning(pop)