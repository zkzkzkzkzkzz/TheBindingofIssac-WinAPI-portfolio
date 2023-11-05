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
		m_vecMenu.push_back(pTexTitle);
		AddObject(LAYER::UI, pTexTitle);
	}
	
	m_CurScreen = (int)TITLE_TYPE::TITLE;

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
			MyCameraMgr::GetInst()->ScrollDown(0.55f);
			m_CurScreen = (int)TITLE_TYPE::MENU;
		}
	}
	else if (m_CurScreen == (int)TITLE_TYPE::MENU)
	{
		if (KEY_TAP(SPACE))
		{
			
			ChangeLevel(LEVEL_TYPE::PLAY_LEVEL);
		}
		else if (KEY_TAP(ESC))
		{
			MyCameraMgr::GetInst()->ScrollUp(0.55f);
			m_CurScreen = (int)TITLE_TYPE::TITLE;
		}
	}
}