#pragma once

#include <Common.h>
#include <maths/Maths.h>

#include "API/Context.h"
#include "shader/DefaultShader.h"
#include "shader/TerrainShader.h"
#include "API/Texture2D.h"
#include "camera/ViewFrustum.h"
#include "API/RenderTarget.h"

#ifndef ZA_DEFAULT_FOV
#	define ZA_DEFAULT_FOV 90.0f
#endif

//TODO put the cleanup methods in the destructors

namespace zaap { namespace graphics {
	class Scene;

	// I left out the "API" namespace because I'm too lazy to type it every time

	// <class>
	//      Renderer3D
	//
	// <Description>
	//      This class is an abstract class. It could/should be passed for rendering. <\n>
	//      
	//      The constructor is protected. Use CreateNewInstance to create a 
	//      instance for the current API
	//      
	class ZAAP_API Renderer3D
	{
		//Static constructor
	public:

		// <Function>
		//      CreateNewInstance
		//
		// <Description>
		//      Creates a Renderer3D for the chosen API.
		//
		// <Note>
		//      The instance is created using the new statement the requester 
		//      has to delete the new instance.
		//
		// <Return>
		//      The renderer for the chosen API or a nullptr in case of failure.
		//
		static Renderer3D* CreateNewInstance();

	protected:
		//Projection Matrix
		float m_FOV = 90.0f;
		float m_NearPlane = 0.1f;
		float m_FarPlane = 1000.0f;
		Mat4 m_ProjectionMatrix;

		//ViewFrustum
		ViewFrustum m_ViewFrustum;

		/* //////////////////////////////////////////////////////////////////////////////// */
		// // render-target //
		/* //////////////////////////////////////////////////////////////////////////////// */

		// <Value>
		//      m_HasCustomRenderTarget
		//
		// <Description>
		//      This represents the Render Target type.
		//      
		// <Note>
		//      It is set to false by default.
		//
		ZA_RENDERER_TARGET_TYPE m_RenderTargetType;

		// <Value>
		//      m_RenderTarget
		// 
		// <Description>
		//      This is the rendering target. It can be set 
		//      to a custom render-target.
		//
		API::RenderTarget* m_RenderTarget; //TODO add getters / setters
		
		// <Value>
		//      m_DepthStencil
		// 
		// <Description>
		//      This is the depth stencil. It has the same 
		//      size as the render-target. It can't be set by
		//      from the outside because it corresponds with
		//      the render-target.
		//
		// <Note>
		//      This usually gets created by the API renderer. 
		//      The last instance gets deleted in the 
		//      cleanupBaseRenderer3D method. This is only done if 
		//      m_HasCustomRenderTarget is false.
		//
		API::Texture2DCore* m_DepthStencil; //TODO add getter

		//Shader
		ZA_SHADER_TYPE  m_ActiveShaderType;
		DefaultShader*  m_DefaultShader;
		TerrainShader*  m_TerrainShader;

	protected:
		//Constructor to init values
		Renderer3D(ZA_RENDERER_TARGET_TYPE renderTargetType);

	public:
		// <Destructor>
		//      Renderer3D
		//
		// <Description>
		//      This method deletes all the values that are created
		//      using the new operator. (This only includes the values that
		//      are inside this base Renderer3D)
		//
		virtual ~Renderer3D();

	protected:
		virtual void renderTargetUpdated() = 0;
	public:
		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Shader stuff //
		/* //////////////////////////////////////////////////////////////////////////////// */
		
		// <Function>
		//      loadTransformationMatrix
		//
		// <Description>
		//      This method loads the given TransformationMatrix into the 
		//      currently active shader (defined by @m_ActiveShaderType).
		//
		// <Note>
		//      In case that @m_ActiveShaderType points to a shader that does
		//      not support a TransformationMatrix it'll just return without
		//      any actions.
		//
		// <Input>
		//      transformationMatrix:
		//          A 4x4 Matrix that is loaded as a TransformationMatrix.
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
		//      lightSetup:
		//          A @LightSetup that is loaded to the shaders.
		//
		void loadLightSetup(const LightSetup& lightSetup);
		
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
		//      scene:
		//          A pointer to a instance of the @Scene class.
		//
		void loadScene(const Scene* scene);

		// <Function>
		//      startShader
		//
		// <Description>
		//      Starts the shader specified by the input.
		//
		// <Input>
		//      shader:
		//         The @ZA_SHADER_TYPE of the requested shader to start.
		//
		void startShader(ZA_SHADER_TYPE shader);
		
