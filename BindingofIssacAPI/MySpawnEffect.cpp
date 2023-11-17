#include "pch.h"
#include "MySpawnEffect.h"

#include "MyAssetMgr.h"
#include "MyTimeMgr.h"
#include "components.h"

MySpawnEffect::MySpawnEffect()
	: m_Atlas(nullptr)
	, m_Animator(nullptr)
	, m_EffectTime(0.f)
{
	m_Atlas = MyAssetMgr::GetInst()->LoadTexture(L"MonsterSpawn", L"texture\\Effect\\effect_009_poof01.png");

	m_Animator = AddComponent<MyAnimator>(L"MonsterSpawnAnimator");
	m_Animator->LoadAnimation(L"animdata\\MonsterSpawnAnim.txt");
	m_Animator->Play(L"MonsterSpawnAnim", false);
}

MySpawnEffect::~MySpawnEffect()
{
}


void MySpawnEffect::tick(float _DT)
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

void MySpawnEffect::render(HDC _dc)
{
	Super::render(_dc);
}


