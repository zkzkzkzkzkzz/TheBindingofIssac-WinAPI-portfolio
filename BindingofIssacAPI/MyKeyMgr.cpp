#include "pch.h"

#include "MyEngine.h"
#include "MyKeyMgr.h"

int g_KeySync[(int)KEY::KEY_END]
{
	'0',
	'1',
	'2',
	'3',
	'4',
	'5',
	'6',
	'7',
	'8',
	'9',

	VK_NUMPAD0,
	VK_NUMPAD1,
	VK_NUMPAD2,
	VK_NUMPAD3,
	VK_NUMPAD4,
	VK_NUMPAD5,
	VK_NUMPAD6,
	VK_NUMPAD7,
	VK_NUMPAD8,
	VK_NUMPAD9,

	'Q',
	'W',
	'E',
	'R',
	'T',
	'Y',
	'U',
	'I',
	'O',
	'P',

	'A',
	'S',
	'D',
	'F',
	'G',
	'H',
	'J',
	'K',
	'L',

	'Z',
	'X',
	'C',
	'V',
	'B',
	'N',
	'M',

	VK_TAB,
	VK_LSHIFT,
	VK_LMENU,
	VK_LCONTROL,
	VK_SPACE,

	VK_ESCAPE,
	VK_RETURN,
	VK_BACK,

	VK_LEFT,
	VK_RIGHT,
	VK_UP,
	VK_DOWN,

	VK_LBUTTON,
	VK_RBUTTON,
};



MyKeyMgr::MyKeyMgr()
{

}

MyKeyMgr::~MyKeyMgr()
{

}

void MyKeyMgr::init()
{
	// Capacity를 미리 확보
	// 데이터 개수도 늘려주는 resize와 다르게 공간만 늘린다
	m_vecKeyData.reserve((size_t)KEY::KEY_END);

	for (UINT i = 0; i < (UINT)KEY::KEY_END; ++i)
	{
		m_vecKeyData.push_back(FKeyData{ (KEY)i, KEY_STATE::NONE, false });
	}
}

void MyKeyMgr::tick()
{
	if (nullptr == GetFocus())
	{
		for (size_t i = 0; i < m_vecKeyData.size(); ++i)
		{
			if (KEY_STATE::TAP == m_vecKeyData[i].eState)
			{
				m_vecKeyData[i].eState = KEY_STATE::PRESSED;
			}
			else if (KEY_STATE::PRESSED == m_vecKeyData[i].eState)
			{
				m_vecKeyData[i].eState = KEY_STATE::RELEASED;
			}
			else if (KEY_STATE::RELEASED == m_vecKeyData[i].eState)
			{
				m_vecKeyData[i].eState = KEY_STATE::NONE;
			}
		}
	}
	else
	{
		for (size_t i = 0; i < m_vecKeyData.size(); ++i)
		{
			if (GetAsyncKeyState(g_KeySync[(int)m_vecKeyData[i].eKey]) & 0x8001)
			{
				// 이번 프레임에 키가 눌렸다
				if (m_vecKeyData[i].bPressed)
				{
					// bPressed가 true였을 때 -> 계속 눌린 상태
					m_vecKeyData[i].eState = KEY_STATE::PRESSED;
				}
				else
				{
					// bPressed가 false였을 때 -> 이제 처음 눌린 상태
					m_vecKeyData[i].eState = KEY_STATE::TAP;
				}

				m_vecKeyData[i].bPressed = true;
			}
			else
			{
				// 이번 프레임에 키가 눌리지 않았다
				if (m_vecKeyData[i].bPressed)
				{
					// bPressed가 true였을 때 -> 눌렀다가 이제 뗀 상태
					m_vecKeyData[i].eState = KEY_STATE::RELEASED;
				}
				else
				{
					// bPressed가 false였을 때 -> 이전에도 안눌렸고 아직도 안누른 상태
					m_vecKeyData[i].eState = KEY_STATE::NONE;
				}

				m_vecKeyData[i].bPressed = false;
			}
		}

		// 마우스 좌표 계산
		POINT pt = {};
		GetCursorPos(&pt);
		ScreenToClient(MyEngine::GetInst()->GetMainWind(), &pt);
		m_vMousePos = pt;
	}
}