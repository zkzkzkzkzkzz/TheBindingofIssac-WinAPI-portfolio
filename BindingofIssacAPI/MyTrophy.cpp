#include "pch.h"
#include "MyTrophy.h"

#include "MyAssetMgr.h"
#include "MyLevelMgr.h"
#include "MyLevel.h"
#include "MyPlayLevel.h"
#include "MyTexture.h"
#include "components.h"

MyTrophy::MyTrophy()
	: m_Atlas(nullptr)
	, m_Collider(nullptr)
{
	m_Atlas = MyAssetMgr::GetInst()->LoadTexture(L"Trophy", L"texture\\Item\\trophy.png");

	m_Collider = AddComponent<MyCollider>(L"TrophyCollider");
	m_Collider->SetScale(Vec2(40.f, 30.f));
	m_Collider->SetOffsetPos(Vec2(0.f, -15.f));
}

MyTrophy::~MyTrophy()
{
}


void MyTrophy::tick(float _DT)
{
	Super::tick(_DT);
}

void MyTrophy::render(HDC _dc)
{
	Vec2 vRenderPos = GetRenderPos();
	Vec2 vScale = Vec2(2.f, 2.f);
	Vec2 vOffset = Vec2(-30.f, -100.f);

	BLENDFUNCTION blend = {};
	blend.BlendOp = AC_SRC_OVER;
	blend.BlendFlags = 0;

	blend.SourceConstantAlpha = 255; // 0 ~ 255
	blend.AlphaFormat = AC_SRC_ALPHA; // 0

	AlphaBlend(_dc
		, int(vRenderPos.x + vOffset.x), int(vRenderPos.y + vOffset.y)
		, int(m_Atlas->GetWidth() * vScale.x)
		, int(m_Atlas->GetHeight() * vScale.y)
		, m_Atlas->GetDC()
		, 0, 0
		, m_Atlas->GetWidth()
		, m_Atlas->GetHeight()
		, blend);

	Super::render(_dc);
}

void MyTrophy::BeginOverlap(MyCollider* _OwnCol, MyObject* _OtherObj, MyCollider* _OtherCol)
{
	MyPlayLevel* pLevel = dynamic_cast<MyPlayLevel*>(MyLevelMgr::GetInst()->GetCurLevel());
	pLevel->SetToInitTrue();
	ChangeLevel(LEVEL_TYPE::ENDING_LEVEL);

}


