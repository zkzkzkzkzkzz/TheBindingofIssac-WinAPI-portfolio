#include "pch.h"
#include "Host.h"

#include "MyAssetMgr.h"
#include "MyLevelMgr.h"
#include "MyLevel.h"
#include "MyTexture.h"
#include "MyPlayer.h"
#include "MyTears.h"
#include "MyMonsterTears.h"
#include "MySpawnEffect.h"
#include "MyFKDeadEffect.h"
#include "components.h"

Host::Host()
	: m_MonsterShadow(nullptr)
	, m_Animator(nullptr)
	, m_Collider(nullptr)
	, m_Info()
	, m_HostState(HOST_STATE::IDLE)
	, m_AccTime(0.f)
{
	m_MonsterShadow = MyAssetMgr::GetInst()->LoadTexture(L"Shadow", L"texture\\Effect\\shadow.png");

	m_Animator = AddComponent<MyAnimator>(L"HostAnimator");
	m_Animator->LoadAnimation(L"animdata\\HostIdleAnim.txt");
	m_Animator->LoadAnimation(L"animdata\\HostAttAnim.txt");
	m_Animator->LoadAnimation(L"animdata\\HostAttToIdleAnim.txt");
	m_Animator->Play(L"HostIdleAnim", false);

	m_Collider = AddComponent<MyCollider>(L"HostCollider");
	m_Collider->SetScale(Vec2(50.f, 44.f));
	m_Collider->SetOffsetPos(Vec2(0.f, -20.f));

	m_Info.HP = 3.f;
}

Host::~Host()
{

}


void Host::begin()
{
	m_Target = dynamic_cast<MyPlayer*>(MyLevelMgr::GetInst()->GetCurLevel()->FindObjectByName(L"Player"));
}

void Host::tick(float _DT)
{
	if (m_IsDead == true)
	{
		return;
	}

	Super::tick(_DT);

	Vec2 HostPos = GetPos();
	Vec2 PlayerPos = m_Target->GetPos();

	float DetectionRange = HostPos.Distance(PlayerPos);

	if (DetectionRange < 200.f)
	{
		m_AccTime += _DT;
	
		IdleToAtt();
	}
	else
	{
		AttToIdle();
	}
}

void Host::render(HDC _dc)
{
	if (m_IsDead == true)
	{
		return;
	}

	Vec2 vRenderPos = GetRenderPos();
	Vec2 vScale = Vec2(0.4f, 0.4f);
	Vec2 vOffset = Vec2(-22.f, -10.f);

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

void Host::BeginOverlap(MyCollider* _OwnCol, MyObject* _OtherObj, MyCollider* _OtherCol)
{
	if (dynamic_cast<MyTears*>(_OtherObj) && m_HostState == HOST_STATE::ATT)
	{
		m_Info.HP -= 1.f;

		if (m_Info.HP <= 0.f)
		{
			m_IsDead = true;
			MyFKDeadEffect* pFDE = new MyFKDeadEffect;
			pFDE->SetPos(GetPos());
			pFDE->SetScale(Vec2(1.5f, 1.5f));
			pFDE->SetOffsetPos(Vec2(-15.f, -20.f));
			MyTaskMgr::GetInst()->AddTask(FTask{ TASK_TYPE::CREATE_OBJECT, (UINT_PTR)LAYER::EFFECT, (UINT_PTR)pFDE });
			Destroy();
		}
	}
}


void Host::IdleToAtt()
{
	m_HostState = HOST_STATE::ATT;

	m_Animator->Play(L"HostAttAnim", false);
	m_Animator->FindAnim(L"HostAttToIdleAnim")->Reset();

	if (m_AccTime >= 2.f)
	{
		MyMonsterTears* pTears = new MyMonsterTears;

		Vec2 TearsPos = GetPos();
		TearsPos.x -= 4.f;
		TearsPos.y -= 10.f;

		pTears->SetSpeed(250.f);
		pTears->SetScale(Vec2(1.4f, 1.4f));
		pTears->SetOffsetPos(Vec2(-14.f, -15.f));
		pTears->SetPos(TearsPos);

		MyTaskMgr::GetInst()->AddTask(FTask{ TASK_TYPE::CREATE_OBJECT, (UINT_PTR)LAYER::MONSTEARS, (UINT_PTR)pTears });

		pTears->fire();

		m_AccTime = 0.f;
	}
}

void Host::AttToIdle()
{
	m_HostState = HOST_STATE::IDLE;

	m_Animator->Play(L"HostAttToIdleAnim", false);
	m_Animator->FindAnim(L"HostAttAnim")->Reset();
}
