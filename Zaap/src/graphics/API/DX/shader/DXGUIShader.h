#pragma once

#include <Common.h>
#include <graphics/shader/GUIShader.h>
#include <graphics/API/DX/shader/DXShader.h>

namespace zaap { namespace graphics { namespace DX {
	
	class ZAAP_API DXGUIShader : public GUIShader, public DXShader
	{
	protected:
		ID3D11Buffer* m_MatrixBuffer;
		void loadTransformationMatrix() const override;
	public:
		// <Constructor>
		//		DXGUIShader
		//
		// <Description>
		//		This constructor simply sets the members to null.
		//
		DXGUIShader();

		// <Deconstructor>
		//		~DXGUIShader
		//
		// <Description>
		//		This deletes the buffers.
		//
		~DXGUIShader();

		// <Function>
		//		init
		//
		// <Description>
		//		This function internalizes this class by compiling
		//		the shader source code and creating the buffers.
		//
		// <Return>
		//		The return value is a @ZA_MULTI_RESULT that contains the
		//		combined results of the shader creating.
		//
		ZA_MULTI_RESULT init() override;

		void start() const override;
		void stop() const override;
	};

}}}
