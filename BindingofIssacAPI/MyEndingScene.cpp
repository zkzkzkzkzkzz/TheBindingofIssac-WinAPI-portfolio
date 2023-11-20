#include "pch.h"
#include "MyEndingScene.h"

#include "MyAssetMgr.h"
#include "MyLevelMgr.h"
#include "MyLevel.h"
#include "MyLayer.h"
#include "MyRoom.h"
#include "MyTimeMgr.h"
#include "components.h"

MyEndingScene::MyEndingScene()
	: m_Atlas(nullptr)
	, m_Animator(nullptr)
	, m_SceneTime(0.f)
{
	m_Atlas = MyAssetMgr::GetInst()->LoadTexture(L"EndingScene", L"texture\\UI\\EndingScene.png");

	m_Animator = AddComponent<MyAnimator>(L"EndingSceneAnimator");
	//m_Animator->CreateAnimation(L"EndingSceneAnim", m_Atlas, Vec2(0.f, 0.f), Vec2(480.f, 320.f), Vec2(0.f, 0.f), 0.03f, 400);
	//m_Animator->SaveAnimations(L"animdata");
	m_Animator->LoadAnimation(L"animdata\\EndingSceneAnim.txt");
	m_Animator->Play(L"EndingSceneAnim", false);
}

MyEndingScene::~MyEndingScene()
{
}

void MyEndingScene::tick(float _DT)
{
	Super::tick(_DT);

	m_SceneTime += _DT;

	float fTime = GetSceneTime();

	if (fTime >= 20.f)
	{
		m_SceneTime = 0;
		Destroy();
	}
}

void MyEndingScene::render(HDC _dc)
{
	Super::render(_dc);
}
