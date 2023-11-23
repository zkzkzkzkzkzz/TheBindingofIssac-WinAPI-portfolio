#include "pch.h"
#include "MyPlayer.h"

#include "MyEngine.h"
#include "MyTimeMgr.h"
#include "MyAssetMgr.h"
#include "MyTaskMgr.h"
#include "MyLevelMgr.h"
#include "MyKeyMgr.h"
#include "MyLevel.h"
#include "MyLayer.h"
#include "MyTears.h"
#include "MyShadow.h"
#include "MyTexture.h"
#include "MySound.h"
#include "components.h"

MyPlayer::MyPlayer()
	: m_AnimatorHead(nullptr)
	, m_AnimatorBody(nullptr)
	, m_Movement(nullptr)
	, m_Collider(nullptr)
	, m_Shadow(nullptr)
	, m_Acctime(0.f)
	, m_Duration(0.5f)
	, m_TearsCount(0)
	, m_IsDamaged(0)
	, m_DamagedMaxTime(100000.f)
	, m_DamagedAccTime(0.f)
	, m_FireSound(nullptr)
	, m_DamageSound(nullptr)
	, m_IsRender(true)
{
	SetName(L"Player");

	//MyTexture* pAtlas = MyAssetMgr::GetInst()->LoadTexture(L"PlayerAtlas", L"texture\\Character\\Issac.png");

	m_AnimatorBody = AddComponent<MyAnimator>(L"BodyAnimator");
	m_AnimatorHead = AddComponent<MyAnimator>(L"HeadAnimator");

	// 머리 애니메이션 로드
	m_AnimatorHead->LoadAnimation(L"animdata\\HIdleDown.txt");
	m_AnimatorHead->LoadAnimation(L"animdata\\HIdleUp.txt");
	m_AnimatorHead->LoadAnimation(L"animdata\\HIdleRight.txt");
	m_AnimatorHead->LoadAnimation(L"animdata\\HIdleLeft.txt");
	m_AnimatorHead->LoadAnimation(L"animdata\\HTearLeft.txt");
	m_AnimatorHead->LoadAnimation(L"animdata\\HTearRight.txt");
	m_AnimatorHead->LoadAnimation(L"animdata\\HTearUp.txt");
	m_AnimatorHead->LoadAnimation(L"animdata\\HTearDown.txt");
	m_AnimatorHead->LoadAnimation(L"animdata\\IssacDamagedAnim.txt");

	// 몸 애니메이션 로드
	m_AnimatorBody->LoadAnimation(L"animdata\\BIdleDown.txt");
	m_AnimatorBody->LoadAnimation(L"animdata\\BWalkLeft.txt");
	m_AnimatorBody->LoadAnimation(L"animdata\\BWalkRight.txt");
	m_AnimatorBody->LoadAnimation(L"animdata\\BWalkDown.txt");
	m_AnimatorBody->LoadAnimation(L"animdata\\IssacDamagedAnim.txt");

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

	m_FireSound = MyAssetMgr::GetInst()->LoadSound(L"FireSound", L"sound\\tear_fire_5.wav");
	m_DamageSound = MyAssetMgr::GetInst()->LoadSound(L"DamagedSound", L"sound\\hurt_grunt.wav");
}

MyPlayer::MyPlayer(const MyPlayer& _Origin)
	: MyObject(_Origin)
	, m_AnimatorHead(nullptr)
	, m_AnimatorBody(nullptr)
	, m_Movement(nullptr)
	, m_Collider(nullptr)
	, m_Shadow(nullptr)
	, m_Acctime(1.f)
	, m_Duration(1.f)
	, m_TearsCount(0)
	, m_IsDamaged(0)
	, m_DamagedMaxTime(100000.f)
	, m_DamagedAccTime(0.f)
	, m_FireSound(_Origin.m_FireSound)
	, m_DamageSound(_Origin.m_DamageSound)
{
	m_AnimatorHead = GetComponent<MyAnimator>();
	m_AnimatorBody = GetComponent<MyAnimator>();
	m_Movement = GetComponent<MyMovement>();
	m_Collider = GetComponent<MyCollider>();
}

