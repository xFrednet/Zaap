#include "Input.h"

namespace zaap {

	//mouse
	Vec2 Input::m_MousePosition(0, 0);
	Vec2 Input::m_MouseMotion(0, 0);
	bool Input::m_MouseButtonPressed[ZAAP_MOUSE_BUTTON_COUNT_SUPPORTED] = {false};

	//keyboard
	bool Input::m_KeysDown[ZAAP_KEYBOARD_KEY_COUNT_SUPPORTED] = { false };
	bool Input::m_KeysLastDown[ZAAP_KEYBOARD_KEY_COUNT_SUPPORTED] = { false };

	//window callback
	std::vector<WindowCallback> Input::s_WindowCallbacks;

	void Input::Init()
	{
	}
	void Input::Update()
	{
		memcpy(m_KeysLastDown, m_KeysDown, sizeof(bool) * ZAAP_KEYBOARD_KEY_COUNT_SUPPORTED);
		m_MouseMotion.X = 0;
		m_MouseMotion.Y = 0;
	}

	//clear
	void Input::ClearKeys()
	{
		//keyboard
		memset(m_KeysDown, false, sizeof(bool) * ZAAP_KEYBOARD_KEY_COUNT_SUPPORTED);
		memset(m_KeysLastDown, false, sizeof(bool) * ZAAP_KEYBOARD_KEY_COUNT_SUPPORTED);
	}
	void Input::ClearButtons()
	{
		//mouse
		memset(m_MouseButtonPressed, false, sizeof(bool) * ZAAP_MOUSE_BUTTON_COUNT_SUPPORTED);
	}

	//
	// Mouse
	//
	void Input::MouseButtonEvent(uint button, bool state)
	{
		if (button < 0 || button >= ZAAP_MOUSE_BUTTON_COUNT_SUPPORTED) return;

		m_MouseButtonPressed[button] = state;
	}
	void Input::MouseMotionEvent(uint mouseX, uint mouseY)
	{
		m_MouseMotion.X += float(m_MousePosition.X - mouseX);
		m_MouseMotion.Y += float(m_MousePosition.Y - mouseY);

		m_MousePosition.X = float(mouseX);
		m_MousePosition.Y = float(mouseY);
	}
	Vec2 Input::GetMouseMotion()
	{
		return m_MouseMotion;
	}
	bool Input::IsButtonPressed(uint button)
	{
		if (button < 0 || button >= ZAAP_MOUSE_BUTTON_COUNT_SUPPORTED) return false;

		return m_MouseButtonPressed[button];
	}

	//
	// Keyboard
	//
	void Input::KeyEvent(uint key, bool state)
	{
		if (key >= ZAAP_KEYBOARD_KEY_COUNT_SUPPORTED) return;

		m_KeysDown[key] = state;
	}
	bool Input::IsKeyDown(int key)
	{
		if (key < 0 && key >= ZAAP_KEYBOARD_KEY_COUNT_SUPPORTED) return false;

		return m_KeysDown[key];
	}
	bool Input::IsKeyPressed(int key)
	{
		if (key < 0 && key >= ZAAP_KEYBOARD_KEY_COUNT_SUPPORTED) return false;

		return m_KeysDown[key] && !m_KeysLastDown[key];
	}

	//
	// Window callback
	//
	void Input::AddWindowCallback(zaap::WindowCallback windowCallback)
	{
		s_WindowCallbacks.push_back(windowCallback);
	}
	void Input::WindowCallback(const Event& windowEvent)
	{
		for (uint i = 0; i < s_WindowCallbacks.size(); i++)
			s_WindowCallbacks[i](windowEvent);
	}
}
