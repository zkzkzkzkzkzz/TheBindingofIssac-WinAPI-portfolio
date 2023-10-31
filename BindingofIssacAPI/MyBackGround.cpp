#include "pch.h"
#include "MyBackGround.h"

#include "MyEngine.h"
#include "MyAssetMgr.h"
#include "MyTexture.h"
#include "MyAnimator.h"

MyBackGround::MyBackGround()
	: m_Atlas(nullptr)
{
	m_Atlas = MyAssetMgr::GetInst()->LoadTexture(L"TitleBG", L"texture\\UI\\TitleLevelBG.png");
}

MyBackGround::MyBackGround(const MyBackGround& _Origin)
	: MyObject(_Origin)
	, m_Atlas(_Origin.m_Atlas)
{
	
}

MyBackGround::~MyBackGround()
{
}


void MyBackGround::tick(float _DT)
{
	Super::tick(_DT);
}

void MyBackGround::render(HDC _dc)
{
	Vec2 vRenderPos = GetRenderPos();

	BLENDFUNCTION blend = {};
	blend.BlendOp = AC_SRC_OVER;
	blend.BlendFlags = 0;

	blend.SourceConstantAlpha = 255; // 0 ~ 255
	blend.AlphaFormat = AC_SRC_ALPHA; // 0

	AlphaBlend(_dc
		, (int)vRenderPos.x,(int)vRenderPos.y
		, m_Atlas->GetWidth()
		, m_Atlas->GetHeight()
		, m_Atlas->GetDC()
		, 0, 0
		, m_Atlas->GetWidth()
		, m_Atlas->GetHeight()
		, blend);

	Super::render(_dc);
}
