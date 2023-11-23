#include "pch.h"
#include "MyScene.h"

#include "MyAssetMgr.h"
#include "MyTimeMgr.h"
#include "MyLevelMgr.h"
#include "MyLevel.h"
#include "MyLayer.h"
#include "MyRoom.h"
#include "MyDoor.h"
#include "MySound.h"
#include "components.h"
#include "MyPlayerUI.h"

MyScene::MyScene()
	: m_Atlas(nullptr)
	, m_Animator(nullptr)
	, m_SceneTime(0.f)
	, m_Summon(nullptr)
	, m_DOpenSound(nullptr)
	, m_DCloseSound(nullptr)
	, m_BossFight(nullptr)
	, m_HideUI(false)
{
	m_Atlas = MyAssetMgr::GetInst()->LoadTexture(L"Scene", L"texture\\UI\\BossCutScene.png");

	m_Animator = AddComponent<MyAnimator>(L"SceneAnimator");
	//m_Animator->CreateAnimation(L"SceneAnim", m_Atlas, Vec2(0.f, 0.f), Vec2(512, 340), Vec2(0.f, 0.f), 0.03f, 86);
	//m_Animator->SaveAnimations(L"animdata");
	m_Animator->LoadAnimation(L"animdata\\SceneAnim.txt");
	m_Animator->Play(L"SceneAnim", false);

	m_DOpenSound = MyAssetMgr::GetInst()->LoadSound(L"DoorOpenSound", L"sound\\door_heavy_open.wav");
	m_DCloseSound = MyAssetMgr::GetInst()->LoadSound(L"DoorCloseSound", L"sound\\door_heavy_close.wav");
	m_BossFight = MyAssetMgr::GetInst()->LoadSound(L"BossFight", L"sound\\basic-boss-fight.wav");
	m_Summon = MyAssetMgr::GetInst()->LoadSound(L"BossSummon", L"sound\\summonsound.wav");
}

MyScene::~MyScene()
{
}


void MyScene::tick(float _DT)
{
	Super::tick(_DT);

	auto UIobjects = MyLevelMgr::GetInst()->GetCurLevel()->GetLayer((UINT)LAYER::UI)->GetObjects();

	if (m_HideUI == false)
	{
		for (size_t i = 0; i < UIobjects.size(); ++i)
		{
			dynamic_cast<MyPlayerUI*>(UIobjects[i])->SetCutScene(true);
		}

		m_HideUI = true;
	}

	m_SceneTime += _DT;

	float fTime = GetSceneTime();

	if (fTime >= 3.5f)
	{
		auto objects = MyLevelMgr::GetInst()->GetCurLevel()->GetLayer((UINT)LAYER::ROOM)->GetObjects();
		
		dynamic_cast<MyRoom*>(objects[(UINT)ROOM_TYPE::BOSS])->SetMonPos();

		if (!m_BossFight->IsPlayed())
		{
			m_DCloseSound->SetVolume(60.f);
			m_DCloseSound->SetPosition(0.f);
			m_DCloseSound->Play(false);

			m_BossFight->SetVolume(60.f);
			m_BossFight->SetPosition(0.f);
			m_BossFight->Play(true);
			m_BossFight->SetPlayed(true);

			m_Summon->SetVolume(60.f);	
			m_Summon->SetPosition(0.f);
			m_Summon->Play(false);
		}

		for (size_t i = 0; i < UIobjects.size(); ++i)
		{
			dynamic_cast<MyPlayerUI*>(UIobjects[i])->SetCutScene(false);
		}

		m_SceneTime = 0;
		Destroy();
	}
}

void MyScene::render(HDC _dc)
{
	Super::render(_dc);
}
