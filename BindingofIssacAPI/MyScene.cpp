#include "pch.h"
#include "MyScene.h"

#include "MyAssetMgr.h"
#include "MyLevelMgr.h"
#include "MyLevel.h"
#include "MyLayer.h"
#include "MyRoom.h"
#include "MyTimeMgr.h"
#include "components.h"

MyScene::MyScene()
	: m_Atlas(nullptr)
	, m_Animator(nullptr)
	, m_SceneTime(0.f)
{
	m_Atlas = MyAssetMgr::GetInst()->LoadTexture(L"Scene", L"texture\\UI\\BossCutScene.png");

	m_Animator = AddComponent<MyAnimator>(L"SceneAnimator");
	//m_Animator->CreateAnimation(L"SceneAnim", m_Atlas, Vec2(0.f, 0.f), Vec2(512, 340), Vec2(0.f, 0.f), 0.03f, 86);
	//m_Animator->SaveAnimations(L"animdata");
	m_Animator->LoadAnimation(L"animdata\\SceneAnim.txt");
	m_Animator->Play(L"SceneAnim", false);
}

MyScene::~MyScene()
{
}


void MyScene::tick(float _DT)
{
	Super::tick(_DT);

	m_SceneTime += _DT;

	float fTime = GetSceneTime();

	if (fTime >= 3.5f)
	{
		m_SceneTime = 0;
		Destroy();

		auto objects = MyLevelMgr::GetInst()->GetCurLevel()->GetLayer((UINT)LAYER::ROOM)->GetObjects();
		dynamic_cast<MyRoom*>(objects[(UINT)ROOM_TYPE::BOSS])->SetMonPos();
	}
}

void MyScene::render(HDC _dc)
{
	Super::render(_dc);
}
