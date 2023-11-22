#include "pch.h"
#include "MyBossDeadEffect.h"

#include "MyAssetMgr.h"
#include "MyTimeMgr.h"
#include "MySound.h"
#include "components.h"

MyBossDeadEffect::MyBossDeadEffect()
	: m_Atlas(nullptr)
	, m_Animator(nullptr)
	, m_EffectTime(0.f)
	, m_BossDead(nullptr)
{
	m_Atlas = MyAssetMgr::GetInst()->LoadTexture(L"BossDead", L"texture\\effect\\effect_077_largebloodexplosion.png");

	m_Animator = AddComponent<MyAnimator>(L"BossDeadAnimator");
	m_Animator->LoadAnimation(L"animdata\\BossDeadAnim.txt");
	m_Animator->Play(L"BossDeadAnim", false);

	m_BossDead = MyAssetMgr::GetInst()->LoadSound(L"BossDead", L"sound\\boss_expolsions_2.wav");
	m_BossDead->SetVolume(80.f);
	m_BossDead->SetPosition(0.f);
	m_BossDead->Play();
}

MyBossDeadEffect::~MyBossDeadEffect()
{
}

void MyBossDeadEffect::tick(float _DT)
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

void MyBossDeadEffect::render(HDC _dc)
{
	Super::render(_dc);
}

