#include "GUIRenderer.h"

#include "API/DX/DXGUIRenderer.h"

#include "API/Context.h"
#include "API/Texture2D.h"

#include <util/Log.h>

namespace zaap { namespace graphics {
	ZA_RESULT GUIRenderer::CreateNewInstance(GUIRenderer** instance)
	{
		ZA_ASSERT(instance);
		ZA_ASSERT(!(*instance));

		*instance = new DX::DXGUIRenderer();

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
		//TODO do this target swap thing of a bob
	}

	void GUIRenderer::finishRendering()
	{
		m_GUIShader->stop();
	}

	void GUIRenderer::setTexure(API::Texture2D* texture) const
	{
		ZA_ASSERT(texture);
		texture->bind(m_GUIShader->getTextureSlot());
	}
}}
