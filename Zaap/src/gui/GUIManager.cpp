#include "GUIManager.h"
#include <util/Log.h>

namespace zaap { namespace gui {
	GUIManager::GUIManager()
		: m_Renderer(nullptr)
	{
	}
	ZA_RESULT GUIManager::init()
	{
		ZA_ASSERT(!m_Renderer);
		if (m_Renderer)
			return ZA_ERROR_GUIMANAGER_ERROR;

		ZA_RESULT zr = graphics::GUIRenderer::CreateNewInstance(&m_Renderer);
		ZA_ASSERT(m_Renderer);

		return zr;
	}

	GUIManager::~GUIManager()
	{
		delete m_Renderer;
		
		while (!m_Members.empty())
		{
			delete m_Members[0];
			m_Members.erase(m_Members.begin());
		}
	}

	/* //////////////////////////////////////////////////////////////////////////////// */
	// // Util //
	/* //////////////////////////////////////////////////////////////////////////////// */
	void GUIManager::render()
	{
		if (m_Members.size() == 0)
			return;

		m_Renderer->startRenderer();

		for (GUIComponent* component : m_Members)
			component->render(m_Renderer);

		m_Renderer->finishRendering();
	}
	void GUIManager::update()
	{
		for (GUIComponent* component : m_Members)
			component->update();
	}

	/* //////////////////////////////////////////////////////////////////////////////// */
	// // Members //
	/* //////////////////////////////////////////////////////////////////////////////// */
	GUIComponent* GUIManager::findComponentByID(const String& ID)
	{
		GUIComponent* component;
		for (GUIComponent* child : m_Members)
		{
			if (child->getID() == ID)
				return child;

			component = child->findComponentByID(ID);
			if (component)
				return component;
		}

		return nullptr;
	}
	void GUIManager::add(GUIComponent* component)
	{
		ZA_ASSERT(component);
		if (component)
		{
			m_Members.push_back(component);
			component->updateVertexBuffer();
		}
	}
	void GUIManager::remove(GUIComponent* component)
	{
		remove(component->getID());
	}
	void GUIManager::remove(const String& ID)
	{
		uint size = m_Members.size();
		for (uint i = 0; i < size; i++)
		{
			if (m_Members[i]->getID() == ID)
			{
				m_Members.erase(m_Members.begin() + i);
				break;
			}
		}
	}
}}
