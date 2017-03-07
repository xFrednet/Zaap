#include "GUIRenderer.h"

#include <graphics/Color.h>
#include "API/Context.h"
#include <util/Log.h>

namespace zaap { namespace graphics {
	ZA_RESULT GUIRenderer::CreateNewInstance(GUIRenderer** instance)
	{
		//TODO *instance = new DX::DXGUIRenderer();

		return (*instance)->init();
	}

	/* //////////////////////////////////////////////////////////////////////////////// */
	// // Initialization / Deconstruction //
	/* //////////////////////////////////////////////////////////////////////////////// */
	GUIRenderer::GUIRenderer()
		: m_TargetWidth(0),
		m_TargetHeight(),
		m_RenderTargetType(ZA_RENDERER_TARGET_DEFAULT),
		m_MainTarget(nullptr),
		m_GUIBackBuffer(nullptr),
		m_GUIShader(nullptr)
	{
		m_MainTarget = API::Context::GetRenderTarget();
		m_MainTarget->addUpdateListener(ZA_METHOD_0(GUIRenderer::renderTargetUpdated));
		m_TargetWidth = m_MainTarget->getWidth();
		m_TargetHeight = m_MainTarget->getHeight();

		m_GUIBackBuffer = API::RenderTarget::Create();
		ZA_RESULT zr = m_GUIBackBuffer->createTarget(m_TargetWidth, m_TargetHeight);

		ZA_ASSERT(ZA_SUCCEDED(zr));
	}

	GUIRenderer::~GUIRenderer()
	{
		if (m_GUIShader)
		{
			m_GUIShader->stop();
			delete m_GUIShader;
		}
		if (m_GUIBackBuffer)
		{
			m_GUIBackBuffer->unbindTexture(0);
			delete m_GUIBackBuffer;
		}
	}

	void GUIRenderer::renderTargetUpdated()
	{
		m_TargetWidth = m_MainTarget->getWidth();
		m_TargetHeight = m_MainTarget->getHeight();
		m_GUIShader->setTargetSize(m_TargetWidth, m_TargetHeight);

		ZA_RESULT zr = m_GUIBackBuffer->resizeTarget(m_TargetWidth, m_TargetHeight);

		ZA_ASSERT(ZA_SUCCEDED(zr));
	}

	void GUIRenderer::startRenderer()
	{
		m_MainTarget->startTarget();
		m_GUIShader->start();
	}

	void GUIRenderer::finishRendering()
	{
		m_GUIShader->stop();
	}
}}
