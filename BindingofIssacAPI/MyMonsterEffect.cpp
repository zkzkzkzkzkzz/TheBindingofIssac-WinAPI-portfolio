#include "pch.h"
#include "MyMonsterEffect.h"

#include "MyAssetMgr.h"
#include "MyTimeMgr.h"
#include "components.h"

MyMonsterEffect::MyMonsterEffect()
	: m_Atlas(nullptr)
	, m_EffectAnimator(nullptr)
	, m_EffectTime(0.f)
{
	m_Atlas = MyAssetMgr::GetInst()->LoadTexture(L"MonsterTears", L"texture\\Effect\\effect_bloodtear.png");

	m_EffectAnimator = AddComponent<MyAnimator>(L"MonsterTearsDestroyAnimator");
	m_EffectAnimator->LoadAnimation(L"animdata\\MonsterTearsDestroy.txt");
	m_EffectAnimator->Play(L"MonsterTearsDestroy", false);
}

MyMonsterEffect::~MyMonsterEffect()
{
}

void MyMonsterEffect::tick(float _DT)
{
	Super::tick(_DT);

	m_EffectTime += _DT;

	float fTime = GetEffectTime();

	if (fTime >= 1.f)
	{
		m_EffectTime = 0;
		Destroy();
	}
}

void MyMonsterEffect::render(HDC _dc)
{
	Super::render(_dc);
}