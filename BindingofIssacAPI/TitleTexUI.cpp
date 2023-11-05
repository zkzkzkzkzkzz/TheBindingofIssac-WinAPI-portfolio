#include "pch.h"
#include "TitleTexUI.h"

#include "MyEngine.h"
#include "MyAssetMgr.h"

#include "MyTexture.h"
#include "components.h"

TitleTexUI::TitleTexUI()
	: m_Menu(nullptr)
	, m_CutPos{}
	, m_Inst(nullptr)
	, m_Delegate(nullptr)
{
	m_Menu = MyAssetMgr::GetInst()->LoadTexture(L"Gamemenu", L"texture\\UI\\gamemenu.png");
}

TitleTexUI::~TitleTexUI()
{
}

void TitleTexUI::tick(float _DT)
{
	Super::tick(_DT);
}



void TitleTexUI::render(HDC _dc)
{
	Vec2 vRenderPos = GetRenderPos();
	Vec2 vScale = GetScale();
	Vec2 vCutPos = GetCutPos();

	BLENDFUNCTION blend = {};
	blend.BlendOp = AC_SRC_OVER;
	blend.BlendFlags = 0;

	blend.SourceConstantAlpha = 255; // 0 ~ 255
	blend.AlphaFormat = AC_SRC_ALPHA; // 0

	AlphaBlend(_dc
		, (int)vRenderPos.x, (int)vRenderPos.y
		, m_Menu->GetWidth() * vScale.x
		, m_Menu->GetHeight() * vScale.y
		, m_Menu->GetDC()
		, vCutPos.x, vCutPos.y
		, 116.f
		, 40.f
		, blend);

	Super::render(_dc);
}

void TitleTexUI::LBtnClicked(Vec2 _vMousePos)
{
	if (nullptr != m_CallBackFunc)
	{
		m_CallBackFunc();
	}
}
