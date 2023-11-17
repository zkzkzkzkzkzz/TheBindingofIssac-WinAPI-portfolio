#include "pch.h"
#include "MyTears.h"
#include "MyAssetMgr.h"
#include "MyTimeMgr.h"

#include "MyEffect.h"
#include "MyShadow.h"
#include "MyTexture.h"
#include "components.h"


MyTears::MyTears()
	: m_Atlas(nullptr)
	, m_Animator(nullptr)
	, m_Movement(nullptr)
	, m_Collider(nullptr)
	, m_Shadow(nullptr)
	, m_Effect(nullptr)
	, m_Speed(0.f)
	, m_Angle(PI /2.f)
	, m_Duration(0.4f)
	, m_Acctime(0.f)
	, m_IsDestroy(false)
	, m_initPos{}
{
	SetName(L"NormalTears");
	m_Atlas = MyAssetMgr::GetInst()->LoadTexture(L"Tears", L"texture\\Effect\\effect_tearpoof.png");

	m_Animator = AddComponent<MyAnimator>(L"TearsAnimator");
	m_Animator->LoadAnimation(L"animdata\\TearsAnim.txt");
	m_Animator->Play(L"TearsAnim", false);

	m_Collider = AddComponent<MyCollider>(L"TearsCollider");
	m_Collider->SetScale(Vec2(19.f, 19.f));
	m_Collider->SetOffsetPos(Vec2(0.f, -8.f));

	m_Movement = AddComponent<MyMovement>(L"TearsMovement");
	m_Movement->SetMass(1.f);
	m_Movement->SetInitSpeed(250.f);
	m_Movement->SetMaxSpeed(250.f);
	m_Movement->SetFrictionScale(0.f);
	m_Movement->SetGravity(1000.f);
	m_Movement->UseGravity(false);

	m_Shadow = new MyShadow(this);
	m_Shadow->SetName(L"TearsShadow");
	MyTaskMgr::GetInst()->AddTask(FTask{ TASK_TYPE::CREATE_OBJECT, (UINT_PTR)LAYER::SHADOW, (UINT_PTR)m_Shadow });

}

MyTears::MyTears(const MyTears& _Origin)
	: m_Atlas(_Origin.m_Atlas)
	, m_Animator(nullptr)
	, m_Movement(nullptr)
	, m_Collider(nullptr)
	, m_Shadow(nullptr)
	, m_Effect(nullptr)
	, m_Speed(0.f)
	, m_Angle(PI / 2.f)
	, m_Duration(1.f)
	, m_Acctime(0.f)
	, m_IsDestroy(false)
{
	m_Animator = GetComponent<MyAnimator>();
	m_Movement = GetComponent<MyMovement>();
	m_Collider = GetComponent<MyCollider>();

	m_Shadow = new MyShadow(this);
	m_Shadow->SetName(L"TearsShadow");
	MyTaskMgr::GetInst()->AddTask(FTask{ TASK_TYPE::CREATE_OBJECT, (UINT_PTR)LAYER::SHADOW, (UINT_PTR)m_Shadow });
}

MyTears::~MyTears()
{

}


void MyTears::begin()
{
	m_initPos = GetPos();

}

void MyTears::tick(float _DT)
{
	Super::tick(_DT);

	if (!m_IsDestroy)
	{
		fire();
	}
}

void MyTears::fire()
{
	m_Acctime += DT;

	Vec2 vPos = GetPos();
	
	m_Shadow->SetPos(Vec2(vPos.x, m_initPos.y + 55.f));
	m_Shadow->SetScale(Vec2(0.2f, 0.2f));
	m_Shadow->SetOffsetPos(Vec2(-12.f, -10.f));

	vPos.x += m_vAngle.x * GetSpeed() * DT;
	vPos.y += m_vAngle.y * GetSpeed() * DT;

	SetPos(vPos);
	if (0 == m_vAngle.x)
	{
		m_Shadow->SetPos(Vec2(m_initPos.x, vPos.y + 20.f));
	}
	else if (0 == m_vAngle.y)
	{
		m_Shadow->SetPos(Vec2(vPos.x, m_initPos.y + 30.f));
	}

	if (m_Duration / 2.f <= m_Acctime)
	{
		m_Movement->UseGravity(true);
	}
}

void MyTears::TearsDestroy()
{
	Vec2 vPos = GetPos();

	m_Effect = new MyEffect;
	m_Effect->SetName(L"TearsDestroyAnimation");
	m_Effect->SetPos(vPos);
	m_Effect->SetScale(Vec2(1.f, 1.f));
	MyTaskMgr::GetInst()->AddTask(FTask{ TASK_TYPE::CREATE_OBJECT, (UINT_PTR)LAYER::EFFECT, (UINT_PTR)m_Effect });

	m_Shadow->Destroy();
	Destroy();
}


void MyTears::BeginOverlap(MyCollider* _OwnCol, MyObject* _OtherObj, MyCollider* _OtherCol)
{
	if (_OtherObj->GetName() != L"PlayerShadow")
	{
		m_IsDestroy = true;
		m_Movement->SetVelocity(Vec2(0.f, 0.f));
		m_Movement->UseGravity(false);
		TearsDestroy();
	}
}