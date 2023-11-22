#include "pch.h"
#include "BossMonster.h"

#include "MyAssetMgr.h"
#include "MyLevelMgr.h"
#include "MyLevel.h"
#include "MyLayer.h"
#include "MyTimeMgr.h"
#include "MyTexture.h"
#include "MyRoom.h"
#include "MyTears.h"
#include "NormalFly.h"
#include "MyMonsterTears.h"
#include "components.h"
#include "MyBossDeadEffect.h"
#include "MySound.h"
#include "MyTrophy.h"

BossMonster::BossMonster()
	: m_Atlas(nullptr)
	, m_MonsterShadow(nullptr)
	, m_Collider(nullptr)
	, m_Animator(nullptr)
	, m_Movement(nullptr)
	, m_MoveTime(0.f)
	, m_StartMoveTime(2.f)
	, m_ChangeDirTime(7.f)
	, m_Info{}
	, m_AttTime(0.f)
	, m_StartAttTime(2.f)
	, m_AttDelay(6.f)
	, m_MonsCount(0)
	, m_SummonFly(nullptr)
{
	m_Atlas = MyAssetMgr::GetInst()->LoadTexture(L"Boss", L"texture\\Boss\\boss_dukeofflies.png");
	m_MonsterShadow = MyAssetMgr::GetInst()->LoadTexture(L"Shadow", L"texture\\Effect\\shadow.png");

	m_Movement = AddComponent<MyMovement>(L"BossMovement");
	m_Movement->SetVelocity(Vec2(0.f, 0.f));
	m_Movement->SetInitSpeed(50.f);
	m_Movement->SetMaxSpeed(50.f);

	m_Animator = AddComponent<MyAnimator>(L"BossAnimator");
	m_Animator->LoadAnimation(L"animdata\\BossIdleAnim.txt");
	m_Animator->LoadAnimation(L"animdata\\BossAttackAnim1.txt");
	m_Animator->LoadAnimation(L"animdata\\BossAttackAnim2.txt");
	m_Animator->LoadAnimation(L"animdata\\BossAttackSpawnAnim1.txt");
	m_Animator->LoadAnimation(L"animdata\\BossAttackSpawnAnim2.txt");
	m_Animator->Play(L"BossIdleAnim", true);

	m_Collider = AddComponent<MyCollider>(L"BossCollider");
	m_Collider->SetScale(Vec2(100.f, 100.f));
	m_Collider->SetOffsetPos(Vec2(0.f, -50.f));

	m_Info.HP = 10.f;

	m_SummonFly = MyAssetMgr::GetInst()->LoadSound(L"SummonFly", L"sound\\boss_lite_roar_1.wav");

	srand((UINT)time(NULL));
}

BossMonster::~BossMonster()
{
}

void BossMonster::begin()
{
	if (m_IsDead == true)
	{
		return;
	}

	GetStartDir();
}

void BossMonster::tick(float _DT)
{
	if (m_IsDead == true || m_IsActive == false)
	{
		return;
	}

	Super::tick(_DT);

	m_MoveTime += _DT;

	if (m_MoveTime >= m_StartMoveTime)
	{
		m_AttTime += _DT;

		if (m_ChangeDirTime <= m_MoveTime)
		{
			int ran = rand() % 4;
			switch ((FKDir)ran)
			{
			case FKDir::UP:
				ChangeDirectionU();
				break;
			case FKDir::DOWN:
				ChangeDirectionD();
				break;
			case FKDir::LEFT:
				ChangeDirectionL();
				break;
			case FKDir::RIGHT:
				ChangeDirectionR();
				break;
			default:
				break;
			}

			m_MoveTime = 2.f;
		}
	}
}

