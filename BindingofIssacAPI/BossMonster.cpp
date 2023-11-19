#include "pch.h"
#include "BossMonster.h"
#include "MyAssetMgr.h"
#include "MyTimeMgr.h"
#include "MyTexture.h"
#include "MyTears.h"
#include "components.h"
#include "MyFKDeadEffect.h"

BossMonster::BossMonster()
	: m_Atlas(nullptr)
	, m_MonsterShadow(nullptr)
	, m_Collider(nullptr)
	, m_Animator(nullptr)
	, m_Movement(nullptr)
	, m_MoveTime(0.f)
	, m_StartMoveTime(1.f)
	, m_ChangeDirTime(8.f)
	, m_Info{}
{
	m_Atlas = MyAssetMgr::GetInst()->LoadTexture(L"Boss", L"texture\\Boss\\boss_dukeofflies.png");
	m_MonsterShadow = MyAssetMgr::GetInst()->LoadTexture(L"Shadow", L"texture\\Effect\\shadow.png");

	m_Animator = AddComponent<MyAnimator>(L"BossAnimator");
	m_Animator->LoadAnimation(L"animdata\\BossIdleAnim.txt");
	m_Animator->LoadAnimation(L"animdata\\BossAttackAnim1.txt");
	m_Animator->LoadAnimation(L"animdata\\BossAttackAnim2.txt");
	m_Animator->Play(L"BossIdleAnim", true);

	m_Collider = AddComponent<MyCollider>(L"BossCollider");
	m_Collider->SetScale(Vec2(100.f, 100.f));
	m_Collider->SetOffsetPos(Vec2(0.f, -50.f));

	m_Movement = AddComponent<MyMovement>(L"BossMovement");
	m_Movement->SetVelocity(Vec2(0.f, 0.f));
	m_Movement->SetInitSpeed(50.f);
	m_Movement->SetMaxSpeed(50.f);

	m_Info.HP = 10.f;

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
	if (m_IsDead == true)
	{
		return;
	}
	m_MoveTime += _DT;

	if (m_MoveTime >= m_StartMoveTime)
	{
		Super::tick(_DT);


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

			m_MoveTime = 1.f;
		}
	}
}

void BossMonster::render(HDC _dc)
{
	if (m_IsDead == true)
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
			
			//Destroy();
		}
	}
}


void BossMonster::ChangeDirectionU()
{
	m_Movement->SetVelocity(Vec2(0.f, -100.f));
}

void BossMonster::ChangeDirectionD()
{
	m_Movement->SetVelocity(Vec2(0.f, 100.f));
}

void BossMonster::ChangeDirectionL()
{
	m_Movement->SetVelocity(Vec2(-100.f, 0.f));
}

void BossMonster::ChangeDirectionR()
{
	m_Movement->SetVelocity(Vec2(100.f, 0.f));
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
	m_Animator->Play(L"BossAttackAnim1", false);
}

void BossMonster::Attack02()
{
	m_Animator->Play(L"BossAttackAnim2", false);
}