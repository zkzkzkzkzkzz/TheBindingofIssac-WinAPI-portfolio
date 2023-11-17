#include "pch.h"
#include "Pooter.h"

#include "MyAssetMgr.h"
#include "MyTimeMgr.h"

#include "MyTexture.h"
#include "MyTears.h"
#include "MyRoom.h"
#include "NMIdle.h"
#include "NMTrace.h"
#include "NMAttack.h"
#include "MySpawnEffect.h"
#include "MyFlyDeadEffect.h"
#include "components.h"

Pooter::Pooter()
	: m_Atlas(nullptr)
	, m_MonsterShadow(nullptr)
	, m_Animator(nullptr)
	, m_Collider(nullptr)
	, m_AI(nullptr)
	, m_AttDelayTime(2.f)
	, m_Acctime(0.f)
{
	m_Atlas = MyAssetMgr::GetInst()->LoadTexture(L"Pooter", L"texture\\monster\\monster_pooter.png");
	m_MonsterShadow = MyAssetMgr::GetInst()->LoadTexture(L"Shadow", L"texture\\Effect\\shadow.png");

	m_Animator = AddComponent<MyAnimator>(L"PooterAnimator");
	m_Animator->LoadAnimation(L"animdata\\PooterLeftAnim.txt");
	m_Animator->LoadAnimation(L"animdata\\PooterLeftAttackAnim.txt");
	m_Animator->LoadAnimation(L"animdata\\PooterRightAnim.txt");
	m_Animator->LoadAnimation(L"animdata\\PooterRightAttackAnim.txt");
	m_Animator->Play(L"PooterRightAnim", true);

	m_Collider = AddComponent<MyCollider>(L"NormalFlyCollider");
	m_Collider->SetScale(Vec2(28.f, 32.f));
	m_Collider->SetOffsetPos(Vec2(0.f, -15.f));

	m_AI = AddComponent<MyStateMachine>(L"NormalFlyAI");
	m_AI->AddState((UINT)NormalMons_STATE::IDLE, new NMIdle);
	m_AI->AddState((UINT)NormalMons_STATE::TRACE, new NMTrace);
	m_AI->AddState((UINT)NormalMons_STATE::ATTACK, new NMAttack);

	m_Info.HP = 3.f;
}

Pooter::Pooter(const Pooter& _Origin)
	: MyMonster(_Origin)
	, m_Atlas(_Origin.m_Atlas)
	, m_MonsterShadow(_Origin.m_MonsterShadow)
	, m_Animator(nullptr)
	, m_Collider(nullptr)
	, m_AI(nullptr)
	, m_AttDelayTime(1.f)
	, m_Acctime(0.f)
{
	m_Animator = GetComponent<MyAnimator>();
	m_AI = GetComponent<MyStateMachine>();
}

Pooter::~Pooter()
{
}

void Pooter::begin()
{
	if (m_IsDead == true)
	{
		return;
	}

	Vec2 vPos = GetPos();
	m_AI->AddDataToBlackboard(L"Initial Position", vPos);
	m_AI->AddDataToBlackboard(L"Detect Range", 700.f);
	m_AI->AddDataToBlackboard(L"Attack Range", 300.f);
	m_AI->AddDataToBlackboard(L"Speed", 5.f);

	m_AI->ChangeState((UINT)NormalMons_STATE::IDLE);
}

void Pooter::tick(float _DT)
{
	if (m_IsDead == true)
	{
		return;
	}

	Super::tick(_DT);
	m_Acctime += DT;
}

void Pooter::render(HDC _dc)
{
	if (m_IsDead == true)
	{
		return;
	}

	Vec2 vRenderPos = GetRenderPos();
	Vec2 vScale = Vec2(0.2f, 0.2f);
	Vec2 vOffset = Vec2(-11.f, 2.f);

	BLENDFUNCTION blend = {};
	blend.BlendOp = AC_SRC_OVER;
	blend.BlendFlags = 0;

	blend.SourceConstantAlpha = 50; // 0 ~ 255
	blend.AlphaFormat = AC_SRC_ALPHA; // 0

	AlphaBlend(_dc
		, int(vRenderPos.x + vOffset.x), int(vRenderPos.y + vOffset.y)
		, int(m_MonsterShadow->GetWidth() * vScale.x)
		, int(m_MonsterShadow->GetHeight() * vScale.y)
		, m_MonsterShadow->GetDC()
		, 0, 0
		, m_MonsterShadow->GetWidth()
		, m_MonsterShadow->GetHeight()
		, blend);


	Super::render(_dc);
}

void Pooter::BeginOverlap(MyCollider* _OwnCol, MyObject* _OtherObj, MyCollider* _OtherCol)
{
	if (dynamic_cast<MyTears*>(_OtherObj))
	{
		m_Info.HP -= 1.f;

		if (m_Info.HP <= 0.f)
		{
			m_IsDead = true;
			MyFlyDeadEffect* pFDE = new MyFlyDeadEffect;
			pFDE->SetPos(GetPos());
			pFDE->SetScale(Vec2(1.f, 1.f));
			MyTaskMgr::GetInst()->AddTask(FTask{ TASK_TYPE::CREATE_OBJECT, (UINT_PTR)LAYER::DOOR, (UINT_PTR)pFDE });
			Destroy();
		}
	}
}