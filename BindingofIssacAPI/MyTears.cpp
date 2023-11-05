#include "pch.h"
#include "MyTears.h"

#include "MyAssetMgr.h"

#include "MyTexture.h"
#include "components.h"

MyTears::MyTears()
	: m_Atlas(nullptr)
	, m_Animator(nullptr)
	, m_Movement(nullptr)
	, m_Speed(0.f)
	, m_Angle(PI /2.f)
{
	m_Atlas = MyAssetMgr::GetInst()->LoadTexture(L"Tears", L"texture\\Effect\\effect_tearpoof.png");

	m_Animator = AddComponent<MyAnimator>(L"TearsAnimator");
	m_Animator->LoadAnimation(L"animdata\\TearsAnim.txt");
	m_Animator->Play(L"TearsAnim", false);

	m_Movement = AddComponent<MyMovement>(L"TearsMovement");
	m_Movement->SetMass(1.f);
	m_Movement->SetInitSpeed(250.f);
	m_Movement->SetMaxSpeed(300.f);
	m_Movement->SetFrictionScale(450.f);
}

MyTears::MyTears(const MyTears& _Origin)
	: MyObject(_Origin)
	, m_Atlas(_Origin.m_Atlas)
	, m_Animator(nullptr)
	, m_Movement(nullptr)
	, m_Speed(_Origin.m_Speed)
	, m_Angle(_Origin.m_Angle)
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

}
