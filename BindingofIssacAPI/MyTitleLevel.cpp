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
#include "TitleUI.h"
#include "MyTexture.h"
#include "components.h"

void MyTitleLevel::init()
{
	MyBackGround* pBG = new MyBackGround;
	pBG->SetPos(Vec2(0.f, 0.f));
	AddObject(LAYER::MAP, pBG);

	TitleUI* pTitle = new TitleUI;
	pTitle->SetPos(Vec2(470.f, 380.f));
	AddObject(LAYER::UI, pTitle);

	m_CurScreen = (int)TITLE_TYPE::TITLE;

	m_Speed = 10000.f;

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
			MyCameraMgr::GetInst()->ScrollDown(0.65f);
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
			MyCameraMgr::GetInst()->ScrollUp(0.65f);
			m_CurScreen = (int)TITLE_TYPE::TITLE;
		}
	}
}