#include "pch.h"
#include "MyPlayer.h"

#include "MyEngine.h"
#include "MyAssetMgr.h"
#include "MyTaskMgr.h"
#include "MyLevelMgr.h"
#include "MyKeyMgr.h"
#include "MyLevel.h"
#include "MyTears.h"
#include "MyTexture.h"

#include "components.h"

MyPlayer::MyPlayer()
	: m_AnimatorHead(nullptr)
	, m_AnimatorBody(nullptr)
	, m_Movement(nullptr)
	, m_IsFire(false)
	//, m_Collider(nullptr)
{
	SetName(L"Player");

	MyTexture* pAtlas = MyAssetMgr::GetInst()->LoadTexture(L"PlayerAtlas", L"texture\\Character\\Issac.png");

	m_AnimatorBody = AddComponent<MyAnimator>(L"BodyAnimator");
	m_AnimatorHead = AddComponent<MyAnimator>(L"HeadAnimator");

	// 몸 애니메이션 로드
	m_AnimatorBody->LoadAnimation(L"animdata\\BIdleDown.txt");
	m_AnimatorBody->LoadAnimation(L"animdata\\BWalkLeft.txt");
	m_AnimatorBody->LoadAnimation(L"animdata\\BWalkRight.txt");
	m_AnimatorBody->LoadAnimation(L"animdata\\BWalkDown.txt");

	// 머리 애니메이션 로드
	m_AnimatorHead->LoadAnimation(L"animdata\\HIdleDown.txt");
	m_AnimatorHead->LoadAnimation(L"animdata\\HIdleUp.txt");
	m_AnimatorHead->LoadAnimation(L"animdata\\HIdleRight.txt");
	m_AnimatorHead->LoadAnimation(L"animdata\\HIdleLeft.txt");

	m_AnimatorBody->Play(L"BIdleDown", true);
	m_AnimatorHead->Play(L"HIdleDown", true);

	// Movement 컴포넌트 추가
	m_Movement = AddComponent<MyMovement>(L"PlayerMovement");
	m_Movement->SetMass(1.f);
	m_Movement->SetInitSpeed(250.f);
	m_Movement->SetMaxSpeed(300.f);
	m_Movement->SetFrictionScale(450.f);
}

MyPlayer::MyPlayer(const MyPlayer& _Origin)
	: MyObject(_Origin)
	, m_AnimatorHead(nullptr)
	, m_AnimatorBody(nullptr)
	, m_Movement(nullptr)
	, m_IsFire(false)
	//, m_Collider(nullptr)
{
	m_AnimatorHead = GetComponent<MyAnimator>();
	m_AnimatorBody = GetComponent<MyAnimator>();
	m_Movement = GetComponent<MyMovement>();
	//m_Collider = GetComponent<MyCollider>();
}

MyPlayer::~MyPlayer()
{
	
}

void MyPlayer::tick(float _DT)
{
	Super::tick(_DT);

	Vec2 vPos = GetPos();

	if (KEY_PRESSED(A))
	{
		m_Movement->AddForce(Vec2(-1000.f, 0.f));
		m_AnimatorBody->Play(L"BWalkLeft", true);
		m_AnimatorHead->Play(L"HIdleLeft", true);
	}

	if (KEY_RELEASED(A))
	{
		m_AnimatorBody->Play(L"BIdleDown", true);
		m_AnimatorHead->Play(L"HIdleDown", true);
	}

	if (KEY_PRESSED(D))
	{
		m_Movement->AddForce(Vec2(1000.f, 0.f));
		m_AnimatorBody->Play(L"BWalkRight", true);
		m_AnimatorHead->Play(L"HIdleRight", true);
	}
	if (KEY_RELEASED(D))
	{
		m_AnimatorBody->Play(L"BIdleDown", true);
		m_AnimatorHead->Play(L"HIdleDown", true);
	}

	if (KEY_PRESSED(W))
	{
		m_Movement->AddForce(Vec2(0.f, -1000.f));
		m_AnimatorBody->Play(L"BWalkDown", true);
		m_AnimatorHead->Play(L"HIdleUp", true);
	}
	if (KEY_RELEASED(W))
	{
		m_AnimatorBody->Play(L"BIdleDown", true);
		m_AnimatorHead->Play(L"HIdleDown", true);
	}

	if (KEY_PRESSED(S))
	{
		m_Movement->AddForce(Vec2(0.f, 1000.f));
		m_AnimatorBody->Play(L"BWalkDown", true);
		m_AnimatorHead->Play(L"HIdleDown", true);
	}
	if (KEY_RELEASED(S))
	{
		m_AnimatorBody->Play(L"BIdleDown", true);
		m_AnimatorHead->Play(L"HIdleDown", true);
	}

	// 눈물 발사
	if (KEY_TAP(LEFT))
	{
		MyLevel* pCurLevel = MyLevelMgr::GetInst()->GetCurLevel();

		MyTears* pTears = new MyTears;

		Vec2 TearsPos = GetPos();

		pTears->SetSpeed(400.f);
		pTears->SetvAngle(Vec2(-1.f, 0.f));
		pTears->SetScale(Vec2(1.3f, 1.3f));
		pTears->SetPos(TearsPos);

		MyTaskMgr::GetInst()->AddTask(FTask{ TASK_TYPE::CREATE_OBJECT, (UINT_PTR)LAYER::TEARS, (UINT_PTR)pTears });

		m_AnimatorHead->Play(L"HIdleLeft", true);
		pTears->fire();
	}
	if (KEY_RELEASED(LEFT))
	{
		m_AnimatorHead->Play(L"HIdleDown", true);
	}

	if (KEY_TAP(RIGHT))
	{
		MyLevel* pCurLevel = MyLevelMgr::GetInst()->GetCurLevel();

		MyTears* pTears = new MyTears;

		Vec2 TearsPos = GetPos();

		pTears->SetSpeed(400.f);
		pTears->SetvAngle(Vec2(1.f, 0.f));
		pTears->SetScale(Vec2(1.3f, 1.3f));
		pTears->SetPos(TearsPos);

		MyTaskMgr::GetInst()->AddTask(FTask{ TASK_TYPE::CREATE_OBJECT, (UINT_PTR)LAYER::TEARS, (UINT_PTR)pTears });

		pTears->fire();
	}

	if (KEY_TAP(UP))
	{
		MyLevel* pCurLevel = MyLevelMgr::GetInst()->GetCurLevel();

		MyTears* pTears = new MyTears;

		Vec2 TearsPos = GetPos();

		pTears->SetSpeed(400.f);
		pTears->SetvAngle(Vec2(0.f, -1.f));
		pTears->SetScale(Vec2(1.3f, 1.3f));
		pTears->SetPos(TearsPos);

		MyTaskMgr::GetInst()->AddTask(FTask{ TASK_TYPE::CREATE_OBJECT, (UINT_PTR)LAYER::TEARS, (UINT_PTR)pTears });

		pTears->fire();
	}

	if (KEY_TAP(DOWN))
	{
		MyLevel* pCurLevel = MyLevelMgr::GetInst()->GetCurLevel();

		MyTears* pTears = new MyTears;

		Vec2 TearsPos = GetPos();

		pTears->SetSpeed(400.f);
		pTears->SetvAngle(Vec2(0.f, 1.f));
		pTears->SetScale(Vec2(1.3f, 1.3f));
		pTears->SetPos(TearsPos);

		MyTaskMgr::GetInst()->AddTask(FTask{ TASK_TYPE::CREATE_OBJECT, (UINT_PTR)LAYER::TEARS, (UINT_PTR)pTears });

		pTears->fire();
	}


	SetPos(vPos);
}
