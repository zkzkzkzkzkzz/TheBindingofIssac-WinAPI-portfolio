#include "pch.h"
#include "MyLoadLevel.h"

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
#include "MyEndingScene.h"
#include "MySound.h"
#include "components.h"
#include "MyLoadUI.h"

void MyLoadLevel::init()
{
	m_Loading = MyAssetMgr::GetInst()->LoadSound(L"LoadingSound", L"sound\\title_screen_jingle_v1_01.wav");

	MyLoadUI* pLUI = new MyLoadUI;
	pLUI->SetPos(Vec2(400.f, 220.f));
	pLUI->SetScale(Vec2(3.f, 3.f));
	pLUI->SetOffsetPos(Vec2(0.f, 0.f));
	AddObject(LAYER::UI, pLUI);

	m_SceneTime = 0.f;

	m_IsInit = false;
	m_IsFade = false;
}

void MyLoadLevel::enter()
{
	// 카메라 설정
	vLookAt = MyEngine::GetInst()->GetResolution();
	vLookAt /= 2.f;
	MyCameraMgr::GetInst()->SetLookAt(vLookAt);

	m_Loading->SetVolume(800.f);
	m_Loading->SetPosition(0.f);
	m_Loading->Play();


	if (m_IsInit == true)
	{
		init();
	}
}

void MyLoadLevel::exit()
{
	DeleteAllObjects();
}

void MyLoadLevel::tick()
{
	MyLevel::tick();

	m_SceneTime += DT;
	
	if (m_SceneTime >= 2.5f && m_SceneTime < 4.f)
	{
		if (!m_IsFade)
		{
			MyCameraMgr::GetInst()->FadeOut(0.5f);
			m_IsFade = true;
		}
	}

	else if (m_SceneTime >= 4.f)
	{
		MyCameraMgr::GetInst()->FadeIn(0.5f);
		m_Loading->Stop(true);
		ChangeLevel(LEVEL_TYPE::PLAY_LEVEL);
		m_SceneTime = 0;
	}
}