		// <Function>
		//      getShader
		//
		// <Description>
		//      Returns the shader that is specified by the input.
		//      This does not create changes or starts any shaders by it self.
		//
		// <Input>
		//      shader: 
		//          The @ZA_SHADER_TYPE of the requested shader.
		//
		// <Returns>
		//      Returns the requested shader instance or a nullptr in case of failure.
		//
		Shader* getShader(ZA_SHADER_TYPE shader);

		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Frame related // 
		/* //////////////////////////////////////////////////////////////////////////////// */

		// <Function>
		//      setCustomRenderTarget
		//
		// <Description>
		//      This sets a custom render-target.
		//
		// <Note>
		//      -   The API renderer has to bind the texture as a resource 
		//          this can take time and therefor reduce performance. So please
		//          please don't change the render-target every frame.
		//      
		//      - This method should affect m_HasCustomRenderTarget
		//          - A valid pointer means that a custom render-target is set.
		//          - A null pointer sets m_HasCustomRenderTarget back to false.
		//            rendered scenes are now rendered to the screen and 
		//            WindowResizeEvents effect the render-target again.
		//
		// <Input>
		//      target: 
		//          The new render-target. Null is also a valid input.
		//      width:
		//          The width of the render-target. This can be 0 if the target is also
		//          set to null.
		//      height:
		//          The height of the render-target. This can be 0 if the target is also
		//          set to null.
		//
		virtual void setCustomRenderTarget(API::RenderTarget* renderTarget);

		virtual void startRenderer() const = 0;

		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Rendering options //
		/* //////////////////////////////////////////////////////////////////////////////// */

		// <Function>
		//      setAlphaTestingState
		//
		// <Description>
		//      This method disables/enables alpha testing.
		//      This can be used to disable the alpha channel for 
		//      objects that should be rendered without that. It should
		//      also improve the performance. 
		//      => Enable if you want/need a alpha value disable it 
		//         otherwise to improve performance.
		//      
		// <Input>
		//      enable: 
		//          indicates the new state 
		//              true = enabled
		//              false = disabled
		//
		virtual void setAlphaTestingState(bool enable) const = 0;
		// <Function>
		//      enableAlphaTesting
		//
		// <Description>
		//      This methods excesses setAlphaTestingState to enable
		//      the alpha testing. So it's just a easier method.
		//      
		inline void enableAlphaTesting() const;
		// <Function>
		//      disableAlphaTesting
		//
		// <Description>
		//      This methods excesses setAlphaTestingState to disable
		//      the alpha testing. So it's just a easier method.
		//
		inline void disableAlphaTesting() const;

		// <Function>
		//      setDepthTestingState
		//
		// <Description>
		//      This method disables/enables depth testing. 
		//      This maybe useful for the GUI and other components
		//      because they are always rendered in front this could
		//      save some extra test. It's also useful to control which
		//      models are rendered to the DepthStencil.
		//      
		// <Input>
		//      enable: 
		//          indicates the new state 
		//              true = enabled
		//              false = disabled
		//
		virtual void setDepthTestingState(bool enable) const = 0;
		// <Function>
		//      enableDepthTesting
		//
		// <Description>
		//      This methods excesses setDepthTestingState to disable
		//      depth testing. So it's just a easier method.
		//
		inline void enableDepthTesting() const;
		// <Function>
		//      disableDepthTesting
		//
		// <Description>
		//      This methods excesses setDepthTestingState to disable
		//      depth testing. So it's just a easier method.
		//
		inline void disableDepthTesting() const;

		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Values //
		/* //////////////////////////////////////////////////////////////////////////////// */
		
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
		//      fov:
		//          A value for m_FOV.
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
		//      nearPlane:
		//          A new value for m_NearPlane.
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
		//      farPlane:
		//          A new value for m_FarPlane.
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
		void calulateProjectionMatrix();
		// <Function>
		//      updateProjectionMatrix
		//
		// <Description>
		//      This uses calulateProjectionMatrix to calculate a new 
		//      ProjectionMatrix to load to the shaders. 
		//
		// <Note>
		//      The font shader also need the width and hight for the
		//      TransformationMatrix. The values are also passed along
		//
		void updateProjectionMatrix();
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
		//      setProjectionMatrix
		//
		// <Description>
		//      Sets the current m_ProjectionMatrix for this Renderer3D.
		//      This method only sets the m_ProjectionMatrix until it's 
		//      changed by a different method. this could be caused by resizing or other
		//      changes.
		//
		// <Input>
		//      projectionMatrix:
		//          The new 4x4 matrix for m_ProjectionMatrix.
		//
		inline void setProjectionMatrix(const Mat4& projectionMatrix);

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
