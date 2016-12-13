#pragma once

#include <Common.h>
#include <maths/Maths.h>

#include "shader/types/FontShader2D.h"
#include "shader/types/MaterialShader.h"
#include "shader/types/TextureShader.h"
#include "shader/types/TerrainShader.h"
#include "API/Texture2D.h"
#include "camera/ViewFrustum.h"

#ifndef ZA_DEFAULT_FOV
#	define ZA_DEFAULT_FOV 90.0f
#endif

namespace zaap { namespace graphics {
	class Scene;

	// I left out the "API" namespace because I'm too lazy to type it every time

	// <class>
	//      Renderer3D
	//
	// <Description>
	//      This class is an abstract class. It could/should be passed for rendering.
	//      
	//      The constructor is protected. Use @Init to create a 
	//      instance for the current API
	//      
	class ZAAP_API Renderer3D
	{
		//Static constructor
	public:
		// <Function>
		//      Init
		//
		// <Description>
		//      Creates a Renderer3D for the chosen API.
		//
		// <Return>
		//      The renderer for the chosen API or a nullptr in case of failure.
		//      
		Renderer3D* Init();

	protected:
		//Projection Matrix
		float m_FOV = 90.0f;
		float m_NearPlane = 0.1f;
		float m_FarPlane = 1000.0f;
		Mat4 m_ProjectionMatrix;

		//ViewFrustum
		ViewFrustum m_ViewFrustum;

		//Render target
		API::Texture2D* m_Rendertarget; //TODO add getters / setters
		uint m_Width; //TODO add getters / setters
		uint m_Height; //TODO add getters / setters

		//Shader
		ZA_SHADER_TYPE  m_ActiveShaderType;
		TextureShader*  m_TextureShader;
		MaterialShader* m_MaterialShader;
		TerrainShader*  m_TerrainShader;
		FontShader2D*   m_FontShader2D;

		//Constructor to init values
		Renderer3D();
	public:
		virtual ~Renderer3D() {}

		//////////////////
		// Shader stuff //
		//////////////////

		// <Function>
		//      loadTransformationMatrix
		//
		// <Description>
		//      This method loads the given TransformationMatrix into the 
		//      currently active shader (defined by @m_ActiveShaderType).
		// 
		//      In case that @m_ActiveShaderType points to a shader that does
		//      not support a TransformationMatrix it'll just return without
		//      any actions.
		//
		// <Input>
		//      A valid TransformationMatrix.
		//
		void loadTransformationMatrix(const Mat4& transformationMatrix) const;
		
		// <Function>
		//      loadLightSetup
		//
		// <Description>
		//      This methods loads the given @LightSetup into all valid shaders
		//      that support it.
		//
		// <Input>
		//      A valid LightSetup.
		//
		void loadLightSetup(const LightSetup& LightSetup);
		
		// <Function>
		//      loadScene
		//
		// <Description>
		//      This methods loads and saves some components from the @Scene class.
		//      Examples:
		//          - @Camera position
		//          - Current @ViewFrustum
		//
		// <Input>
		//      A Instance of the @Scene.
		//
		void loadScene(const Scene const* scene);


		// <Function>
		//      startShader
		//
		// <Description>
		//      Starts the shader specified by the input.
		//
		// <Input>
		//      @ZA_SHADER_TYPE the requested shader to start
		//
		void startShader(ZA_SHADER_TYPE shader);
		
		// <Function>
		//      getShader
		//
		// <Description>
		//      Returns the shader that is specified by the input.
		//      This does not create changes or starts any shaders by it self.0.
		//
		// <Input>
		//      @ZA_SHADER_TYPE the requested shader type
		//
		// <Returns>
		//      Returns the requested shader instance or a nullptr in case of failure.
		Shader* getShader(ZA_SHADER_TYPE shader);


