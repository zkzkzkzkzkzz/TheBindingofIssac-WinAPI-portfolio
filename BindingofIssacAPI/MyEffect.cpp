#include "pch.h"
#include "MyEffect.h"

#include "MyAssetMgr.h"
#include "MyTimeMgr.h"
#include "MySound.h"
#include "components.h"

MyEffect::MyEffect()
	: m_Atlas(nullptr)
	, m_EffectAnimator(nullptr)
	, m_EffectTime(0.f)
	, m_DestroySound(nullptr)
{
	m_Atlas = MyAssetMgr::GetInst()->LoadTexture(L"Tears", L"texture\\Effect\\effect_tearpoof.png");

	m_EffectAnimator = AddComponent<MyAnimator>(L"TearsDestroyAnimator");
	m_EffectAnimator->LoadAnimation(L"animdata\\TearsDestroy.txt");
	m_EffectAnimator->Play(L"TearsDestroy", false);

	m_DestroySound = MyAssetMgr::GetInst()->LoadSound(L"PTDestroySound", L"sound\\tear_block.wav");
	m_DestroySound->SetVolume(100.f);
	m_DestroySound->SetPosition(0.f);
	m_DestroySound->Play();
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