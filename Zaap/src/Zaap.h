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

#include <maths/Maths.h>

#include <app/Application.h>

/* //////////////////////////////////////////////////////////////////////////////// */
// // System //
/* //////////////////////////////////////////////////////////////////////////////// */
#include <system/FileSystem.h>

/* //////////////////////////////////////////////////////////////////////////////// */
// // Util //
/* //////////////////////////////////////////////////////////////////////////////// */
#include <util/Log.h>
#include <util/StringUtil.h>
#include <util/ImageLoader.h>
#include <util/UUID.h>


/* //////////////////////////////////////////////////////////////////////////////// */
// // Scene //
/* //////////////////////////////////////////////////////////////////////////////// */
#include <graphics/Scene.h>
#include <scene/terrain/Terrain.h>

/* //////////////////////////////////////////////////////////////////////////////// */
// // Graphic objects //
/* //////////////////////////////////////////////////////////////////////////////// */
#include <graphics/Format.h>
#include <graphics/Color.h>
#include <graphics/Bitmap.h>
#include <graphics/Material.h>
#include <graphics/Font.h>

/* //////////////////////////////////////////////////////////////////////////////// */
// // GUI //
/* //////////////////////////////////////////////////////////////////////////////// */
#include <gui/GUIManager.h>
#include <gui/GUIComponent.h>

#include <gui/components/GUIBackground.h>
#include <gui/components/GUITextureFrame.h>
#include <gui/components/GUILabel.h>

/* //////////////////////////////////////////////////////////////////////////////// */
// // API component //
/* //////////////////////////////////////////////////////////////////////////////// */
#include <graphics/API/RenderTarget.h>
#include <graphics/API/Texture.h>
#include <graphics/API/Texture2D.h>
#include <graphics/API/VertexBuffer.h>

//renders
#include <graphics/Renderer3D.h>
#include <graphics/GUIRenderer.h>

#include <entity/light/LightSetup.h>
#include <entity/light/Light.h>

#include <graphics/camera/ControllableCamera.h>
#include <graphics/camera/Camera.h>

#include <graphics/mesh/MeshManager.h>
#include <graphics/TextureManager.h>
#include <graphics/MaterialManager.h>
#include <graphics/API/Context.h>

#include <events/Input.h>


#pragma warning(pop)