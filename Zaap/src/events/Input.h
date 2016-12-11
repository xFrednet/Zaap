#pragma once

#include <Common.h>
#include <Types.h>
#include <maths/Vec2.h>
#include <functional>
#include "EventManager.h"

#define ZA_MOUSE_BUTTON_COUNT_SUPPORTED 16
#define ZAAP_KEYBOARD_KEY_COUNT_SUPPORTED 256

#define ZAAP_UNKNOWN_MOUSE_POSITION -1

namespace zaap {
	
	typedef std::function<void(const Event& windowEvent)> WindowCallback;

	class ZAAP_API Input
	{
	private:
		//mouse
		static Vec2 m_MousePosition;
		static Vec2 m_MouseMotion;
		static bool m_MouseButtonPressed[ZA_MOUSE_BUTTON_COUNT_SUPPORTED];

		//keyboard
		static bool m_KeysDown[ZAAP_KEYBOARD_KEY_COUNT_SUPPORTED];
		static bool m_KeysLastDown[ZAAP_KEYBOARD_KEY_COUNT_SUPPORTED];

		//window callback
		static std::vector<WindowCallback> s_WindowCallbacks;
	public:
		static void Init(void);
		static void Update(void);
		
		static void ClearKeys(void);
		static void ClearButtons(void);

		//mouse
		static void MouseButtonEvent(uint button, bool state);
		static void MouseMotionEvent(uint mouseX, uint mouseY);
		static Vec2 GetMouseMotion();
		static bool IsButtonPressed(uint button);

		//keyboard
		static void KeyEvent(uint key, bool state);
		static bool IsKeyDown(char key);
		static bool IsKeyDown(int key);
		static bool IsKeyPressed(int Key);

		//Window callbacks
		static void AddWindowCallback(WindowCallback windowCallback);
		static void WindowCallback(const Event& windowEvent);
	};

}

#include <events/WindowEvent.h>

/*
* Mouse stuff
*/
#define ZA_MOUSE_BUTTON_1    0
#define ZA_MOUSE_BUTTON_2    1
#define ZA_MOUSE_BUTTON_3    2

#define ZA_MOUSE_LEFT        ZA_MOUSE_BUTTON_1
#define ZA_MOUSE_MIDDLE      ZA_MOUSE_BUTTON_2
#define ZA_MOUSE_RIGHT       ZA_MOUSE_BUTTON_3

/*
* Keyboard stuff
*/

#define ZA_VK_BACK           0x08
#define ZA_VK_TAB            0x09

/*
* 0x0A - 0x0B : reserved
*/

#define ZA_VK_CLEAR          0x0C
#define ZA_VK_RETURN         0x0D

#define ZA_VK_SHIFT          0x10
#define ZA_VK_CONTROL        0x11
#define ZA_VK_MENU           0x12
#define ZA_VK_PAUSE          0x13
#define ZA_VK_CAPITAL        0x14

#define ZA_VK_ESCAPE         0x1B

#define ZA_VK_CONVERT        0x1C
#define ZA_VK_NONCONVERT     0x1D
#define ZA_VK_ACCEPT         0x1E
#define ZA_VK_MODECHANGE     0x1F

#define ZA_VK_SPACE          0x20
#define ZA_VK_PRIOR          0x21
#define ZA_VK_NEXT           0x22
#define ZA_VK_END            0x23
#define ZA_VK_HOME           0x24
#define ZA_VK_LEFT           0x25
#define ZA_VK_UP             0x26
#define ZA_VK_RIGHT          0x27
#define ZA_VK_DOWN           0x28
#define ZA_VK_SELECT         0x29
#define ZA_VK_PRINT          0x2A
#define ZA_VK_EXECUTE        0x2B
#define ZA_VK_SNAPSHOT       0x2C
#define ZA_VK_INSERT         0x2D
#define ZA_VK_DELETE         0x2E
#define ZA_VK_HELP           0x2F

/*
* ZA_VK_0 - ZA_VK_9 are the same as ASCII '0' - '9' (0x30 - 0x39)
* 0x40 : unassigned
* ZA_VK_A - ZA_VK_Z are the same as ASCII 'A' - 'Z' (0x41 - 0x5A)
*/
#define ZA_VK_0              0x30
#define ZA_VK_1              0x31
#define ZA_VK_2              0x32
#define ZA_VK_3              0x33
#define ZA_VK_4              0x34
#define ZA_VK_5              0x35
#define ZA_VK_6              0x36
#define ZA_VK_7              0x37
#define ZA_VK_8              0x38
#define ZA_VK_9              0x39

#define ZA_VK_A              0x41
#define ZA_VK_B              0x42
#define ZA_VK_C              0x43
#define ZA_VK_D              0x44
#define ZA_VK_E              0x45
#define ZA_VK_F              0x46
#define ZA_VK_G              0x47
#define ZA_VK_H              0x48
#define ZA_VK_I              0x49
#define ZA_VK_J              0x4A
#define ZA_VK_K              0x4B
#define ZA_VK_L              0x4C
#define ZA_VK_M              0x4D
#define ZA_VK_N              0x4E
#define ZA_VK_O              0x4F
#define ZA_VK_P              0x50
#define ZA_VK_Q              0x51
#define ZA_VK_R              0x52
#define ZA_VK_S              0x53
#define ZA_VK_T              0x54
#define ZA_VK_U              0x55
#define ZA_VK_V              0x56
#define ZA_VK_W              0x57
#define ZA_VK_X              0x58
#define ZA_VK_Y              0x59
#define ZA_VK_Z              0x5A


#define ZA_VK_LWIN           0x5B
#define ZA_VK_RWIN           0x5C
#define ZA_VK_APPS           0x5D

/*
* 0x5E : reserved
*/

#define ZA_VK_NUMPAD0        0x60
#define ZA_VK_NUMPAD1        0x61
#define ZA_VK_NUMPAD2        0x62
#define ZA_VK_NUMPAD3        0x63
#define ZA_VK_NUMPAD4        0x64
#define ZA_VK_NUMPAD5        0x65
#define ZA_VK_NUMPAD6        0x66
#define ZA_VK_NUMPAD7        0x67
#define ZA_VK_NUMPAD8        0x68
#define ZA_VK_NUMPAD9        0x69
#define ZA_VK_MULTIPLY       0x6A
#define ZA_VK_ADD            0x6B
#define ZA_VK_SEPARATOR      0x6C
#define ZA_VK_SUBTRACT       0x6D
#define ZA_VK_DECIMAL        0x6E
#define ZA_VK_DIVIDE         0x6F
#define ZA_VK_F1             0x70
#define ZA_VK_F2             0x71
#define ZA_VK_F3             0x72
#define ZA_VK_F4             0x73
#define ZA_VK_F5             0x74
#define ZA_VK_F6             0x75
#define ZA_VK_F7             0x76
#define ZA_VK_F8             0x77
#define ZA_VK_F9             0x78
#define ZA_VK_F10            0x79
#define ZA_VK_F11            0x7A
#define ZA_VK_F12            0x7B
#define ZA_VK_F13            0x7C
#define ZA_VK_F14            0x7D
#define ZA_VK_F15            0x7E
#define ZA_VK_F16            0x7F
#define ZA_VK_F17            0x80
#define ZA_VK_F18            0x81
#define ZA_VK_F19            0x82
#define ZA_VK_F20            0x83
#define ZA_VK_F21            0x84
#define ZA_VK_F22            0x85
#define ZA_VK_F23            0x86
#define ZA_VK_F24            0x87