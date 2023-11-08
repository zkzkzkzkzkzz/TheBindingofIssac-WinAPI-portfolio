#include "pch.h"
#include "MyTears.h"

#include "MyAssetMgr.h"
#include "MyTimeMgr.h"

#include "MyTexture.h"
#include "components.h"

MyTears::MyTears()
	: m_Atlas(nullptr)
	, m_Animator(nullptr)
	, m_Movement(nullptr)
	, m_Speed(0.f)
	, m_Angle(PI /2.f)
	, m_Duration(0.4f)
	, m_Acctime(0.f)
	, m_IsDestroy(false)
{
	m_Atlas = MyAssetMgr::GetInst()->LoadTexture(L"Tears", L"texture\\Effect\\effect_tearpoof.png");

	m_Animator = AddComponent<MyAnimator>(L"TearsAnimator");
	m_Animator->LoadAnimation(L"animdata\\TearsAnim.txt");
	m_Animator->LoadAnimation(L"animdata\\TearsDestroy.txt");
	m_Animator->Play(L"TearsAnim", false);

	m_Movement = AddComponent<MyMovement>(L"TearsMovement");
	m_Movement->SetMass(1.f);
	m_Movement->SetInitSpeed(250.f);
	m_Movement->SetMaxSpeed(250.f);
	m_Movement->SetFrictionScale(0.f);
	m_Movement->SetGravity(1000.f);
	m_Movement->UseGravity(false);
}

MyTears::MyTears(const MyTears& _Origin)
	: MyObject(_Origin)
	, m_Atlas(_Origin.m_Atlas)
	, m_Animator(nullptr)
	, m_Movement(nullptr)
	, m_Speed(0.f)
	, m_Angle(PI / 2.f)
	, m_Duration(0.5f)
	, m_Acctime(0.f)
	, m_IsDestroy(false)
{
	m_Animator = GetComponent<MyAnimator>();
	m_Movement = GetComponent<MyMovement>();
}

MyTears::~MyTears()
{

}

void MyTears::tick(float _DT)
{
	Super::tick(_DT);

	fire();

	if (m_Duration <= m_Acctime)
	{
		m_Movement->UseGravity(true);
		TearsDestroy();
	}

	if (m_IsDestroy && m_Acctime >= 0.8f)
	{
		Destroy();
	}

}

void MyTears::fire()
{
	m_Acctime += DT;

	Vec2 vPos = GetPos();

	vPos.x += m_vAngle.x * GetSpeed() * DT;
	vPos.y += m_vAngle.y * GetSpeed() * DT;

	SetPos(vPos);
}

void MyTears::TearsDestroy()
{
	m_Animator->Play(L"TearsDestroy", false);

	m_IsDestroy = true;
}
