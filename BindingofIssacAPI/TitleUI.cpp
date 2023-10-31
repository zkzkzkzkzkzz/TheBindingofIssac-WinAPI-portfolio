#include "pch.h"
#include "TitleUI.h"

#include "MyAssetMgr.h"

#include "MyTexture.h"
#include "components.h"

TitleUI::TitleUI()
	: m_Atlas(nullptr)
	, m_Animator(nullptr)
{
	m_Atlas = MyAssetMgr::GetInst()->LoadTexture(L"Titlemenu", L"texture\\UI\\titlemenu.png");
	
	m_Animator = AddComponent<MyAnimator>(L"TitleAnimator");

	m_Animator->LoadAnimation(L"animdata\\TitleAnim.txt");
	m_Animator->Play(L"TitleAnim", true);
}

TitleUI::~TitleUI()
{
}

void TitleUI::tick(float _DT)
{
	Super::tick(_DT);
	Vec2 vPos = GetPos();
	SetPos(vPos);
}

void TitleUI::render(HDC _dc)
{
	Super::render(_dc);
}