		// <Function>
		//      setAlphaTestingState
		//
		// <Description> //TODO add desc
		virtual void setAlphaTestingState(bool enabled) const = 0;
		//these two methods just access the "setAlphaTestingState(bool)" method
		inline void enableAlphaTesting() const;
		inline void disableAlphaTesting() const;

		// <Function>
		//      setDepthTestingState
		//
		// <Description>
		// TODO Description
		virtual void setDepthTestingState(bool enable) const = 0;
		//accessing setDepthTestingState
		inline void enableDepthTesting() const;
		inline void disableDepthTesting() const;

		//
		// Values
		//

		// <Function>
		//      getFOV
		//
		// <Description>
		//      Returns the m_FOV value of this Renderer3D.
		//      m_FOV is used create the m_ProjectionMatrix.
		//
		// <Return>
		//      The current value of m_FOV.
		//
		inline float getFOV() const;

		// <Function>
		//      getFOV
		//
		// <Description>
		//      Sets the m_FOV value of this Renderer3D.
		//      m_FOV is used create the m_ProjectionMatrix.
		//
		// <Input>
		//      A value for m_FOV.
		//
		inline void setFOV(const float& fov);

		// <Function>
		//      getNearPlane
		//
		// <Description>
		//      Returns the m_NearPlane value of this Renderer3D.
		//      m_NearPlane is used create the m_ProjectionMatrix.
		//
		// <Return>
		//      The current value of m_NearPlane.
		//
		inline float getNearPlane() const;

		// <Function>
		//      setNearPlane
		//
		// <Description>
		//      Sets the m_NearPlane value of this Renderer3D.
		//      m_NearPlane is used create the m_ProjectionMatrix.
		//
		// <Input>
		//      A new value for m_NearPlane.
		//
		inline void setNearPlane(const float& nearPlane);

		// <Function>
		//      getFarPlane
		//
		// <Description>
		//      Returns the m_FarPlane value of this Renderer3D.
		//      m_FarPlane is used create the m_ProjectionMatrix.
		//
		// <Return>
		//      The current value of m_FarPlane.
		//
		inline float getFarPlane() const;

		// <Function>
		//      setFarPlane
		//
		// <Description>
		//      Sets the m_FarPlane value of this Renderer3D.
		//      m_FarPlane is used create the m_ProjectionMatrix.
		//
		// <Input>
		//      A new value for m_FarPlane.
		//
		inline void setFarPlane(const float& farPlane);

		// <Function>
		//      calulateProjectionMatrix
		//
		// <Description>
		//      Recalculates the current m_ProjectionMatrix for this Renderer3D.
		//      This method uses the m_FOV, m_NearPlane, m_FarPlane and the size defined
		//      by m_Width and m_Height.
		//
		inline void calulateProjectionMatrix();

		// <Function>
		//      getProjectionMatrix
		//
		// <Description>
		//      Returns the current m_ProjectionMatrix for this Renderer3D.
		//      This method only returns the m_ProjectionMatrix. Use 
		//      calulateProjectionMatrix to recalculate the Matrix. 
		//      (This is done usually automatically)
		//
		// <Returns>
		//      Returns the current m_ProjectionMatrix.
		//
		inline Mat4 getProjectionMatrix() const;
		
		// <Function>
		//      setProjectionmatrix
		//
		// <Description>
		//      Sets the current m_ProjectionMatrix for this Renderer3D.
		//      This method only sets the m_ProjectionMatrix until it's 
		//      changed by a different method. this could be caused by resizing or other
		//      changes.
		//
		// <Input>
		//      The new value for m_ProjectionMatrix.
		//
		inline void setProjectionmatrix(const Mat4& projectionMatrix);

		// <Function>
		//      getViewFrustum
		//
		// <Description>
		//      This returns the current ViewFrustum. It should be updated every
		//      update by the scene class. (It's set by the camera in loadScene())
		//
		// <Resturn>
		//      Returns the current m_ViewFrustum.
		//
		inline ViewFrustum getViewFrustum() const;
	};

}}
