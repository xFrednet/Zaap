#pragma once

#include <ZaapCLI.h>

#include <graphics\Renderer3D.h>
#include "shader\Shader.h"
#include "components\Texture2D.h"
#include "camera\ViewFrustum.h"
#include "..\entity\light\LightSetup.h"


namespace ZaapCLI
{

	ref class Scene;

	// <class>
	//      Renderer3D
	//
	// <Description>
	//      This class is an abstract class. It could/should be passed for rendering.
	//      
	public ref class Renderer3D : public ManagedClass<zaap::graphics::Renderer3D> 
	{
	public:
		////////////////////////////////////////////////////////////////////////////////
		// Constructor //
		////////////////////////////////////////////////////////////////////////////////

		// <Constructor>
		//      Renderer3D
		//
		// <Description>
		//      This creates a new Renderer3D for the current
		//      graphics API
		//
		Renderer3D();
		
		// <Constructor>
		//      Renderer3D
		//
		// <Description>
		//      This creates a new CLI class from the given
		//      pointer instance.
		//
		// <Note> 
		//      This is only used for ZaapCLI intern stuff.
		//      
		Renderer3D(zaap::graphics::Renderer3D* instance);

		////////////////////////////////////////////////////////////////////////////////
		// Shader stuff //
		////////////////////////////////////////////////////////////////////////////////

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
		//      lightSetup:
		//          A @LightSetup that is loaded to the shaders.
		//
		void loadTransformationMatrix(Matrix4^ transformationMatrix);

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
		void loadLightSetup(LightSetup^ lightSetup);

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
		void loadScene(Scene^ scene);

		// <Function>
		//      startShader
		//
		// <Description>
		//      Starts the shader specified by the input.
		//
		// <Input>
		//      shader:
		//          @ZA_SHADER_TYPE the requested shader to start
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
		Shader^ getShader(ZA_SHADER_TYPE shader);

		////////////////////////////////////////////////////////////////////////////////
		// Frame related // 
		////////////////////////////////////////////////////////////////////////////////

		// <Function>
		//      setCustomRenderTarget
		//      
		// <Description>
		//      This sets a custom render-target.
		//      
		// <Note>
		//   1. The API renderer has to bind the texture as a resource 
		//        this can take time and therefor reduce performance. So please
		//        please don't change the render-target every frame.
		//      
		//   2. This method should affect m_HasCustomRenderTarget
		//        - A valid pointer means that a custom render-target is set.
		//
		// <Input>
		//      target: 
		//          The new render-target.
		//      width:
		//          The width of the render-target.
		//      height:
		//          The height of the render-target.
		//
		void setCustomRenderTarget(Texture2D^ target, uint width, uint height);

		// <Function>
		//      diableCustomRenderTarget
		//
		// <Description>
		//      This disables the custom render-target.
		//
		// <Note>
		//     1. The API renderer has to create a new render-target 
		//          this can take time and therefor reduce performance. So please
		//          please don't change the render-target every frame.
		//      
		//     2. This method should affect m_HasCustomRenderTarget
		//
		void diableCustomRenderTarget();

		// <Function>
		//      prepareFrame
		//
		// <Description>
		//      This method should be called at the start of every Frame.
		//      It prepares the Frame in some different ways, just call it
		//      for the greater good of the engine.
		//      (Note: Some APIs might have some extra functions in here.)
		//
		void prepareFrame();

		// <Function>
		//      prepareFrame
		//
		// <Description>
		//      This method should be called at the end of every Frame.
		//      It presents the Frame by swapping the BackBuffer.
		//      (Note: Some APIs might have some extra functions in here.)
		//
		void presentFrame();

		////////////////////////////////////////////////////////////////////////////////
		// Rendering options //
		////////////////////////////////////////////////////////////////////////////////

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
		void setAlphaTestingState(bool enable);
		// <Function>
		//      enableAlphaTesting
		//
		// <Description>
		//      This methods excesses setAlphaTestingState to enable
		//      the alpha testing. So it's just a easier method.
		//      
		void enableAlphaTesting();
		// <Function>
		//      disableAlphaTesting
		//
		// <Description>
		//      This methods excesses setAlphaTestingState to disable
		//      the alpha testing. So it's just a easier method.
		//
		void disableAlphaTesting();

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
		void setDepthTestingState(bool enable);
		// <Function>
		//      enableDepthTesting
		//
		// <Description>
		//      This methods excesses setDepthTestingState to disable
		//      depth testing. So it's just a easier method.
		//
		void enableDepthTesting();
		// <Function>
		//      disableDepthTesting
		//
		// <Description>
		//      This methods excesses setDepthTestingState to disable
		//      depth testing. So it's just a easier method.
		//
		void disableDepthTesting();

		// <Function>
		//      resize
		//
		// <Description>
		//      This method configures the RenderTarget size and
		//      some API related things.
		//      
		// <Input>
		//      width: 
		//          the new width.
		//      height: 
		//          the new height.
		//      
		// <Note>
		//      This method will be changed to add extra resize options 
		//      or to enable the user to set a target frame part
		//      
		void resize(uint width, uint height);

		////////////////////////////////////////////////////////////////////////////////
		// Values //
		////////////////////////////////////////////////////////////////////////////////

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
		float getFOV();
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
		void setFOV(float fov);

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
		float getNearPlane();
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
		void setNearPlane(float nearPlane);

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
		float getFarPlane();
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
		void setFarPlane(float farPlane);

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
		Matrix4^ getProjectionMatrix();
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
		//      projectionMatrix:
		//          The new 4x4 matrix for m_ProjectionMatrix.
		//
		void setProjectionMatrix(Matrix4^ projectionMatrix);

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
		ViewFrustum^ getViewFrustum();
	};

}