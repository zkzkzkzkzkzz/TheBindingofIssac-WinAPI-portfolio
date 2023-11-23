#include "pch.h"
#include "MyLoadUI.h"

#include "MyAssetMgr.h"
#include "MyTexture.h"
#include "components.h"

MyLoadUI::MyLoadUI()
	: m_Atlas(nullptr)
	, m_Animator(nullptr)
	, m_AccTime(0.f)
{
	m_Atlas = MyAssetMgr::GetInst()->LoadTexture(L"LoadImage", L"texture\\UI\\loadimages.png");

	m_Animator = AddComponent<MyAnimator>(L"LoadImageAnimator");
	m_Animator->LoadAnimation(L"animdata\\LoadAnim.txt");
	m_Animator->Play(L"LoadAnim", true);
}

MyLoadUI::~MyLoadUI()
{
}

void MyLoadUI::tick(float _DT)
{
	Super::tick(_DT);

	m_AccTime += _DT;

	if (m_AccTime >= 3.f)
	{
		m_AccTime = 0.f;
		Destroy();
	}
}

void MyLoadUI::render(HDC _dc)
{
	Super::render(_dc);
}

