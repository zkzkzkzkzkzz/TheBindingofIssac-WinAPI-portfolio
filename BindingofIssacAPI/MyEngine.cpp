#include "pch.h"
#include "MyEngine.h"

// Manager
#include "MyTimeMgr.h"
#include "MyKeyMgr.h"
#include "MyAssetMgr.h"
#include "MyLevelMgr.h"
#include "MyPathMgr.h"
#include "MyTaskMgr.h"
#include "MyCollisionMgr.h"
#include "MyGCMgr.h"
#include "MyLogMgr.h"
#include "MyCameraMgr.h"
#include "MyUIMgr.h"
#include "MySoundMgr.h"
		  
#include "MyTexture.h"

MyEngine::MyEngine()
	: m_hWnd(nullptr)
	, m_ptResolution{}
	, m_DC(nullptr)
	, m_bDebugRender(true)
	, m_arrPen{}
{
}

MyEngine::~MyEngine()
{
	ReleaseDC(m_hWnd, m_DC);

	for (UINT i = 0; i < (UINT)PEN_TYPE::END; ++i)
	{
		DeleteObject(m_arrPen[i]);
	}
}


void MyEngine::CreateDefaultGDI()
{
	m_arrPen[(UINT)PEN_TYPE::RED_PEN] = CreatePen(PS_SOLID, 1, RGB(255, 20, 20));
	m_arrPen[(UINT)PEN_TYPE::GREEN_PEN] = CreatePen(PS_SOLID, 1, RGB(20, 255, 20));
	m_arrPen[(UINT)PEN_TYPE::BLUE_PEN] = CreatePen(PS_SOLID, 1, RGB(20, 20, 255));
}

void MyEngine::init(HWND _hWnd, POINT _ptResolution)
{
	m_hWnd = _hWnd;
	ChangeWindowSize(_ptResolution, false);
	ShowWindow(m_hWnd, true);

	// DC : Device Context
	// pen : Black 
	// brush : White
	// Bitmap(그림 그릴 곳) : 핸들에 해당하는 윈도우 비트맵
	m_DC = GetDC(m_hWnd);

	// 추가 비트맵 버퍼
	m_SubTex = MyAssetMgr::GetInst()->CreateTexture(L"SubTex", m_ptResolution.x, m_ptResolution.y);

	// Manager 초기화
	MyTimeMgr::GetInst()->init();
	MyKeyMgr::GetInst()->init();
	MyPathMgr::init();
	//MySoundMgr::GetInst()->init();
	MyLevelMgr::GetInst()->init();

	// Default GDI Object 생성
	CreateDefaultGDI();
}

void MyEngine::tick()
{
	// Manager Update
	MyTimeMgr::GetInst()->tick();
	MyKeyMgr::GetInst()->tick();
	MyCameraMgr::GetInst()->tick();

	if (KEY_TAP(NUM8))
	{
		m_bDebugRender ? m_bDebugRender = false : m_bDebugRender = true;
	}


	// LevelMgr
	MyLevelMgr::GetInst()->tick();
	MyCollisionMgr::GetInst()->tick();

	//MyUIMgr::GetInst()->tick();
	MyLevelMgr::GetInst()->render(m_SubTex->GetDC());

	// Camera render
	MyCameraMgr::GetInst()->render(m_SubTex->GetDC());

	// m_SubDC -> m_DC 로 비트맵 복사
	BitBlt(MyEngine::GetInst()->GetMainDC()
		, 0, 0
		, m_ptResolution.x, m_ptResolution.y
		, m_SubTex->GetDC()
		, 0, 0, SRCCOPY);

	// Task Execute
	MyTaskMgr::GetInst()->tick();

	// CG
	MyGCMgr::GetInst()->tick();
}


void MyEngine::ChangeWindowSize(POINT _ptResolution, bool _bMenu)
{
	m_ptResolution = _ptResolution;

	RECT rt = { 0, 0, _ptResolution.x, _ptResolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, _bMenu);
	SetWindowPos(m_hWnd, nullptr, 10, 10, rt.right - rt.left, rt.bottom - rt.top, 0);
}