#include "pch.h"
#include "MyPlayerUI.h"

#include "MyAssetMgr.h"
#include "MyTexture.h"
#include "components.h"


MyPlayerUI::MyPlayerUI()
	: m_Atlas(nullptr)
	, m_Atlas2(nullptr)
	, m_Atlas3(nullptr)
	, m_CutPos{}
	, m_CutSize{}
	, m_Type(UI_TYPE::HEART)
	, m_IsCutScene(false)

{
	m_Atlas = MyAssetMgr::GetInst()->LoadTexture(L"PlayerHeart", L"texture\\UI\\ui_hearts.png");
	m_Atlas2 = MyAssetMgr::GetInst()->LoadTexture(L"PickUpItemUI", L"texture\\UI\\hudpickups.png");
	m_Atlas3 = MyAssetMgr::GetInst()->LoadTexture(L"UIFont", L"texture\\Font\\pftempestasevencondensed_0.png");
}

MyPlayerUI::~MyPlayerUI()
{
}

void MyPlayerUI::tick(float _DT)
{
	Super::tick(_DT);
}

void MyPlayerUI::render(HDC _dc)
{
	if (!m_IsCutScene)
	{
		if (m_Type == UI_TYPE::HEART)
		{
			Vec2 vPos = GetPos();
			Vec2 vScale = GetScale();
			Vec2 vCutPos = GetCutPos();
			Vec2 vCutSize = GetCutSize();

			BLENDFUNCTION blend = {};
			blend.BlendOp = AC_SRC_OVER;
			blend.BlendFlags = 0;

			blend.SourceConstantAlpha = 255; // 0 ~ 255
			blend.AlphaFormat = AC_SRC_ALPHA; // 0

			AlphaBlend(_dc
				, (int)vPos.x
				, (int)vPos.y
				, int(m_Atlas->GetWidth() * vScale.x)
				, int(m_Atlas->GetHeight() * vScale.y)
				, m_Atlas->GetDC()
				, (int)vCutPos.x, (int)vCutPos.y
				, (int)vCutSize.x
				, (int)vCutSize.y
				, blend);
		}
		else if (m_Type == UI_TYPE::PICKUP)
		{
			Vec2 vPos = GetPos();
			Vec2 vScale = GetScale();
			Vec2 vCutPos = GetCutPos();
			Vec2 vCutSize = GetCutSize();

			BLENDFUNCTION blend = {};
			blend.BlendOp = AC_SRC_OVER;
			blend.BlendFlags = 0;

			blend.SourceConstantAlpha = 255; // 0 ~ 255
			blend.AlphaFormat = AC_SRC_ALPHA; // 0

			AlphaBlend(_dc
				, (int)vPos.x
				, (int)vPos.y
				, int(m_Atlas2->GetWidth() * vScale.x)
				, int(m_Atlas2->GetHeight() * vScale.y)
				, m_Atlas2->GetDC()
				, (int)vCutPos.x, (int)vCutPos.y
				, (int)vCutSize.x
				, (int)vCutSize.y
				, blend);
		}
		else if (m_Type == UI_TYPE::FONT)
		{
			Vec2 vPos = GetPos();
			Vec2 vScale = GetScale();
			Vec2 vCutPos = GetCutPos();
			Vec2 vCutSize = GetCutSize();

			BLENDFUNCTION blend = {};
			blend.BlendOp = AC_SRC_OVER;
			blend.BlendFlags = 0;

			blend.SourceConstantAlpha = 255; // 0 ~ 255
			blend.AlphaFormat = AC_SRC_ALPHA; // 0

			AlphaBlend(_dc
				, (int)vPos.x
				, (int)vPos.y
				, int(m_Atlas3->GetWidth() * vScale.x)
				, int(m_Atlas3->GetHeight() * vScale.y)
				, m_Atlas3->GetDC()
				, (int)vCutPos.x, (int)vCutPos.y
				, (int)vCutSize.x
				, (int)vCutSize.y
				, blend);
		}
		
	}
	Super::render(_dc);
}


