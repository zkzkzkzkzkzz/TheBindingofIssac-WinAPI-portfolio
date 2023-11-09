#include "pch.h"
#include "MyShadow.h"

#include "MyAssetMgr.h"
#include "MyObject.h"
#include "MyTexture.h"

MyShadow::MyShadow()
	: m_ShadowTex(nullptr)
	, m_Collider(nullptr)
{
	m_ShadowTex = MyAssetMgr::GetInst()->LoadTexture(L"Shadow", L"texture\\Effect\\shadow.png");

	m_Collider = AddComponent<MyCollider>(L"ShadowCollider");

	m_Collider->SetScale(Vec2(27.f, 5.f));
	m_Collider->SetOffsetPos(Vec2(-1.f, -4.f));
}

MyShadow::MyShadow(const MyShadow& _Origin)
	: MyObject(_Origin)
	, m_ShadowTex(_Origin.m_ShadowTex)
	, m_Collider(nullptr)
{
	m_Collider = GetComponent<MyCollider>();
}

MyShadow::~MyShadow()
{
}


void MyShadow::begin()
{
	wstring str = m_Collider->GetOwner()->GetName();
	if (str == L"PlayerShadow")
	{
		m_Collider->SetScale(Vec2(40.f, 20.f));
		m_Collider->SetOffsetPos(Vec2(0.f, 0.f));
	}
}

void MyShadow::tick(float _DT)
{
	Super::tick(_DT);
}

void MyShadow::render(HDC _dc)
{
	Vec2 vRenderPos = GetRenderPos();
	Vec2 vScale = GetScale();
	Vec2 vOffset = GetOffsetPos();

	BLENDFUNCTION blend = {};
	blend.BlendOp = AC_SRC_OVER;
	blend.BlendFlags = 0;

	blend.SourceConstantAlpha = 50; // 0 ~ 255
	blend.AlphaFormat = AC_SRC_ALPHA; // 0

	AlphaBlend(_dc
		, int(vRenderPos.x + vOffset.x), int(vRenderPos.y + vOffset.y)
		, int(m_ShadowTex->GetWidth() * vScale.x)
		, int(m_ShadowTex->GetHeight() * vScale.y)
		, m_ShadowTex->GetDC()
		, 0, 0
		, m_ShadowTex->GetWidth()
		, m_ShadowTex->GetHeight()
		, blend);


	Super::render(_dc);
}