MyPlayer::~MyPlayer()
{
	
}


void MyPlayer::begin()
{
	Vec2 vPos = GetPos();

	m_Shadow = new MyShadow;

	m_Shadow->SetName(L"PlayerShadow");
	m_Shadow->SetPos(vPos);
	m_Shadow->SetScale(Vec2(0.32f, 0.32f));
	m_Shadow->SetOffsetPos(Vec2(-18.5f, -6.f));

	MyTaskMgr::GetInst()->AddTask(FTask{ TASK_TYPE::CREATE_OBJECT, (UINT_PTR)LAYER::SHADOW, (UINT_PTR)m_Shadow });
}

void MyPlayer::tick(float _DT)
{
	Super::tick(_DT);

	Vec2 vPos = GetPos();

	m_Acctime += _DT;

	if (m_IsDamaged != 0)
	{
		m_DamagedAccTime += _DT;
		
		if (m_DamagedAccTime >= 0.f && m_DamagedAccTime < 0.1f)
		{
			m_IsRender = true;
		}
		else if (m_DamagedAccTime >= 0.1f && m_DamagedAccTime < 0.2f)
		{
			m_IsRender = false;
		}
		else if (m_DamagedAccTime >= 0.3f && m_DamagedAccTime < 0.4f)
		{
			m_IsRender = true;
		}
		else if (m_DamagedAccTime >= 0.4f && m_DamagedAccTime < 0.5f)
		{
			m_IsRender = false;
		}
		if (m_DamagedAccTime >= m_DamagedMaxTime)
		{
			m_IsRender = true;
			m_IsDamaged = 0;
			m_DamagedMaxTime = 100000.f;
			m_DamagedAccTime = 0.f;
		}
	}
	


	// 눈물을 안쏘고 있을 때
	if (KEY_PRESSED(A) && 0 == m_TearsCount)
	{
		m_Movement->AddForce(Vec2(-1000.f, 0.f));

		if (m_IsDamaged == 0)
		{
			m_AnimatorBody->Play(L"BWalkLeft", true);
			m_AnimatorHead->Play(L"HIdleLeft", true);

		}
	}
	if (KEY_RELEASED(A) && 0 == m_TearsCount)
	{
		if (m_IsDamaged == 0)
		{
			m_AnimatorBody->Play(L"BIdleDown", true);
			m_AnimatorHead->Play(L"HIdleDown", true);

		}
	}

	if (KEY_PRESSED(D) && 0 == m_TearsCount)
	{
		m_Movement->AddForce(Vec2(1000.f, 0.f));

		if (m_IsDamaged == 0)
		{

			m_AnimatorBody->Play(L"BWalkRight", true);
			m_AnimatorHead->Play(L"HIdleRight", true);
		}
	}
	if (KEY_RELEASED(D) && 0 == m_TearsCount)
	{
		if (m_IsDamaged == 0)
		{
			m_AnimatorBody->Play(L"BIdleDown", true);
			m_AnimatorHead->Play(L"HIdleDown", true);

		}
	}

	if (KEY_PRESSED(W) && 0 == m_TearsCount)
	{
		m_Movement->AddForce(Vec2(0.f, -1000.f));

		if (m_IsDamaged == 0)
		{
			m_AnimatorBody->Play(L"BWalkDown", true);
			m_AnimatorHead->Play(L"HIdleUp", true);

		}
	}
	if (KEY_RELEASED(W) && 0 == m_TearsCount)
	{
		if (m_IsDamaged == 0)
		{

			m_AnimatorBody->Play(L"BIdleDown", true);
			m_AnimatorHead->Play(L"HIdleDown", true);
		}
	}

	if (KEY_PRESSED(S) && 0 == m_TearsCount)
	{
		m_Movement->AddForce(Vec2(0.f, 1000.f));

		if (m_IsDamaged == 0)
		{
			m_AnimatorBody->Play(L"BWalkDown", true);
			m_AnimatorHead->Play(L"HIdleDown", true);

		}
	}
	if (KEY_RELEASED(S) && 0 == m_TearsCount)
	{
		if (m_IsDamaged == 0)
		{
			m_AnimatorBody->Play(L"BIdleDown", true);
			m_AnimatorHead->Play(L"HIdleDown", true);

		}
	}

	// 눈물을 쏘면서 움직일 때
	if (KEY_TAP(LEFT))
	{
		++m_TearsCount;
	}
	else if (KEY_PRESSED(LEFT))
	{
		if (m_IsDamaged == 0)
		{
			m_AnimatorHead->Play(L"HTearLeft", true);
		
			if (m_Duration <= m_Acctime)
			{
				m_FireSound->SetVolume(100.f);
				m_FireSound->SetPosition(0.f);
				m_FireSound->Play(false);

				MyTears* pTears = new MyTears;

				Vec2 TearsPos = GetPos();
				TearsPos.x -= 20.f;
				TearsPos.y -= 25.f;

				pTears->SetSpeed(450.f);
				pTears->SetvAngle(Vec2(-1.f, 0.f));
				pTears->SetScale(Vec2(1.4f, 1.4f));
				pTears->SetOffsetPos(Vec2(-14.f, -18.f));
				pTears->SetPos(TearsPos);

				MyTaskMgr::GetInst()->AddTask(FTask{ TASK_TYPE::CREATE_OBJECT, (UINT_PTR)LAYER::TEARS, (UINT_PTR)pTears });

				pTears->fire();

				m_Acctime = 0.f;
			}
		}

		if (KEY_PRESSED(A) && 0 != m_TearsCount)
		{
			m_Movement->AddForce(Vec2(-1000.f, 0.f));
			if (m_IsDamaged == 0)
			{

				m_AnimatorBody->Play(L"BWalkLeft", true);
			}
		}
		if (KEY_RELEASED(A) && 0 != m_TearsCount)
		{
			if (m_IsDamaged == 0)
			{

				m_AnimatorBody->Play(L"BIdleDown", true);
				m_AnimatorHead->Play(L"HIdleDown", true);
			}
		}

		if (KEY_PRESSED(D) && 0 != m_TearsCount)
		{
			m_Movement->AddForce(Vec2(1000.f, 0.f));

			if (m_IsDamaged == 0)
			{

				m_AnimatorBody->Play(L"BWalkRight", true);
			}
		}
		if (KEY_RELEASED(D) && 0 != m_TearsCount)
		{
			if (m_IsDamaged == 0)
			{

				m_AnimatorBody->Play(L"BIdleDown", true);
				m_AnimatorHead->Play(L"HIdleDown", true);
			}
		}

		if (KEY_PRESSED(W) && 0 != m_TearsCount)
		{
			m_Movement->AddForce(Vec2(0.f, -1000.f));

			if (m_IsDamaged == 0)
			{
				m_AnimatorBody->Play(L"BWalkDown", true);

			}
		}
		if (KEY_RELEASED(W) && 0 != m_TearsCount)
		{
			if (m_IsDamaged == 0)
			{

				m_AnimatorBody->Play(L"BIdleDown", true);
				m_AnimatorHead->Play(L"HIdleDown", true);
			}
		}

		if (KEY_PRESSED(S) && 0 != m_TearsCount)
		{
			m_Movement->AddForce(Vec2(0.f, 1000.f));
			if (m_IsDamaged == 0)
			{
				m_AnimatorBody->Play(L"BWalkDown", true);

			}
		}
		if (KEY_RELEASED(S) && 0 != m_TearsCount)
		{
			if (m_IsDamaged == 0)
			{

				m_AnimatorBody->Play(L"BIdleDown", true);
				m_AnimatorHead->Play(L"HIdleDown", true);
			}
		}
	}
	else if (KEY_RELEASED(LEFT))
	{
		if (m_IsDamaged == 0)
		{

			m_AnimatorHead->Play(L"HIdleDown", true);
		}
			--m_TearsCount;
	}

	if (KEY_TAP(RIGHT))
	{
		++m_TearsCount;
	}
	else if (KEY_PRESSED(RIGHT))
	{
		if (m_IsDamaged == 0)
		{

			m_AnimatorHead->Play(L"HTearRight", true);

			if (m_Duration <= m_Acctime)
			{
				m_FireSound->SetVolume(100.f);
				m_FireSound->SetPosition(0.f);
				m_FireSound->Play(false);

				MyTears* pTears = new MyTears;

				Vec2 TearsPos = GetPos();
				TearsPos.x += 12.f;
				TearsPos.y -= 25.f;

				pTears->SetSpeed(450.f);
				pTears->SetvAngle(Vec2(1.f, 0.f));
				pTears->SetScale(Vec2(1.4f, 1.4f));
				pTears->SetOffsetPos(Vec2(-14.f, -18.f));
				pTears->SetPos(TearsPos);

				MyTaskMgr::GetInst()->AddTask(FTask{ TASK_TYPE::CREATE_OBJECT, (UINT_PTR)LAYER::TEARS, (UINT_PTR)pTears });

				pTears->fire();

				m_Acctime = 0.f;
			}
		}

		if (KEY_PRESSED(A) && 0 != m_TearsCount)
		{
			m_Movement->AddForce(Vec2(-1000.f, 0.f));
			if (m_IsDamaged == 0)
			{

			m_AnimatorBody->Play(L"BWalkLeft", true);
			}
		}
		if (KEY_RELEASED(A) && 0 != m_TearsCount)
		{
			if (m_IsDamaged == 0)
			{

			m_AnimatorBody->Play(L"BIdleDown", true);
			m_AnimatorHead->Play(L"HIdleDown", true);
			}
		}

		if (KEY_PRESSED(D) && 0 != m_TearsCount)
		{
			m_Movement->AddForce(Vec2(1000.f, 0.f));
			if (m_IsDamaged == 0)
			{

			m_AnimatorBody->Play(L"BWalkRight", true);
			}
		}
		if (KEY_RELEASED(D) && 0 != m_TearsCount)
		{
			if (m_IsDamaged == 0)
			{

			m_AnimatorBody->Play(L"BIdleDown", true);
			m_AnimatorHead->Play(L"HIdleDown", true);
			}
		}

		if (KEY_PRESSED(W) && 0 != m_TearsCount)
		{
			m_Movement->AddForce(Vec2(0.f, -1000.f));
			
			if (m_IsDamaged == 0)
			{

			m_AnimatorBody->Play(L"BWalkDown", true);
			}
		}
		if (KEY_RELEASED(W) && 0 != m_TearsCount)
		{
			if (m_IsDamaged == 0)
			{

			m_AnimatorBody->Play(L"BIdleDown", true);
			m_AnimatorHead->Play(L"HIdleDown", true);
			}
		}

		if (KEY_PRESSED(S) && 0 != m_TearsCount)
		{
			m_Movement->AddForce(Vec2(0.f, 1000.f));
			
			if (m_IsDamaged == 0)
			{

			m_AnimatorBody->Play(L"BWalkDown", true);
			}
		}
		if (KEY_RELEASED(S) && 0 != m_TearsCount)
		{
			if (m_IsDamaged == 0)
			{

			m_AnimatorBody->Play(L"BIdleDown", true);
			m_AnimatorHead->Play(L"HIdleDown", true);
			}
		}
	}
	else if (KEY_RELEASED(RIGHT))
	{
		if (m_IsDamaged == 0)
		{

		m_AnimatorHead->Play(L"HIdleDown", true);
		}
		--m_TearsCount;
	}

	if (KEY_TAP(UP))
	{
		++m_TearsCount;
	}
	else if (KEY_PRESSED(UP))
	{
		if (m_IsDamaged == 0)
		{

		m_AnimatorHead->Play(L"HTearUp", true);

		if (m_Duration <= m_Acctime)
		{
			m_FireSound->SetVolume(100.f);
			m_FireSound->SetPosition(0.f);
			m_FireSound->Play(false);

			MyTears* pTears = new MyTears;

			Vec2 TearsPos = GetPos();
			TearsPos.x -= 8.f;
			TearsPos.y -= 60.f;

			pTears->SetSpeed(450.f);
			pTears->SetvAngle(Vec2(0.f, -1.f));
			pTears->SetScale(Vec2(1.4f, 1.4f));
			pTears->SetOffsetPos(Vec2(-14.f, -18.f));
			pTears->SetPos(TearsPos);

			MyTaskMgr::GetInst()->AddTask(FTask{ TASK_TYPE::CREATE_OBJECT, (UINT_PTR)LAYER::TEARS, (UINT_PTR)pTears });

			pTears->fire();

			m_Acctime = 0.f;
		}
		}

		if (KEY_PRESSED(A) && 0 != m_TearsCount)
		{
			m_Movement->AddForce(Vec2(-1000.f, 0.f));
			if (m_IsDamaged == 0)
			{

			m_AnimatorBody->Play(L"BWalkLeft", true);
			}
		}
		if (KEY_RELEASED(A) && 0 != m_TearsCount)
		{
			if (m_IsDamaged == 0)
			{

			m_AnimatorBody->Play(L"BIdleDown", true);
			m_AnimatorHead->Play(L"HIdleDown", true);
			}
		}

		if (KEY_PRESSED(D) && 0 != m_TearsCount)
		{
			m_Movement->AddForce(Vec2(1000.f, 0.f));
			
			if (m_IsDamaged == 0)
			{

			m_AnimatorBody->Play(L"BWalkRight", true);
			}
		}
		if (KEY_RELEASED(D) && 0 != m_TearsCount)
		{
			if (m_IsDamaged == 0)
			{

			m_AnimatorBody->Play(L"BIdleDown", true);
			m_AnimatorHead->Play(L"HIdleDown", true);
			}
		}

		if (KEY_PRESSED(W) && 0 != m_TearsCount)
		{
			m_Movement->AddForce(Vec2(0.f, -1000.f));
			if (m_IsDamaged == 0)
			{

			m_AnimatorBody->Play(L"BWalkDown", true);
			}
		}
		if (KEY_RELEASED(W) && 0 != m_TearsCount)
		{
			if (m_IsDamaged == 0)
			{

			m_AnimatorBody->Play(L"BIdleDown", true);
			m_AnimatorHead->Play(L"HIdleDown", true);
			}
		}

		if (KEY_PRESSED(S) && 0 != m_TearsCount)
		{
			m_Movement->AddForce(Vec2(0.f, 1000.f));
			
			if (m_IsDamaged == 0)
			{

			m_AnimatorBody->Play(L"BWalkDown", true);
			}
		}
		if (KEY_RELEASED(S) && 0 != m_TearsCount)
		{
			if (m_IsDamaged == 0)
			{

			m_AnimatorBody->Play(L"BIdleDown", true);
			m_AnimatorHead->Play(L"HIdleDown", true);
			}
		}
	}
	else if (KEY_RELEASED(UP))
	{
		if (m_IsDamaged == 0)
		{

		m_AnimatorHead->Play(L"HIdleDown", true);
		}
		--m_TearsCount;
	}

	if (KEY_TAP(DOWN))
	{
		++m_TearsCount;
	}
	else if (KEY_PRESSED(DOWN))
	{
		if (m_IsDamaged == 0)
		{

		m_AnimatorHead->Play(L"HTearDown", true);

		if (m_Duration <= m_Acctime)
		{
			m_FireSound->SetVolume(100.f);
			m_FireSound->SetPosition(0.f);
			m_FireSound->Play(false);

			MyTears* pTears = new MyTears;

			Vec2 TearsPos = GetPos();
			TearsPos.x -= 4.f;
			TearsPos.y -= 10.f;

			pTears->SetSpeed(450.f);
			pTears->SetvAngle(Vec2(0.f, 1.f));
			pTears->SetScale(Vec2(1.4f, 1.4f));
			pTears->SetOffsetPos(Vec2(-14.f, -18.f));
			pTears->SetPos(TearsPos);

			MyTaskMgr::GetInst()->AddTask(FTask{ TASK_TYPE::CREATE_OBJECT, (UINT_PTR)LAYER::TEARS, (UINT_PTR)pTears });

			pTears->fire();

			m_Acctime = 0.f;
		}
		}

		if (KEY_PRESSED(A) && 0 != m_TearsCount)
		{
			m_Movement->AddForce(Vec2(-1000.f, 0.f));
			
			if (m_IsDamaged == 0)
			{

			m_AnimatorBody->Play(L"BWalkLeft", true);
			}
		}
		if (KEY_RELEASED(A) && 0 != m_TearsCount)
		{
			if (m_IsDamaged == 0)
			{

			m_AnimatorBody->Play(L"BIdleDown", true);
			m_AnimatorHead->Play(L"HIdleDown", true);
			}
		}

		if (KEY_PRESSED(D) && 0 != m_TearsCount)
		{
			m_Movement->AddForce(Vec2(1000.f, 0.f));
			if (m_IsDamaged == 0)
			{

			m_AnimatorBody->Play(L"BWalkRight", true);
			}
		}
		if (KEY_RELEASED(D) && 0 != m_TearsCount)
		{
			if (m_IsDamaged == 0)
			{

			m_AnimatorBody->Play(L"BIdleDown", true);
			m_AnimatorHead->Play(L"HIdleDown", true);
			}
		}

		if (KEY_PRESSED(W) && 0 != m_TearsCount)
		{
			m_Movement->AddForce(Vec2(0.f, -1000.f));
			
			if (m_IsDamaged == 0)
			{

			m_AnimatorBody->Play(L"BWalkDown", true);
			}
		}
		if (KEY_RELEASED(W) && 0 != m_TearsCount)
		{
			if (m_IsDamaged == 0)
			{

			m_AnimatorBody->Play(L"BIdleDown", true);
			m_AnimatorHead->Play(L"HIdleDown", true);
			}
		}

		if (KEY_PRESSED(S) && 0 != m_TearsCount)
		{
			m_Movement->AddForce(Vec2(0.f, 1000.f));
			if (m_IsDamaged == 0)
			{

			m_AnimatorBody->Play(L"BWalkDown", true);
			}
		}
		if (KEY_RELEASED(S) && 0 != m_TearsCount)
		{
			if (m_IsDamaged == 0)
			{

			m_AnimatorBody->Play(L"BIdleDown", true);
			m_AnimatorHead->Play(L"HIdleDown", true);
			}
		}
	}
	else if (KEY_RELEASED(DOWN))
	{
		if (m_IsDamaged == 0)
		{

		m_AnimatorHead->Play(L"HIdleDown", true);
		}
		--m_TearsCount;
	}


	SetPos(vPos);
	m_Shadow->SetPos(vPos);
}

void MyPlayer::render(HDC _dc)
{
	if (m_IsRender)
	{
		Super::render(_dc);
	}

}


void MyPlayer::BeginOverlap(MyCollider* _OwnCol, MyObject* _OtherObj, MyCollider* _OtherCol)
{
	wstring str = _OtherCol ->GetName();

	if (str != L"TrophyCollider")
	{
		m_IsRender = false;
		m_IsDamaged = 1;
		m_DamagedMaxTime = 0.5f;
		m_AnimatorHead->Play(L"IssacDamagedAnim", false);
		m_AnimatorBody->Play(L"IssacDamagedAnim", false);

		m_DamageSound->SetVolume(80.f);
		m_DamageSound->SetPosition(0.f);
		m_DamageSound->Play();
	}
}

void MyPlayer::EndOverlap(MyCollider* _OwnCol, MyObject* _OtherObj, MyCollider* _OtherCol)
{
	wstring str = _OtherCol->GetName();

	if (str != L"TrophyCollider")
	{
		m_AnimatorHead->WaitPlay(L"HIdleDown", false, 0.2f);
		m_AnimatorBody->WaitPlay(L"BIdleDown", false, 0.2f);
	}
}