#include "pch.h"
#include "NormalFly.h"

#include "MyAssetMgr.h"

#include "NMIdle.h"
#include "NMTrace.h"

#include "components.h"

NormalFly::NormalFly()
	: m_Atlas(nullptr)
	, m_Animator(nullptr)
	, m_AI(nullptr)
{
	m_Atlas = MyAssetMgr::GetInst()->LoadTexture(L"NormalFly", L"texture\\monster\\monster_fly.png");

	m_Animator = AddComponent<MyAnimator>(L"NormalFlyAnimator");
	m_Animator->LoadAnimation(L"animdata\\NormalFlyAnim.txt");
	m_Animator->Play(L"NormalFlyAnim", true);

	m_Collider = AddComponent<MyCollider>(L"NormalFlyCollider");
	m_Collider->SetScale(Vec2(28.f, 28.f));
	m_Collider->SetOffsetPos(Vec2(0.f, -14.f));

	m_AI = AddComponent<MyStateMachine>(L"NormalFlyAI");
	m_AI->AddState((UINT)NormalMons_STATE::IDLE, new NMIdle);
	m_AI->AddState((UINT)NormalMons_STATE::TRACE, new NMTrace);
}

NormalFly::NormalFly(const NormalFly& _Origin)
	: MyMonster(_Origin)
	, m_Atlas(_Origin.m_Atlas)
	, m_Animator(nullptr)
	, m_AI(nullptr)
{
	m_Animator = GetComponent<MyAnimator>();
	m_AI = GetComponent<MyStateMachine>();
}

NormalFly::~NormalFly()
{
}

void NormalFly::begin()
{
	Vec2 vPos = GetPos();
	m_AI->AddDataToBlackboard(L"Initial Position", vPos);
	m_AI->AddDataToBlackboard(L"Detect Range", 1000.f);
	m_AI->AddDataToBlackboard(L"Speed", 50.f);

	m_AI->ChangeState((UINT)NormalMons_STATE::IDLE);
}

void NormalFly::tick(float _DT)
{
	Super::tick(_DT);
}

void NormalFly::render(HDC _dc)
{
	Super::render(_dc);
}

void NormalFly::BeginOverlap(MyCollider* _OwnCol, MyObject* _OtherObj, MyCollider* _OtherCol)
{
}