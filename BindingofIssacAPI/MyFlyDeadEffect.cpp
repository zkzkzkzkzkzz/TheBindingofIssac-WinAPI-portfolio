#include "pch.h"
#include "MyFlyDeadEffect.h"

#include "MyAssetMgr.h"
#include "MyTimeMgr.h"
#include "MySound.h"
#include "components.h"

MyFlyDeadEffect::MyFlyDeadEffect()
	: m_Atlas(nullptr)
	, m_Animator(nullptr)
	, m_EffectTime(0.f)
	, m_FlyDead(nullptr)
{
	m_Atlas = MyAssetMgr::GetInst()->LoadTexture(L"NormalFly", L"texture\\monster\\monster_fly.png");

	m_Animator = AddComponent<MyAnimator>(L"FlyDeadAnimator");
	m_Animator->LoadAnimation(L"animdata\\FlyDeadAnim.txt");
	m_Animator->Play(L"FlyDeadAnim", false);

	m_FlyDead = MyAssetMgr::GetInst()->LoadSound(L"FlyDead", L"sound\\death_burst_small.wav");
	m_FlyDead->SetVolume(80.f);
	m_FlyDead->SetPosition(0.f);
	m_FlyDead->Play();
}

MyFlyDeadEffect::~MyFlyDeadEffect()
{
}


void MyFlyDeadEffect::tick(float _DT)
{
	Super::tick(_DT);

	m_EffectTime += _DT;

	float fTime = GetEffectTime();

	if (fTime >= 0.7f)
	{
		m_EffectTime = 0;
		Destroy();
	}
}

void MyFlyDeadEffect::render(HDC _dc)
{
	Super::render(_dc);
}