void BossMonster::render(HDC _dc)
{
	if (m_IsDead == true || m_IsActive == false)
	{
		return;
	}

	Vec2 vRenderPos = GetRenderPos();
	Vec2 vScale = Vec2(1.f, 1.f);
	Vec2 vOffset = Vec2(-60.f, 0.f);

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

void BossMonster::BeginOverlap(MyCollider* _OwnCol, MyObject* _OtherObj, MyCollider* _OtherCol)
{
	if (!m_IsDead)
	{
		if ((_OtherCol->GetName() == L"RoomColliderUp1" || _OtherCol->GetName() == L"RoomColliderUp2"
			|| _OtherCol->GetName() == L"RoomColliderUp3" || _OtherCol->GetName() == L"CloseUpDoorCollider")
			&& _OwnCol->GetName() == L"BossCollider")
		{
			SetStartDir(FKDir::DOWN);
		}

		if ((_OtherCol->GetName() == L"RoomColliderDown1" || _OtherCol->GetName() == L"RoomColliderDown2"
			|| _OtherCol->GetName() == L"RoomColliderDown3" || _OtherCol->GetName() == L"CloseDownDoorCollider")
			&& _OwnCol->GetName() == L"BossCollider")
		{
			SetStartDir(FKDir::UP);
		}

		if ((_OtherCol->GetName() == L"RoomColliderLeft1" || _OtherCol->GetName() == L"RoomColliderLeft2"
			|| _OtherCol->GetName() == L"RoomColliderLeft3" || _OtherCol->GetName() == L"CloseLeftDoorCollider")
			&& _OwnCol->GetName() == L"BossCollider")
		{
			SetStartDir(FKDir::RIGHT);
		}

		if ((_OtherCol->GetName() == L"RoomColliderRight1" || _OtherCol->GetName() == L"RoomColliderRight2"
			|| _OtherCol->GetName() == L"RoomColliderRight3" || _OtherCol->GetName() == L"CloseRightDoorCollider")
			&& _OwnCol->GetName() == L"BossCollider")
		{
			SetStartDir(FKDir::LEFT);
		}
	}


	if (dynamic_cast<MyTears*>(_OtherObj) && _OwnCol->GetName() == L"BossCollider")
	{
		m_Info.HP -= 1.f;

		if (m_Info.HP <= 0.f)
		{
			m_IsDead = true;
			MyBossDeadEffect* pBDE = new MyBossDeadEffect;
			pBDE->SetPos(GetPos());
			pBDE->SetScale(Vec2(1.f, 1.f));
			pBDE->SetOffsetPos(Vec2(-15.f, -20.f));
			MyTaskMgr::GetInst()->AddTask(FTask{ TASK_TYPE::CREATE_OBJECT, (UINT_PTR)LAYER::EFFECT, (UINT_PTR)pBDE });
		}
	}
}


void BossMonster::ChangeDirectionU()
{
	m_Movement->SetVelocity(Vec2(-100.f, -100.f));

	if (m_AttTime >= m_StartAttTime)
	{
		if (m_AttTime >= m_AttDelay)
		{
			int ran = rand() % 2;
			switch ((ATT_TYPE)ran)
			{
			case ATT_TYPE::ATT1:
				Attack01();
				break;
			case ATT_TYPE::ATT2:
				Attack02();
				break;
			default:
				break;
			}

			m_AttTime = 2.f;
		}
	}
}

void BossMonster::ChangeDirectionD()
{
	m_Movement->SetVelocity(Vec2(100.f, 100.f));

	if (m_AttTime >= m_StartAttTime)
	{
		if (m_AttTime >= m_AttDelay)
		{
			int ran = rand() % 2;
			switch ((ATT_TYPE)ran)
			{
			case ATT_TYPE::ATT1:
				Attack01();
				break;
			case ATT_TYPE::ATT2:
				Attack02();
				break;
			default:
				break;
			}

			m_AttTime = 2.f;
		}
	}
}

void BossMonster::ChangeDirectionL()
{
	m_Movement->SetVelocity(Vec2(-100.f, 100.f));

	if (m_AttTime >= m_StartAttTime)
	{
		if (m_AttTime >= m_AttDelay)
		{
			int ran = rand() % 2;
			switch ((ATT_TYPE)ran)
			{
			case ATT_TYPE::ATT1:
				Attack01();
				break;
			case ATT_TYPE::ATT2:
				Attack02();
				break;
			default:
				break;
			}

			m_AttTime = 2.f;
		}
	}
}

void BossMonster::ChangeDirectionR()
{
	m_Movement->SetVelocity(Vec2(100.f, -100.f));

	if (m_AttTime >= m_StartAttTime)
	{
		if (m_AttTime >= m_AttDelay)
		{
			int ran = rand() % 3;
			switch ((ATT_TYPE)ran)
			{
			case ATT_TYPE::ATT1:
				Attack01();
				break;
			case ATT_TYPE::ATT2:
				Attack02();
				break;
			default:
				break;
			}

			m_AttTime = 2.f;
		}
	}
}


void BossMonster::SetStartDir(FKDir _dir)
{
	switch (_dir)
	{
	case FKDir::UP:
		ChangeDirectionU();
		break;
	case FKDir::DOWN:
		ChangeDirectionD();
		break;
	case FKDir::LEFT:
		ChangeDirectionL();
		break;
	case FKDir::RIGHT:
		ChangeDirectionR();
		break;
	default:
		break;
	}
}



void BossMonster::Attack01()
{
	m_AttType = ATT_TYPE::ATT1;
	m_Animator->Play(L"BossAttackAnim1", false);
	m_Animator->FindAnim(L"BossAttackAnim2")->Reset();
	SpawnFly();
}

void BossMonster::Attack02()
{
	m_AttType = ATT_TYPE::ATT2;
	m_Animator->Play(L"BossAttackAnim2", false);
	m_Animator->FindAnim(L"BossAttackAnim1")->Reset();

	SpawnFly();
}

void BossMonster::SpawnFly()
{
	Vec2 vPos = GetPos();
	if (m_AttType == ATT_TYPE::ATT1)
	{
		m_Animator->Play(L"BossAttackSpawnAnim1", false);
		m_Animator->FindAnim(L"BossAttackSpawnAnim1")->Reset();
		m_Animator->FindAnim(L"BossAttackSpawnAnim2")->Reset();
	}
	else if (m_AttType == ATT_TYPE::ATT2)
	{
		m_Animator->Play(L"BossAttackSpawnAnim2", false);
		m_Animator->FindAnim(L"BossAttackSpawnAnim1")->Reset();
		m_Animator->FindAnim(L"BossAttackSpawnAnim2")->Reset();
	}

	auto objects = MyLevelMgr::GetInst()->GetCurLevel()->GetLayer((UINT)LAYER::ROOM)->GetObjects();

	NormalFly* pFly = new NormalFly;
	pFly->SetPos(Vec2(-10000.f, -10000.f));
	pFly->SetInitPos(Vec2(vPos.x - 50.f, vPos.y + 50.f));
	pFly->SetScale(Vec2(2.f, 2.f));
	pFly->SetOffsetPos(Vec2(-15.f, -25.f));
	MyTaskMgr::GetInst()->AddTask(FTask{ TASK_TYPE::CREATE_OBJECT, (UINT_PTR)LAYER::MONSTER, (UINT_PTR)pFly });

	NormalFly* pFly2 = new NormalFly;
	pFly2->SetPos(Vec2(-10000.f, -10000.f));
	pFly2->SetInitPos(Vec2(vPos.x + 50.f, vPos.y + 50.f));
	pFly2->SetScale(Vec2(2.f, 2.f));
	pFly2->SetOffsetPos(Vec2(-15.f, -25.f));
	MyTaskMgr::GetInst()->AddTask(FTask{ TASK_TYPE::CREATE_OBJECT, (UINT_PTR)LAYER::MONSTER, (UINT_PTR)pFly2 });

	NormalFly* pFly3 = new NormalFly;
	pFly3->SetPos(Vec2(-10000.f, -10000.f));
	pFly3->SetInitPos(Vec2(vPos.x + 50.f, vPos.y - 50.f));
	pFly3->SetScale(Vec2(2.f, 2.f));
	pFly3->SetOffsetPos(Vec2(-15.f, -25.f));
	MyTaskMgr::GetInst()->AddTask(FTask{ TASK_TYPE::CREATE_OBJECT, (UINT_PTR)LAYER::MONSTER, (UINT_PTR)pFly3 });

	dynamic_cast<MyRoom*>(objects[(UINT)ROOM_TYPE::BOSS])->AddMonster(pFly);
	dynamic_cast<MyRoom*>(objects[(UINT)ROOM_TYPE::BOSS])->AddMonster(pFly2);
	dynamic_cast<MyRoom*>(objects[(UINT)ROOM_TYPE::BOSS])->AddMonster(pFly3);

	pFly->SetToInitPos();
	pFly2->SetToInitPos();
	pFly3->SetToInitPos();

	m_SummonFly->SetVolume(80.f);
	m_SummonFly->SetPosition(0.f);
	m_SummonFly->Play();
}
