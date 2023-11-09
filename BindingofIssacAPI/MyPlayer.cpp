#include "pch.h"
#include "MyPlayer.h"

#include "MyEngine.h"
#include "MyTimeMgr.h"
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
	, m_Collider(nullptr)
	, m_Acctime(0.6f)
	, m_Duration(0.6f)
	, m_TearsCount(0)
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
	m_AnimatorHead->LoadAnimation(L"animdata\\HTearLeft.txt");
	m_AnimatorHead->LoadAnimation(L"animdata\\HTearRight.txt");
	m_AnimatorHead->LoadAnimation(L"animdata\\HTearUp.txt");
	m_AnimatorHead->LoadAnimation(L"animdata\\HTearDown.txt");

	m_AnimatorBody->Play(L"BIdleDown", true);
	m_AnimatorHead->Play(L"HIdleDown", true);

	// 충돌체 추가
	m_Collider = AddComponent<MyCollider>(L"PlayerCollider");
	m_Collider->SetScale(Vec2(40.f, 64.f));
	m_Collider->SetOffsetPos(Vec2(0.f, -29.f));

	// Movement 컴포넌트 추가
	m_Movement = AddComponent<MyMovement>(L"PlayerMovement");
	m_Movement->SetMass(1.f);
	m_Movement->SetInitSpeed(250.f);
	m_Movement->SetMaxSpeed(300.f);
	m_Movement->SetFrictionScale(450.f);
	m_Movement->SetGravity(0.f);
	m_Movement->UseGravity(false);
}

MyPlayer::MyPlayer(const MyPlayer& _Origin)
	: MyObject(_Origin)
	, m_AnimatorHead(nullptr)
	, m_AnimatorBody(nullptr)
	, m_Movement(nullptr)
	, m_Collider(nullptr)
	, m_Acctime(1.f)
	, m_Duration(1.f)
	, m_TearsCount(0)
{
	m_AnimatorHead = GetComponent<MyAnimator>();
	m_AnimatorBody = GetComponent<MyAnimator>();
	m_Movement = GetComponent<MyMovement>();
	m_Collider = GetComponent<MyCollider>();
}

MyPlayer::~MyPlayer()
{
	
}

