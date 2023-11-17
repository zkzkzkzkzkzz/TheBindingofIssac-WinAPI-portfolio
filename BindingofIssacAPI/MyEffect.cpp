#include "pch.h"
#include "MyEffect.h"

#include "MyAssetMgr.h"
#include "MyTimeMgr.h"
#include "components.h"

MyEffect::MyEffect()
	: m_Atlas(nullptr)
	, m_EffectAnimator(nullptr)
	, m_EffectTime(0.f)
{
	m_Atlas = MyAssetMgr::GetInst()->LoadTexture(L"Tears", L"texture\\Effect\\effect_tearpoof.png");

	m_EffectAnimator = AddComponent<MyAnimator>(L"TearsDestroyAnimator");
	m_EffectAnimator->LoadAnimation(L"animdata\\TearsDestroy.txt");
	m_EffectAnimator->Play(L"TearsDestroy", false);
}

MyEffect::~MyEffect()
{

}


void MyEffect::tick(float _DT)
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

void MyEffect::render(HDC _dc)
{
	Super::render(_dc);
}