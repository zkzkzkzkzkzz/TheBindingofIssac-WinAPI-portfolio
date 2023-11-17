#include "pch.h"
#include "FloatingKnight.h"
#include "MyAssetMgr.h"
#include "MyTimeMgr.h"
#include "MyTexture.h"
#include "MyTears.h"
#include "components.h"
#include "MyFKDeadEffect.h"

FloatingKnight::FloatingKnight()
	: m_Atlas(nullptr)
	, m_MonsterShadow(nullptr)
	, m_HeadCollider(nullptr)
	, m_TailCollider(nullptr)
	, m_Animator(nullptr)
	, m_Movement(nullptr)
	, m_Info{}
	, m_MoveTime(0.f)
	, m_StartMoveTime(1.f)
	, m_ChangeDirTime(10.f)
{
	m_Atlas = MyAssetMgr::GetInst()->LoadTexture(L"FloatingKnight", L"texture\\monster\\monster_floatingknight.png");
	m_MonsterShadow = MyAssetMgr::GetInst()->LoadTexture(L"Shadow", L"texture\\Effect\\shadow.png");

	m_Animator = AddComponent<MyAnimator>(L"FKAnimator");
	m_Animator->LoadAnimation(L"animdata\\FloatingKnightDownAnim.txt");
	m_Animator->LoadAnimation(L"animdata\\FloatingKnightUpAnim.txt");
	m_Animator->LoadAnimation(L"animdata\\FloatingKnightRightAnim.txt");
	m_Animator->LoadAnimation(L"animdata\\FloatingKnightLeftAnim.txt");
	m_Animator->Play(L"FloatingKnightDownAnim", true);

	m_HeadCollider = AddComponent<MyCollider>(L"FKHeadCollider");

	m_TailCollider = AddComponent<MyCollider>(L"FKTailCollider");

	m_Movement = AddComponent<MyMovement>(L"FKMovement");
	m_Movement->SetVelocity(Vec2(0.f, 100.f));
	m_Movement->SetInitSpeed(30.f);
	m_Movement->SetMaxSpeed(30.f);


	m_Info.HP = 3.f;

	srand((UINT)time(NULL));
}

FloatingKnight::~FloatingKnight()
{
}



void FloatingKnight::begin()
{
	if (m_IsDead == true)
	{
		return;
	}

	GetStartDir();
}

void FloatingKnight::tick(float _DT)
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

void FloatingKnight::render(HDC _dc)
{
	if (m_IsDead == true)
	{
		return;
	}

	Vec2 vRenderPos = GetRenderPos();
	Vec2 vScale = Vec2(0.4f, 0.4f);
	Vec2 vOffset = Vec2(-22.f, -5.f);

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

void FloatingKnight::BeginOverlap(MyCollider* _OwnCol, MyObject* _OtherObj, MyCollider* _OtherCol)
{
	if (!m_IsDead)
	{
		if ((_OtherCol->GetName() == L"RoomColliderUp1" || _OtherCol->GetName() == L"RoomColliderUp2"
			|| _OtherCol->GetName() == L"RoomColliderUp3" || _OtherCol->GetName() == L"CloseUpDoorCollider")
			&& _OwnCol->GetName() == L"FKHeadCollider")
		{
			SetStartDir(FKDir::DOWN);
		}

		if ((_OtherCol->GetName() == L"RoomColliderDown1" || _OtherCol->GetName() == L"RoomColliderDown2"
			|| _OtherCol->GetName() == L"RoomColliderDown3" || _OtherCol->GetName() == L"CloseDownDoorCollider")
			&& _OwnCol->GetName() == L"FKHeadCollider")
		{
			SetStartDir(FKDir::UP);
		}

		if ((_OtherCol->GetName() == L"RoomColliderLeft1" || _OtherCol->GetName() == L"RoomColliderLeft2"
			|| _OtherCol->GetName() == L"RoomColliderLeft3" || _OtherCol->GetName() == L"CloseLeftDoorCollider")
			&& _OwnCol->GetName() == L"FKHeadCollider")
		{
			SetStartDir(FKDir::RIGHT);
		}

		if ((_OtherCol->GetName() == L"RoomColliderRight1" || _OtherCol->GetName() == L"RoomColliderRight2"
			|| _OtherCol->GetName() == L"RoomColliderRight3" || _OtherCol->GetName() == L"CloseRightDoorCollider")
			&& _OwnCol->GetName() == L"FKHeadCollider")
		{
			SetStartDir(FKDir::LEFT);
		}
	}
	

	if (dynamic_cast<MyTears*>(_OtherObj) && _OwnCol->GetName() == L"FKTailCollider")
	{
		m_Info.HP -= 1.f;

		if (m_Info.HP <= 0.f)
		{
			m_IsDead = true;
			MyFKDeadEffect* pFDE = new MyFKDeadEffect;
			pFDE->SetPos(GetPos());
			pFDE->SetScale(Vec2(1.5f, 1.5f));
			pFDE->SetOffsetPos(Vec2(-15.f, -20.f));
			MyTaskMgr::GetInst()->AddTask(FTask{ TASK_TYPE::CREATE_OBJECT, (UINT_PTR)LAYER::DOOR, (UINT_PTR)pFDE });
			//Destroy();
		}
	}
}


void FloatingKnight::ChangeDirectionU()
{
	m_Movement->SetVelocity(Vec2(0.f, -100.f));

	m_HeadCollider->SetScale(Vec2(50.f, 20.f));
	m_HeadCollider->SetOffsetPos(Vec2(0.f, -35.f));

	m_TailCollider->SetScale(Vec2(50.f, 30.f));
	m_TailCollider->SetOffsetPos(Vec2(0.f, -15.f));

	m_Animator->Play(L"FloatingKnightUpAnim", true);
}

void FloatingKnight::ChangeDirectionD()
{
	m_Movement->SetVelocity(Vec2(0.f, 100.f));

	m_HeadCollider->SetScale(Vec2(40.f, 40.f));
	m_HeadCollider->SetOffsetPos(Vec2(0.f, -19.f));

	m_TailCollider->SetScale(Vec2(40.f, 20.f));
	m_TailCollider->SetOffsetPos(Vec2(0.f, -40.f));

	m_Animator->Play(L"FloatingKnightDownAnim", true);
}

void FloatingKnight::ChangeDirectionL()
{
	m_Movement->SetVelocity(Vec2(-100.f, 0.f));

	m_HeadCollider->SetScale(Vec2(20.f, 50.f));
	m_HeadCollider->SetOffsetPos(Vec2(-10.f, -25.f));

	m_TailCollider->SetScale(Vec2(30.f, 45.f));
	m_TailCollider->SetOffsetPos(Vec2(10.f, -25.f));

	m_Animator->Play(L"FloatingKnightLeftAnim", true);
}

void FloatingKnight::ChangeDirectionR()
{
	m_Movement->SetVelocity(Vec2(100.f, 0.f));

	m_HeadCollider->SetScale(Vec2(30.f, 50.f));
	m_HeadCollider->SetOffsetPos(Vec2(10.f, -25.f));

	m_TailCollider->SetScale(Vec2(20.f, 45.f));
	m_TailCollider->SetOffsetPos(Vec2(-10.f, -25.f));

	m_Animator->Play(L"FloatingKnightRightAnim", true);
}

void FloatingKnight::SetStartDir(FKDir _dir)
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