void MyPlayer::tick(float _DT)
{
	Super::tick(_DT);

	Vec2 vPos = GetPos();
	m_Acctime += DT;

	// 눈물을 안쏘고 있을 때
	if (KEY_PRESSED(A) && 0 == m_TearsCount)
	{
		m_Movement->AddForce(Vec2(-1000.f, 0.f));
		m_AnimatorBody->Play(L"BWalkLeft", true);
		m_AnimatorHead->Play(L"HIdleLeft", true);
	}
	if (KEY_RELEASED(A) && 0 == m_TearsCount)
	{
		m_AnimatorBody->Play(L"BIdleDown", true);
		m_AnimatorHead->Play(L"HIdleDown", true);
	}

	if (KEY_PRESSED(D) && 0 == m_TearsCount)
	{
		m_Movement->AddForce(Vec2(1000.f, 0.f));
		m_AnimatorBody->Play(L"BWalkRight", true);
		m_AnimatorHead->Play(L"HIdleRight", true);
	}
	if (KEY_RELEASED(D) && 0 == m_TearsCount)
	{
		m_AnimatorBody->Play(L"BIdleDown", true);
		m_AnimatorHead->Play(L"HIdleDown", true);
	}

	if (KEY_PRESSED(W) && 0 == m_TearsCount)
	{
		m_Movement->AddForce(Vec2(0.f, -1000.f));
		m_AnimatorBody->Play(L"BWalkDown", true);
		m_AnimatorHead->Play(L"HIdleUp", true);
	}
	if (KEY_RELEASED(W) && 0 == m_TearsCount)
	{
		m_AnimatorBody->Play(L"BIdleDown", true);
		m_AnimatorHead->Play(L"HIdleDown", true);
	}

	if (KEY_PRESSED(S) && 0 == m_TearsCount)
	{
		m_Movement->AddForce(Vec2(0.f, 1000.f));
		m_AnimatorBody->Play(L"BWalkDown", true);
		m_AnimatorHead->Play(L"HIdleDown", true);
	}
	if (KEY_RELEASED(S) && 0 == m_TearsCount)
	{
		m_AnimatorBody->Play(L"BIdleDown", true);
		m_AnimatorHead->Play(L"HIdleDown", true);
	}

	// 눈물을 쏘면서 움직일 때
	if (KEY_TAP(LEFT))
	{
		++m_TearsCount;
	}
	else if (KEY_PRESSED(LEFT))
	{
		m_AnimatorHead->Play(L"HTearLeft", true);
		
		if (m_Duration <= m_Acctime)
		{
			MyLevel* pCurLevel = MyLevelMgr::GetInst()->GetCurLevel();

			MyTears* pTears = new MyTears;

			Vec2 TearsPos = GetPos();
			TearsPos.x -= 20.f;
			TearsPos.y -= 40.f;

			pTears->SetSpeed(400.f);
			pTears->SetvAngle(Vec2(-1.f, 0.f));
			pTears->SetScale(Vec2(1.3f, 1.3f));
			pTears->SetPos(TearsPos);

			MyTaskMgr::GetInst()->AddTask(FTask{ TASK_TYPE::CREATE_OBJECT, (UINT_PTR)LAYER::TEARS, (UINT_PTR)pTears });

			pTears->fire();

			m_Acctime = 0.f;
		}

		if (KEY_PRESSED(A) && 0 != m_TearsCount)
		{
			m_Movement->AddForce(Vec2(-1000.f, 0.f));
			m_AnimatorBody->Play(L"BWalkLeft", true);
		}
		if (KEY_RELEASED(A) && 0 != m_TearsCount)
		{
			m_AnimatorBody->Play(L"BIdleDown", true);
			m_AnimatorHead->Play(L"HIdleDown", true);
		}

		if (KEY_PRESSED(D) && 0 != m_TearsCount)
		{
			m_Movement->AddForce(Vec2(1000.f, 0.f));
			m_AnimatorBody->Play(L"BWalkRight", true);
		}
		if (KEY_RELEASED(D) && 0 != m_TearsCount)
		{
			m_AnimatorBody->Play(L"BIdleDown", true);
			m_AnimatorHead->Play(L"HIdleDown", true);
		}

		if (KEY_PRESSED(W) && 0 != m_TearsCount)
		{
			m_Movement->AddForce(Vec2(0.f, -1000.f));
			m_AnimatorBody->Play(L"BWalkDown", true);
		}
		if (KEY_RELEASED(W) && 0 != m_TearsCount)
		{
			m_AnimatorBody->Play(L"BIdleDown", true);
			m_AnimatorHead->Play(L"HIdleDown", true);
		}

		if (KEY_PRESSED(S) && 0 != m_TearsCount)
		{
			m_Movement->AddForce(Vec2(0.f, 1000.f));
			m_AnimatorBody->Play(L"BWalkDown", true);
		}
		if (KEY_RELEASED(S) && 0 != m_TearsCount)
		{
			m_AnimatorBody->Play(L"BIdleDown", true);
			m_AnimatorHead->Play(L"HIdleDown", true);
		}
	}
	else if (KEY_RELEASED(LEFT))
	{
		m_AnimatorHead->Play(L"HIdleDown", true);
		--m_TearsCount;
	}

	if (KEY_TAP(RIGHT))
	{
		++m_TearsCount;
	}
	else if (KEY_PRESSED(RIGHT))
	{
		m_AnimatorHead->Play(L"HTearRight", true);

		if (m_Duration <= m_Acctime)
		{
			MyLevel* pCurLevel = MyLevelMgr::GetInst()->GetCurLevel();

			MyTears* pTears = new MyTears;

			Vec2 TearsPos = GetPos();
			TearsPos.x += 12.f;
			TearsPos.y -= 40.f;

			pTears->SetSpeed(400.f);
			pTears->SetvAngle(Vec2(1.f, 0.f));
			pTears->SetScale(Vec2(1.3f, 1.3f));
			pTears->SetPos(TearsPos);

			MyTaskMgr::GetInst()->AddTask(FTask{ TASK_TYPE::CREATE_OBJECT, (UINT_PTR)LAYER::TEARS, (UINT_PTR)pTears });

			pTears->fire();

			m_Acctime = 0.f;
		}

		if (KEY_PRESSED(A) && 0 != m_TearsCount)
		{
			m_Movement->AddForce(Vec2(-1000.f, 0.f));
			m_AnimatorBody->Play(L"BWalkLeft", true);
		}
		if (KEY_RELEASED(A) && 0 != m_TearsCount)
		{
			m_AnimatorBody->Play(L"BIdleDown", true);
			m_AnimatorHead->Play(L"HIdleDown", true);
		}

		if (KEY_PRESSED(D) && 0 != m_TearsCount)
		{
			m_Movement->AddForce(Vec2(1000.f, 0.f));
			m_AnimatorBody->Play(L"BWalkRight", true);
		}
		if (KEY_RELEASED(D) && 0 != m_TearsCount)
		{
			m_AnimatorBody->Play(L"BIdleDown", true);
			m_AnimatorHead->Play(L"HIdleDown", true);
		}

		if (KEY_PRESSED(W) && 0 != m_TearsCount)
		{
			m_Movement->AddForce(Vec2(0.f, -1000.f));
			m_AnimatorBody->Play(L"BWalkDown", true);
		}
		if (KEY_RELEASED(W) && 0 != m_TearsCount)
		{
			m_AnimatorBody->Play(L"BIdleDown", true);
			m_AnimatorHead->Play(L"HIdleDown", true);
		}

		if (KEY_PRESSED(S) && 0 != m_TearsCount)
		{
			m_Movement->AddForce(Vec2(0.f, 1000.f));
			m_AnimatorBody->Play(L"BWalkDown", true);
		}
		if (KEY_RELEASED(S) && 0 != m_TearsCount)
		{
			m_AnimatorBody->Play(L"BIdleDown", true);
			m_AnimatorHead->Play(L"HIdleDown", true);
		}
	}
	else if (KEY_RELEASED(RIGHT))
	{
		m_AnimatorHead->Play(L"HIdleDown", true);
		--m_TearsCount;
	}

	if (KEY_TAP(UP))
	{
		++m_TearsCount;
	}
	else if (KEY_PRESSED(UP))
	{
		m_AnimatorHead->Play(L"HTearUp", true);

		if (m_Duration <= m_Acctime)
		{
			MyLevel* pCurLevel = MyLevelMgr::GetInst()->GetCurLevel();

			MyTears* pTears = new MyTears;

			Vec2 TearsPos = GetPos();
			TearsPos.x -= 8.f;
			TearsPos.y -= 60.f;

			pTears->SetSpeed(400.f);
			pTears->SetvAngle(Vec2(0.f, -1.f));
			pTears->SetScale(Vec2(1.3f, 1.3f));
			pTears->SetPos(TearsPos);

			MyTaskMgr::GetInst()->AddTask(FTask{ TASK_TYPE::CREATE_OBJECT, (UINT_PTR)LAYER::TEARS, (UINT_PTR)pTears });

			pTears->fire();

			m_Acctime = 0.f;
		}

		if (KEY_PRESSED(A) && 0 != m_TearsCount)
		{
			m_Movement->AddForce(Vec2(-1000.f, 0.f));
			m_AnimatorBody->Play(L"BWalkLeft", true);
		}
		if (KEY_RELEASED(A) && 0 != m_TearsCount)
		{
			m_AnimatorBody->Play(L"BIdleDown", true);
			m_AnimatorHead->Play(L"HIdleDown", true);
		}

		if (KEY_PRESSED(D) && 0 != m_TearsCount)
		{
			m_Movement->AddForce(Vec2(1000.f, 0.f));
			m_AnimatorBody->Play(L"BWalkRight", true);
		}
		if (KEY_RELEASED(D) && 0 != m_TearsCount)
		{
			m_AnimatorBody->Play(L"BIdleDown", true);
			m_AnimatorHead->Play(L"HIdleDown", true);
		}

		if (KEY_PRESSED(W) && 0 != m_TearsCount)
		{
			m_Movement->AddForce(Vec2(0.f, -1000.f));
			m_AnimatorBody->Play(L"BWalkDown", true);
		}
		if (KEY_RELEASED(W) && 0 != m_TearsCount)
		{
			m_AnimatorBody->Play(L"BIdleDown", true);
			m_AnimatorHead->Play(L"HIdleDown", true);
		}

		if (KEY_PRESSED(S) && 0 != m_TearsCount)
		{
			m_Movement->AddForce(Vec2(0.f, 1000.f));
			m_AnimatorBody->Play(L"BWalkDown", true);
		}
		if (KEY_RELEASED(S) && 0 != m_TearsCount)
		{
			m_AnimatorBody->Play(L"BIdleDown", true);
			m_AnimatorHead->Play(L"HIdleDown", true);
		}
	}
	else if (KEY_RELEASED(UP))
	{
		m_AnimatorHead->Play(L"HIdleDown", true);
		--m_TearsCount;
	}

	if (KEY_TAP(DOWN))
	{
		++m_TearsCount;
	}
	else if (KEY_PRESSED(DOWN))
	{
		m_AnimatorHead->Play(L"HTearDown", true);

		if (m_Duration <= m_Acctime)
		{
			MyLevel* pCurLevel = MyLevelMgr::GetInst()->GetCurLevel();

			MyTears* pTears = new MyTears;

			Vec2 TearsPos = GetPos();
			TearsPos.x -= 8.f;
			TearsPos.y -= 35.f;

			pTears->SetSpeed(400.f);
			pTears->SetvAngle(Vec2(0.f, 1.f));
			pTears->SetScale(Vec2(1.3f, 1.3f));
			pTears->SetPos(TearsPos);

			MyTaskMgr::GetInst()->AddTask(FTask{ TASK_TYPE::CREATE_OBJECT, (UINT_PTR)LAYER::TEARS, (UINT_PTR)pTears });

			pTears->fire();

			m_Acctime = 0.f;
		}

		if (KEY_PRESSED(A) && 0 != m_TearsCount)
		{
			m_Movement->AddForce(Vec2(-1000.f, 0.f));
			m_AnimatorBody->Play(L"BWalkLeft", true);
		}
		if (KEY_RELEASED(A) && 0 != m_TearsCount)
		{
			m_AnimatorBody->Play(L"BIdleDown", true);
			m_AnimatorHead->Play(L"HIdleDown", true);
		}

		if (KEY_PRESSED(D) && 0 != m_TearsCount)
		{
			m_Movement->AddForce(Vec2(1000.f, 0.f));
			m_AnimatorBody->Play(L"BWalkRight", true);
		}
		if (KEY_RELEASED(D) && 0 != m_TearsCount)
		{
			m_AnimatorBody->Play(L"BIdleDown", true);
			m_AnimatorHead->Play(L"HIdleDown", true);
		}

		if (KEY_PRESSED(W) && 0 != m_TearsCount)
		{
			m_Movement->AddForce(Vec2(0.f, -1000.f));
			m_AnimatorBody->Play(L"BWalkDown", true);
		}
		if (KEY_RELEASED(W) && 0 != m_TearsCount)
		{
			m_AnimatorBody->Play(L"BIdleDown", true);
			m_AnimatorHead->Play(L"HIdleDown", true);
		}

		if (KEY_PRESSED(S) && 0 != m_TearsCount)
		{
			m_Movement->AddForce(Vec2(0.f, 1000.f));
			m_AnimatorBody->Play(L"BWalkDown", true);
		}
		if (KEY_RELEASED(S) && 0 != m_TearsCount)
		{
			m_AnimatorBody->Play(L"BIdleDown", true);
			m_AnimatorHead->Play(L"HIdleDown", true);
		}
	}
	else if (KEY_RELEASED(DOWN))
	{
		m_AnimatorHead->Play(L"HIdleDown", true);
		--m_TearsCount;
	}

	SetPos(vPos);
}
