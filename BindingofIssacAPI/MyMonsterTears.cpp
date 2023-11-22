#include "pch.h"
#include "MyMonsterTears.h"
#include "MyAssetMgr.h"
#include "MyTimeMgr.h"
#include "MyLevelMgr.h"
#include "MyLevel.h"
#include "MyPlayer.h"
#include "MyMonsterEffect.h"
#include "MyShadow.h"
#include "MyTexture.h"
#include "MySound.h"
#include "components.h"

MyMonsterTears::MyMonsterTears()
	: m_Atlas(nullptr)
	, m_Animator(nullptr)
	, m_Movement(nullptr)
	, m_Collider(nullptr)
	, m_Shadow(nullptr)
	, m_Speed(0.f)
	, m_Angle(PI / 2.f)
	, m_Duration(0.8f)
	, m_Acctime(0.f)
	, m_IsDestroy(false)
	, m_pTarget(nullptr)
	, m_TargetPos()
	, m_MTSound(nullptr)
{
	SetName(L"MonsterTears");
	m_Atlas = MyAssetMgr::GetInst()->LoadTexture(L"MonsterTearsTex", L"texture\\Effect\\effect_bloodtear.png");

	m_Animator = AddComponent<MyAnimator>(L"MonsterTearsAnimator");
	m_Animator->LoadAnimation(L"animdata\\MonsterTearsAnim.txt");
	m_Animator->Play(L"MonsterTearsAnim", false);

	m_Collider = AddComponent<MyCollider>(L"MonsterTearsCollider");
	m_Collider->SetScale(Vec2(19.f, 19.f));
	m_Collider->SetOffsetPos(Vec2(0.f, -8.f));

	m_Movement = AddComponent<MyMovement>(L"MonsterTearsMovement");
	m_Movement->SetMass(1.f);
	m_Movement->SetInitSpeed(250.f);
	m_Movement->SetMaxSpeed(250.f);
	m_Movement->SetFrictionScale(0.f);
	m_Movement->SetGravity(500.f);
	m_Movement->UseGravity(false);

	m_Shadow = new MyShadow(this);
	m_Shadow->SetName(L"MonsterTearsShadow");
	MyTaskMgr::GetInst()->AddTask(FTask{ TASK_TYPE::CREATE_OBJECT, (UINT_PTR)LAYER::SHADOW, (UINT_PTR)m_Shadow });

	m_MTSound = MyAssetMgr::GetInst()->LoadSound(L"MTSound", L"sound\\blood_fire.wav");
	m_MTSound->SetVolume(100.f);
	m_MTSound->SetPosition(0.f);
	m_MTSound->Play();
}

MyMonsterTears::MyMonsterTears(const MyMonsterTears& _Origin)
	: m_Atlas(_Origin.m_Atlas)
	, m_Animator(nullptr)
	, m_Movement(nullptr)
	, m_Collider(nullptr)
	, m_Shadow(nullptr)
	, m_Effect(nullptr)
	, m_Speed(0.f)
	, m_Angle(PI / 2.f)
	, m_Duration(0.8f)
	, m_Acctime(0.f)
	, m_IsDestroy(false)
	, m_pTarget(nullptr)
	, m_TargetPos()
	, m_MTSound(_Origin.m_MTSound)
{
	m_Animator = GetComponent<MyAnimator>();
	m_Movement = GetComponent<MyMovement>();
	m_Collider = GetComponent<MyCollider>();

	m_Shadow = new MyShadow(this);
	m_Shadow->SetName(L"MonsterTearsShadow");
	MyTaskMgr::GetInst()->AddTask(FTask{ TASK_TYPE::CREATE_OBJECT, (UINT_PTR)LAYER::SHADOW, (UINT_PTR)m_Shadow });
}

MyMonsterTears::~MyMonsterTears()
{
}

void MyMonsterTears::begin()
{
	m_pTarget = dynamic_cast<MyPlayer*>(MyLevelMgr::GetInst()->GetCurLevel()->FindObjectByName(L"Player"));
	m_TargetPos = m_pTarget->GetPos();
}

void MyMonsterTears::tick(float _DT)
{
	Super::tick(_DT);

	if (!m_IsDestroy)
	{
		fire();
	}

	if (m_Duration * 0.8f <= m_Acctime)
	{
		TearsDestroy();
	}
}

void MyMonsterTears::fire()
{
	m_Acctime += DT;

	Vec2 vPos = GetPos();
	
	Vec2 vDir = m_TargetPos - vPos;
	vDir.Normalize();

	vPos.x += vDir.x * GetSpeed() * DT;
	vPos.y += vDir.y * GetSpeed() * DT;

	SetPos(vPos);

	m_Shadow->SetPos(Vec2(vPos.x, vPos.y + 30.f));
	m_Shadow->SetScale(Vec2(0.2f, 0.2f));
	m_Shadow->SetOffsetPos(Vec2(-12.f, -10.f));

	/*if (m_Duration / 4.f <= m_Acctime)
	{
		m_Movement->UseGravity(true);
	}*/
}

void MyMonsterTears::TearsDestroy()
{
	Vec2 vPos = GetPos();

	m_Effect = new MyMonsterEffect;
	m_Effect->SetName(L"MonsterTearsDestroyAnimation");
	m_Effect->SetPos(vPos);
	m_Effect->SetScale(Vec2(1.f, 1.f));
	MyTaskMgr::GetInst()->AddTask(FTask{ TASK_TYPE::CREATE_OBJECT, (UINT_PTR)LAYER::EFFECT, (UINT_PTR)m_Effect });

	m_Shadow->Destroy();
	Destroy();
}

void MyMonsterTears::BeginOverlap(MyCollider* _OwnCol, MyObject* _OtherObj, MyCollider* _OtherCol)
{
	if (_OtherObj->GetName() == L"Player")
	{
		m_IsDestroy = true;
		m_Movement->SetVelocity(Vec2(0.f, 0.f));
		m_Movement->UseGravity(false);
		TearsDestroy();
	}
}

