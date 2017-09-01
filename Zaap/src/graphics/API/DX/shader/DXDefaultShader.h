#pragma once

#include <Common.h>
#include <graphics/shader/DefaultShader.h>
#include "DXShader.h"


namespace zaap { namespace graphics { namespace DX {
	
	class ZAAP_API DXDefaultShader : public DefaultShader, public DXShader
	{
		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Buffers //
		/* //////////////////////////////////////////////////////////////////////////////// */
	protected:
		/* ##################################### */
		// # Matrix buffer #
		/* ##################################### */

		ID3D11Buffer* m_MatrixBuffer;
		void loadMatrixBuffer() const override;

		/* ##################################### */
		// # Scene buffer #
		/* ##################################### */

		ID3D11Buffer* m_SceneBuffer;
		void loadSceneBuffer() const override;

		/* ##################################### */
		// # Light buffers #
		/* ##################################### */

		ID3D11Buffer* m_VSLightBuffer;
		ID3D11Buffer* m_PSLightBuffer;
		void loadLightBuffers() const override;

		/* ##################################### */
		// # Material buffer #
		/* ##################################### */

		ID3D11Buffer* m_MaterialBuffer;
		void loadMaterialBuffer() const override;

		/* //////////////////////////////////////////////////////////////////////////////// */
		// // Initialization //
		/* //////////////////////////////////////////////////////////////////////////////// */
	public:
		// <Constructor>
		//		DXDefaultShader
		//
		// <Description>
		//		This constructor simply sets the members to null.
		//
		DXDefaultShader();

		// <Destructor>
		//		~DXShader
		//
		// <Description>
		//		This deletes the buffers.
		//
		~DXDefaultShader();

		// <Function>
		//		init
		//
		// <Description>
		//		This function internalizes this class by compiling
		//		the shader source code and creating the buffers.
		//
		// <Return>
		//		The return value is a @ZA_MULTI_RESULT that contains the
		//		combined results of the shader creation.
		//
		ZA_MULTI_RESULT init();

		void start() const override;
		void stop() const override;
	};
}}}
