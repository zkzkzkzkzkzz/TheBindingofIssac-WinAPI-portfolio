#include "pch.h"
#include "MyCollider.h"

#include "MyEngine.h"
#include "MyLevelMgr.h"
#include "MyCameraMgr.h"
		  
#include "MyLevel.h"
#include "MyLayer.h"

#include "MyObject.h"


MyCollider::MyCollider(MyObject* _Owner)
	: MyComponent(_Owner)
	, m_iCollisionCount(0)
{

}

MyCollider::MyCollider(const MyCollider& _Origin)
	: MyComponent(_Origin)
	, m_vOffsetPos(_Origin.m_vOffsetPos)
	, m_vScale(_Origin.m_vScale)
	, m_vFinalPos(_Origin.m_vFinalPos)
	, m_iCollisionCount(0)
{
}

MyCollider::~MyCollider()
{

}

void MyCollider::finaltick(float _DT)
{
	Vec2 vOwnerPos = GetOwner()->GetPos();

	m_vFinalPos = vOwnerPos + m_vOffsetPos;

	// 현재 속해있는 레이어에 충돌체(본인) 를 등록
	int iLayerIdx = GetOwner()->GetLayerIdx();

	// Collider 를 보유하고 있는 오브젝트가 레벨 소속이 아닌데 Finaltick 이 호출된 경우
	assert(!(iLayerIdx < 0));
	MyLayer* pCurLayer = MyLevelMgr::GetInst()->GetCurLevel()->GetLayer(iLayerIdx);
	pCurLayer->RegisterCollider(this);
}

void MyCollider::render(HDC _dc)
{
	if (!DEBUG_RENDER)
		return;

	SELECT_BRUSH(_dc, (HBRUSH)GetStockObject(HOLLOW_BRUSH));

	Vec2 vRenderPos = MyCameraMgr::GetInst()->GetRenderPos(m_vFinalPos);

	if (0 < m_iCollisionCount)
	{
		SELECT_PEN(_dc, PEN_TYPE::RED_PEN);

		// render
		Rectangle(_dc, int(vRenderPos.x - m_vScale.x / 2.f)
			, int(vRenderPos.y - m_vScale.y / 2.f)
			, int(vRenderPos.x + m_vScale.x / 2.f)
			, int(vRenderPos.y + m_vScale.y / 2.f));
	}
	else
	{
		SELECT_PEN(_dc, PEN_TYPE::GREEN_PEN);

		// render
		Rectangle(_dc, int(vRenderPos.x - m_vScale.x / 2.f)
			, int(vRenderPos.y - m_vScale.y / 2.f)
			, int(vRenderPos.x + m_vScale.x / 2.f)
			, int(vRenderPos.y + m_vScale.y / 2.f));
	}
}


void MyCollider::BeginOverlap(MyCollider* _OtherCol)
{
	++m_iCollisionCount;
	GetOwner()->BeginOverlap(this, _OtherCol->GetOwner(), _OtherCol);
}

void MyCollider::Overlap(MyCollider* _OtherCol)
{
	GetOwner()->Overlap(this, _OtherCol->GetOwner(), _OtherCol);
}

void MyCollider::EndOverlap(MyCollider* _OtherCol)
{
	--m_iCollisionCount;
	GetOwner()->EndOverlap(this, _OtherCol->GetOwner(), _OtherCol);
}