#include "pch.h"
#include "MyFKDeadEffect.h"

#include "MyAssetMgr.h"
#include "MyTimeMgr.h"
#include "MySound.h"
#include "components.h"

MyFKDeadEffect::MyFKDeadEffect()
	: m_Atlas(nullptr)
	, m_Animator(nullptr)
	, m_EffectTime(0.f)
	, m_FKDead(nullptr)
{
	m_Atlas = MyAssetMgr::GetInst()->LoadTexture(L"FKDead", L"texture\\effect\\effect_002_bloodpoof.png");

	m_Animator = AddComponent<MyAnimator>(L"FKDeadAnimator");
	m_Animator->LoadAnimation(L"animdata\\FKDeadAnim.txt");
	m_Animator->Play(L"FKDeadAnim", false);

	m_FKDead = MyAssetMgr::GetInst()->LoadSound(L"FKDead", L"sound\\death_burst_small.wav");
	m_FKDead->SetVolume(80.f);
	m_FKDead->SetPosition(0.f);
	m_FKDead->Play();
}

MyFKDeadEffect::~MyFKDeadEffect()
{
}


void MyFKDeadEffect::tick(float _DT)
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

void MyFKDeadEffect::render(HDC _dc)
{
	Super::render(_dc);
}


