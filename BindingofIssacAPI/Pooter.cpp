#include "pch.h"
#include "Pooter.h"

#include "MyAssetMgr.h"

#include "NMIdle.h"
#include "NMTrace.h"

#include "components.h"

Pooter::Pooter()
	: m_Atlas(nullptr)
	, m_Animator(nullptr)
	, m_AI(nullptr)
{
	m_Atlas = MyAssetMgr::GetInst()->LoadTexture(L"Pooter", L"texture\\monster\\monster_pooter.png");

	m_Animator = AddComponent<MyAnimator>(L"PooterAnimator");
	m_Animator->LoadAnimation(L"animdata\\PooterLeftAnim.txt");
	m_Animator->LoadAnimation(L"animdata\\PooterRightAnim.txt");
	m_Animator->Play(L"PooterRightAnim", true);

	m_Collider = AddComponent<MyCollider>(L"NormalFlyCollider");
	m_Collider->SetScale(Vec2(28.f, 32.f));
	m_Collider->SetOffsetPos(Vec2(0.f, -15.f));

	m_AI = AddComponent<MyStateMachine>(L"NormalFlyAI");
	m_AI->AddState((UINT)NormalMons_STATE::IDLE, new NMIdle);
	m_AI->AddState((UINT)NormalMons_STATE::TRACE, new NMTrace);
}

Pooter::Pooter(const Pooter& _Origin)
	: MyMonster(_Origin)
	, m_Atlas(_Origin.m_Atlas)
	, m_Animator(nullptr)
	, m_AI(nullptr)
{
	m_Animator = GetComponent<MyAnimator>();
	m_AI = GetComponent<MyStateMachine>();
}

Pooter::~Pooter()
{
}

void Pooter::begin()
{
	Vec2 vPos = GetPos();
	m_AI->AddDataToBlackboard(L"Initial Position", vPos);
	m_AI->AddDataToBlackboard(L"Detect Range", 1000.f);
	m_AI->AddDataToBlackboard(L"Speed", 10.f);

	m_AI->ChangeState((UINT)NormalMons_STATE::IDLE);
}

void Pooter::tick(float _DT)
{
	Super::tick(_DT);
}

void Pooter::render(HDC _dc)
{
	Super::render(_dc);
}

void Pooter::BeginOverlap(MyCollider* _OwnCol, MyObject* _OtherObj, MyCollider* _OtherCol)
{
}