#include "pch.h"
#include "MySoundMgr.h"

#include "MyEngine.h"
#include "MySound.h"

MySoundMgr::MySoundMgr()
	: m_pSound(nullptr)
	, m_pBGM(nullptr)
{
}

MySoundMgr::~MySoundMgr()
{
}

int MySoundMgr::init(void)
{
	if (FAILED(DirectSoundCreate8(NULL, &m_pSound, NULL)))
	{
		MessageBox(NULL, L"사운드 디바이스 생성 실패", L"SYSTEM ERROR", MB_OK);
		return false;
	}

	// 사운드 협조레벨 설정
	HWND hWnd = MyEngine::GetInst()->GetMainWind();
	if (FAILED(m_pSound->SetCooperativeLevel(hWnd, DISCL_EXCLUSIVE)))
	{
		MessageBox(NULL, L"사운드 매니저 초기화 실패", L"SYSTEM ERROR", MB_OK);
		return false;
	}

	return true;
}

void MySoundMgr::RegisterToBGM(MySound* _pSound)
{
	if (m_pBGM != nullptr)
	{
		m_pBGM->Stop(true);
	}

	m_pBGM = _pSound;
}