#pragma once

#include <Common.h>

#include "../Scene.h"

namespace zaap { namespace graphics {
	struct Material;

	// <Class>
	//		DefaultShader
	//
	// <Description>
	//		This class is a representation for the default
	//		shader for the current API. <\n>
	//		The default shader renders the models as good as
	//		it possibly can. It can be overridden to achieve some
	//		different effect.
	//
	class ZAAP_API DefaultShader : public Shader {
	protected:
		
		/* ##################################### */
		// # Matrix buffer #
		/* ##################################### */

		// <Value>
		//		m_MatrixBufferStruct
		//
		// <Description>
		//		This struct holds the matrices for the vertex shader.
		//
		ZA_VS_MATRIX_BUFFER m_MatrixBufferStruct;

		// <Function>
		//		loadMatrixBuffer
		//
		// <Description>
		//		This function uploads the matrix buffer to the
		//		shader. It is overridden by the sub classes.
		//
		virtual void loadMatrixBuffer() = 0;

		/* ##################################### */
		// # Scene buffer #
		/* ##################################### */

		// <Value>
		//		m_SceneBufferStruct
		//
		// <Description>
		//		This struct holds the relevant @Scene information
		//
		ZA_VS_SCENE_BUFFER m_SceneBufferStruct;

		// <Function>
		//		loadSceneBuffer
		//
		// <Description>
		//		This function uploads the scene buffer to the
		//		shader. It is overridden by the sub classes.
		//
		virtual void loadSceneBuffer() = 0;

		/* ##################################### */
		// # Light buffers #
		/* ##################################### */

		// <Value>
		//		m_VSLightBifferStruct
		//
		// <Description>
		//		This struct holds the needed @Light information
		//		of the loaded @LightSetup.
		//
		ZA_VS_LIGHT_BUFFER m_VSLightBifferStruct;
		// <Value>
		//		m_PSLightBifferStruct
		//
		// <Description>
		//		This struct holds the required @Light information
		//		of the loaded @LightSetup.
		//
		ZA_PS_LIGHT_BUFFER m_PSLightBifferStruct;

		// <Function>
		//		loadLightBuffers
		//
		// <Description>
		//		This function uploads the @Light buffers to the
		//		shaders. It is overridden by the sub classes.
		//
		virtual void loadLightBuffers() = 0;

		/* ##################################### */
		// # Material buffer #
		/* ##################################### */

		// <Value>
		//		m_MaterialBufferStruct
		//
		// <Description>
		//		This holds the @Materials for the pixel shader.
		//
		ZA_PS_MATERIAL_BUFFER m_MaterialBufferStruct;

		// <Function>
		//		loadMaterialBuffer
		//
		// <Description>
		//		This function uploads the @Material buffer to the
		//		pixel shader. It is overridden by the sub classes.
		//
		virtual void loadMaterialBuffer() = 0;

	public:
		virtual ~DefaultShader() {}

		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Loaders //
		/* //////////////////////////////////////////////////////////////////////////////// */

		/* ##################################### */
		// # Matrix buffer #
		/* ##################################### */

		// <Function>
		//		setTransformationMatrix
		//
		// <Description>
		//		This sets the current transformation matrix and updates
		//		the current matrix buffer in the actual shader.
		//
		// <Input>
		//		transformationMatrix::
		//			The Matrix that should be set as the transformation
		//			matrix in the matrix buffer struct.;;
		//
		inline void setTransformationMatrix(const Mat4& transformationMatrix);

		// <Function>
		//		setViewMatrix
		//
		// <Description>
		//		This sets the current view matrix and updates
		//		the current matrix buffer in the actual shader.
		//
		// <Input>
		//		viewMatrix::
		//			The Matrix that should be set as the view matrix
		//			in the matrix buffer struct.;;
		//
		inline void setViewMatrix(const Mat4& viewMatrix);

		// <Function>
		//		setProjectionMatrix
		//
		// <Description>
		//		This sets the current projection matrix and updates
		//		the current matrix buffer in the actual shader.
		//
		// <Input>
		//		viewMatrix::
		//			The Matrix that should be set as the projection
		//			matrix in the matrix buffer struct.;;
		//
		inline void setProjectionMatrix(const Mat4& projectionMatrix);

		// <Function>
		//		setMatrixBuffer
		//
		// <Description>
		//		This changes the entire matrix buffer and uploads it
		//		to the current shader.
		//
		// <Input>
		//		matrixBuffer::
		//			The matrix buffer that should be used.;;
		//
		inline void setMatrixBuffer(ZA_VS_MATRIX_BUFFER matrixBuffer);

		// <Function>
		//		getMatrixBuffer
		//
		// <Return>
		//		This return the current matrix buffer.
		//
		inline ZA_VS_MATRIX_BUFFER getMatrixBuffer() const;

		/* ##################################### */
		// # Scene buffer #
		/* ##################################### */

		// <Function>
		//		setCameraPosition
		//
		// <Description>
		//		This sets the @Camera position of the @Scene shader.
		//
		// <Input>
		//		position::
		//			The position that should be set as the @Camera position
		//			in the @Scene shader.;;
		//
		inline void setCameraPosition(const Vec3& position);

		// <Function>
		//		loadScene
		//
		// <Description>
		//		This loads the required information from the @Scene
		//		and uploads it to @Scene buffer.
		//
		// <Input>
		//		scene::
		//			The scene were the information is loaded from.;;
		//
		void loadScene(const Scene const* scene);

		/* ##################################### */
		// # Light buffers #
		/* ##################################### */

		// <Function>
		//		loadLightSetup
		//
		// <Description>
		//		This loads the lights and information from
		//		the submitted @LightSetup.
		//
		// <Input>
		//		lightSetup::
		//			The @Light buffer structs are filled with
		//			the information form this @LightSetup.
		//
		void loadLightSetup(const LightSetup& lightSetup);

		// <Function>
		//		getVSLightBuffer
		//
		// <Return>
		//		This returns the current @Light buffer
		//		of the vertex shader.
		//
		inline ZA_VS_LIGHT_BUFFER getVSLightBuffer() const;

		// <Function>
		//		getPSLightBuffer
		//
		// <Return>
		//		This returns the current @Light buffer
		//		of the pixel shader.
		//
		inline ZA_PS_LIGHT_BUFFER getPSLightBuffer() const;

		/* ##################################### */
		// # Material buffer #
		/* ##################################### */

		// <Function>
		//		loadMaterials
		//
		// <Description>
		//		This loads the materials to the @Material
		//		buffer.
		//
		// <Input>
		//		materials::
		//			The materials that should be loaded.;;
		//		count::
		//			The amount of materials that are inside the array.;;
		//
		void loadMaterials(const Material const* materials, uint count);

		// <Function>
		//		getMaterialBuffer
		//
		// <Return>
		//		This returns the current @Material buffer struct.
		//
		inline ZA_PS_MATERIAL_BUFFER getMaterialBuffer() const;

		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Util //
		/* //////////////////////////////////////////////////////////////////////////////// */

		// <Function>
		//      getShaderType
		//
		// <Description>
		//      This returns the shader type of this shader.
		//      
		ZA_SHADER_TYPE getShaderType() const override;
	};

}}
