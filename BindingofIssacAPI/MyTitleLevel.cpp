#include "pch.h"
#include "MyTitleLevel.h"

#include "MyEngine.h"

#include "MyAssetMgr.h"
#include "MyKeyMgr.h"
#include "MyLevelMgr.h"
#include "MyCameraMgr.h"
#include "MyTimeMgr.h"

#include "MyObject.h"
#include "MyBackGround.h"
#include "TitleAnimUI.h"
#include "TitleTexUI.h"
#include "MyTexture.h"
#include "components.h"

void MyTitleLevel::init()
{
	// 타이틀 배경 생성
	MyBackGround* pBG = new MyBackGround;
	pBG->SetPos(Vec2(0.f, 0.f));
	pBG->SetScale(Vec2(2.f, 2.f));
	AddObject(LAYER::MAP, pBG);

	// 타이틀 화면 애니메이션 추가
	TitleAnimUI* pAnimTitle = new TitleAnimUI;
	pAnimTitle->SetPos(Vec2(470.f, 380.f));
	pAnimTitle->SetScale(Vec2(1.f, 1.f));
	AddObject(LAYER::UI, pAnimTitle);

	// 메뉴 생성
	for (int i = 0; i < MaxMenuSize; ++i)
	{
		TitleTexUI* pTexTitle = new TitleTexUI;
		pTexTitle->SetPos(Vec2(350.f + i * 10.f, 780.f + i * 70.f));
		pTexTitle->SetScale(Vec2(0.5f, 0.1f));
		pTexTitle->SetCutPos(Vec2(32.f, 288.f + i * 50.f));
		pTexTitle->SetCutSize(Vec2(116.f, 40.f));
		AddObject(LAYER::UI, pTexTitle);
	}

	// 커서 생성
	m_Cursor = new TitleTexUI;
	m_Cursor->SetPos(Vec2(305.f, 805.f));
	m_Cursor->SetScale(Vec2(0.1f, 0.1f));
	m_Cursor->SetCutPos(Vec2(0.f, 310.f));
	m_Cursor->SetCutSize(Vec2(25.f, 25.f));
	AddObject(LAYER::UI, m_Cursor);

	m_CurScreen = (int)TITLE_TYPE::TITLE;

	// 로딩용 이미지 생성


	// 카메라 설정
	vLookAt = MyEngine::GetInst()->GetResolution();
	vLookAt /= 2.f;
	MyCameraMgr::GetInst()->SetLookAt(vLookAt);
}

void MyTitleLevel::enter()
{

}

void MyTitleLevel::exit()
{
	DeleteAllObjects();
}

void MyTitleLevel::tick()
{
	MyLevel::tick();

	if (m_CurScreen == (int)TITLE_TYPE::TITLE)
	{
		if (KEY_TAP(SPACE))
		{
			MyCameraMgr::GetInst()->ScrollDown(0.6f);
			m_CurScreen = (int)TITLE_TYPE::MENU;
		}
		else if(KEY_TAP(ESC))
		{
			DestroyWindow(MyEngine::GetInst()->GetMainWind());
		}
	}
	else if (m_CurScreen == (int)TITLE_TYPE::MENU)
	{
		if (KEY_TAP(SPACE) && m_CursorIdx == 0)
		{	
			MyCameraMgr::GetInst()->FadeIn(1.5f);

			ChangeLevel(LEVEL_TYPE::PLAY_LEVEL);
		}
		else if (KEY_TAP(ESC))
		{
			MyCameraMgr::GetInst()->ScrollUp(0.6f);
			m_CurScreen = (int)TITLE_TYPE::TITLE;
		}
		else if (KEY_TAP(DOWN))
		{
			++m_CursorIdx;
			Vec2 vPos = m_Cursor->GetPos();

			vPos.x += 10.f;
			vPos.y += 68.f;

			m_Cursor->SetPos(Vec2(vPos));

			if (m_CursorIdx >= MaxMenuSize)
			{
				m_Cursor->SetPos(Vec2(305.f, 805.f));
				m_CursorIdx = 0;
			}
		}
		else if (KEY_TAP(UP))
		{
			--m_CursorIdx;
			Vec2 vPos = m_Cursor->GetPos();

			vPos.x -= 10.f;
			vPos.y -= 68.f;

			m_Cursor->SetPos(Vec2(vPos));

			if (0 > m_CursorIdx)
			{
				m_Cursor->SetPos(Vec2(345.f, 1075.f));
				m_CursorIdx = 4;
			}
		}
	}
}
