#include "pch.h"
#include "TitleAnimUI.h"

#include "MyAssetMgr.h"

#include "MyTexture.h"
#include "components.h"

TitleAnimUI::TitleAnimUI()
	: m_Atlas(nullptr)
	, m_Animator(nullptr)
{
	m_Atlas = MyAssetMgr::GetInst()->LoadTexture(L"Titlemenu", L"texture\\UI\\titlemenu.png");

	m_Animator = AddComponent<MyAnimator>(L"TitleAnimator");

	m_Animator->LoadAnimation(L"animdata\\TitleAnim.txt");

	m_Animator->Play(L"TitleAnim", true);
}

TitleAnimUI::~TitleAnimUI()
{
}

void TitleAnimUI::tick(float _DT)
{
	Super::tick(_DT);

}



void TitleAnimUI::render(HDC _dc)
{
	Super::render(_dc);
}
