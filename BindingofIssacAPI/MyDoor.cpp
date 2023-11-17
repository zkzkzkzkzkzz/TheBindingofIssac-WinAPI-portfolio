#include "pch.h"
#include "MyDoor.h"

#include "MyAssetMgr.h"
#include "MyCameraMgr.h"
#include "MyKeyMgr.h"
#include "MyLevelMgr.h"
#include "MyLevel.h"
#include "MyPlayer.h"
#include "MyShadow.h"
#include "MyTears.h"
#include "MyEffect.h"
#include "MyRoom.h"
#include "components.h"

MyDoor::MyDoor()
	: m_Atlas(nullptr)
	, m_OutAnimator(nullptr)
	, m_InAnimator(nullptr)
	, m_OpenCollider(nullptr)
	, m_CloseCollider(nullptr)
	, UpDoorColOpen(false)
	, DownDoorColOpen(false)
	, LeftDoorColOpen(false)
	, RightDoorColOpen(false)
	, m_OwnerRoom(nullptr)
	, m_Effect(nullptr)
	, m_DoorDir(0)
{
	m_Atlas = MyAssetMgr::GetInst()->LoadTexture(L"Door", L"texture\\Grid\\door_01_normaldoor.png");

	// 애니메이션
	m_OutAnimator = AddComponent<MyAnimator>(L"OutDoorAnimator");
	m_OutAnimator->LoadAnimation(L"animdata\\UpOutDoorAnim.txt");
	m_OutAnimator->LoadAnimation(L"animdata\\DownOutDoorAnim.txt");
	m_OutAnimator->LoadAnimation(L"animdata\\LeftOutDoorAnim.txt");
	m_OutAnimator->LoadAnimation(L"animdata\\RightOutDoorAnim.txt");
	
	m_InAnimator = AddComponent<MyAnimator>(L"InDoorAnimator");
	m_InAnimator->LoadAnimation(L"animdata\\UpInDoorIdleAnim.txt");
	m_InAnimator->LoadAnimation(L"animdata\\UpInDoorOpenAnim.txt");
	m_InAnimator->LoadAnimation(L"animdata\\UpInDoorCloseAnim.txt");
	m_InAnimator->LoadAnimation(L"animdata\\DownInDoorIdleAnim.txt");
	m_InAnimator->LoadAnimation(L"animdata\\DownInDoorOpenAnim.txt");
	m_InAnimator->LoadAnimation(L"animdata\\DownInDoorCloseAnim.txt");
	m_InAnimator->LoadAnimation(L"animdata\\LeftInDoorIdleAnim.txt");
	m_InAnimator->LoadAnimation(L"animdata\\LeftInDoorOpenAnim.txt");
	m_InAnimator->LoadAnimation(L"animdata\\LeftInDoorCloseAnim.txt");
	m_InAnimator->LoadAnimation(L"animdata\\RightInDoorIdleAnim.txt");
	m_InAnimator->LoadAnimation(L"animdata\\RightInDoorOpenAnim.txt");
	m_InAnimator->LoadAnimation(L"animdata\\RightInDoorCloseAnim.txt");
}

MyDoor::MyDoor(MyRoom* _Owner)
	: m_Atlas(nullptr)
	, m_OutAnimator(nullptr)
	, m_InAnimator(nullptr)
	, m_OpenCollider(nullptr)
	, m_CloseCollider(nullptr)
	, UpDoorColOpen(false)
	, DownDoorColOpen(false)
	, LeftDoorColOpen(false)
	, RightDoorColOpen(false)
	, m_Effect(nullptr)
	, m_OwnerRoom(_Owner)
	, m_DoorDir(0)
{
	m_Atlas = MyAssetMgr::GetInst()->LoadTexture(L"Door", L"texture\\Grid\\door_01_normaldoor.png");

	// 애니메이션
	m_OutAnimator = AddComponent<MyAnimator>(L"OutDoorAnimator");
	m_OutAnimator->LoadAnimation(L"animdata\\UpOutDoorAnim.txt");
	m_OutAnimator->LoadAnimation(L"animdata\\DownOutDoorAnim.txt");
	m_OutAnimator->LoadAnimation(L"animdata\\LeftOutDoorAnim.txt");
	m_OutAnimator->LoadAnimation(L"animdata\\RightOutDoorAnim.txt");

	m_InAnimator = AddComponent<MyAnimator>(L"InDoorAnimator");
	m_InAnimator->LoadAnimation(L"animdata\\UpInDoorIdleAnim.txt");
	m_InAnimator->LoadAnimation(L"animdata\\UpInDoorOpenAnim.txt");
	m_InAnimator->LoadAnimation(L"animdata\\UpInDoorCloseAnim.txt");
	m_InAnimator->LoadAnimation(L"animdata\\DownInDoorIdleAnim.txt");
	m_InAnimator->LoadAnimation(L"animdata\\DownInDoorOpenAnim.txt");
	m_InAnimator->LoadAnimation(L"animdata\\DownInDoorCloseAnim.txt");
	m_InAnimator->LoadAnimation(L"animdata\\LeftInDoorIdleAnim.txt");
	m_InAnimator->LoadAnimation(L"animdata\\LeftInDoorOpenAnim.txt");
	m_InAnimator->LoadAnimation(L"animdata\\LeftInDoorCloseAnim.txt");
	m_InAnimator->LoadAnimation(L"animdata\\RightInDoorIdleAnim.txt");
	m_InAnimator->LoadAnimation(L"animdata\\RightInDoorOpenAnim.txt");
	m_InAnimator->LoadAnimation(L"animdata\\RightInDoorCloseAnim.txt");
}

MyDoor::~MyDoor()
{
}

void MyDoor::begin()
{
	Vec2 OwnerRoomPos = m_OwnerRoom->GetPos();

	if (m_OwnerRoom->GetUpDoorColOpen() && m_DoorDir == (int)DOOR_DIR::UP && m_OwnerRoom->IsRoomOpen())
	{
		m_OutAnimator->Play(L"UpOutDoorAnim", true);

		m_CloseCollider = AddComponent<MyCollider>(L"CloseUpDoorCollider");
		m_OpenCollider = AddComponent<MyCollider>(L"OpenUpDoorCollider");

		m_CloseCollider->SetScale(Vec2(80.f, 120.f));
		m_CloseCollider->SetOffsetPos(Vec2(OwnerRoomPos.x + 480.f, OwnerRoomPos.y + 50.f));

		m_OpenCollider->SetScale(Vec2(80.f, 80.f));
		m_OpenCollider->SetOffsetPos(Vec2(OwnerRoomPos.x + 480.f, OwnerRoomPos.y + 60.f));

		m_InAnimator->Play(L"UpInDoorOpenAnim", false);
	}
	else if (m_OwnerRoom->GetUpDoorColOpen() && m_DoorDir == (int)DOOR_DIR::UP && !m_OwnerRoom->IsRoomOpen())
	{
		m_OutAnimator->Play(L"UpOutDoorAnim", true);

		m_CloseCollider = AddComponent<MyCollider>(L"CloseUpDoorCollider");
		m_OpenCollider = AddComponent<MyCollider>(L"OpenUpDoorCollider");

		m_CloseCollider->SetScale(Vec2(80.f, 120.f));
		m_CloseCollider->SetOffsetPos(Vec2(OwnerRoomPos.x + 480.f, OwnerRoomPos.y + 50.f));

		m_OpenCollider->SetScale(Vec2(80.f, 80.f));
		m_OpenCollider->SetOffsetPos(Vec2(OwnerRoomPos.x + 480.f, OwnerRoomPos.y + 60.f));

		m_InAnimator->Play(L"UpInDoorCloseAnim", false);
	}

	if (m_OwnerRoom->GetDownDoorColOpen() && m_DoorDir == (int)DOOR_DIR::DOWN && m_OwnerRoom->IsRoomOpen())
	{
		m_OutAnimator->Play(L"DownOutDoorAnim", true);

		m_CloseCollider = AddComponent<MyCollider>(L"CloseDownDoorCollider");
		m_OpenCollider = AddComponent<MyCollider>(L"OpenDownDoorCollider");

		m_CloseCollider->SetScale(Vec2(80.f, 120.f));
		m_CloseCollider->SetOffsetPos(Vec2(OwnerRoomPos.x + 480.f, OwnerRoomPos.y + 585.f));

		m_OpenCollider->SetScale(Vec2(80.f, 80.f));
		m_OpenCollider->SetOffsetPos(Vec2(OwnerRoomPos.x + 480.f, OwnerRoomPos.y + 585.f));

		m_InAnimator->Play(L"DownInDoorOpenAnim", false);
	}
	else if (m_OwnerRoom->GetDownDoorColOpen() && m_DoorDir == (int)DOOR_DIR::DOWN && !m_OwnerRoom->IsRoomOpen())
	{
		m_OutAnimator->Play(L"DownOutDoorAnim", true);

		m_CloseCollider = AddComponent<MyCollider>(L"CloseDownDoorCollider");
		m_OpenCollider = AddComponent<MyCollider>(L"OpenDownDoorCollider");

		m_CloseCollider->SetScale(Vec2(80.f, 120.f));
		m_CloseCollider->SetOffsetPos(Vec2(OwnerRoomPos.x + 480.f, OwnerRoomPos.y + 585.f));

		m_OpenCollider->SetScale(Vec2(80.f, 80.f));
		m_OpenCollider->SetOffsetPos(Vec2(OwnerRoomPos.x + 480.f, OwnerRoomPos.y + 585.f));

		m_InAnimator->Play(L"DownInDoorCloseAnim", false);
	}

	if (m_OwnerRoom->GetLeftDoorColOpen() && m_DoorDir == (int)DOOR_DIR::LEFT && m_OwnerRoom->IsRoomOpen())
	{
		m_OutAnimator->Play(L"LeftOutDoorAnim", true);

		m_CloseCollider = AddComponent<MyCollider>(L"CloseLeftDoorCollider");
		m_OpenCollider = AddComponent<MyCollider>(L"OpenLeftDoorCollider");

		m_CloseCollider->SetScale(Vec2(100.f, 80.f));
		m_CloseCollider->SetOffsetPos(Vec2(OwnerRoomPos.x + 65.f, OwnerRoomPos.y + 320.f));

		m_OpenCollider->SetScale(Vec2(80.f, 80.f));
		m_OpenCollider->SetOffsetPos(Vec2(OwnerRoomPos.x + 55.f, OwnerRoomPos.y + 320.f));

		m_InAnimator->Play(L"LeftInDoorOpenAnim", false);
	}
	else if(m_OwnerRoom->GetLeftDoorColOpen() && m_DoorDir == (int)DOOR_DIR::LEFT && !m_OwnerRoom->IsRoomOpen())
	{
		m_OutAnimator->Play(L"LeftOutDoorAnim", true);

		m_CloseCollider = AddComponent<MyCollider>(L"CloseLeftDoorCollider");
		m_OpenCollider = AddComponent<MyCollider>(L"OpenLeftDoorCollider");

		m_CloseCollider->SetScale(Vec2(100.f, 80.f));
		m_CloseCollider->SetOffsetPos(Vec2(OwnerRoomPos.x + 65.f, OwnerRoomPos.y + 320.f));

		m_OpenCollider->SetScale(Vec2(80.f, 80.f));
		m_OpenCollider->SetOffsetPos(Vec2(OwnerRoomPos.x + 55.f, OwnerRoomPos.y + 320.f));

		m_InAnimator->Play(L"LeftInDoorCloseAnim", false);
	}

	if (m_OwnerRoom->GetRightDoorColOpen() && m_DoorDir == (int)DOOR_DIR::RIGHT && m_OwnerRoom->IsRoomOpen())
	{
		m_OutAnimator->Play(L"RightOutDoorAnim", true);

		m_CloseCollider = AddComponent<MyCollider>(L"CloseRightDoorCollider");
		m_OpenCollider = AddComponent<MyCollider>(L"OpenRightDoorCollider");

		m_CloseCollider->SetScale(Vec2(100.f, 80.f));
		m_CloseCollider->SetOffsetPos(Vec2(OwnerRoomPos.x + 895.f, OwnerRoomPos.y + 320.f));

		m_OpenCollider->SetScale(Vec2(80.f, 80.f));
		m_OpenCollider->SetOffsetPos(Vec2(OwnerRoomPos.x + 905.f, OwnerRoomPos.y + 320.f));

		m_InAnimator->Play(L"RightInDoorOpenAnim", false);
	}
	else if (m_OwnerRoom->GetRightDoorColOpen() && m_DoorDir == (int)DOOR_DIR::RIGHT && !m_OwnerRoom->IsRoomOpen())
	{
		m_OutAnimator->Play(L"RightOutDoorAnim", true);

		m_CloseCollider = AddComponent<MyCollider>(L"CloseRightDoorCollider");
		m_OpenCollider = AddComponent<MyCollider>(L"OpenRightDoorCollider");

		m_CloseCollider->SetScale(Vec2(100.f, 80.f));
		m_CloseCollider->SetOffsetPos(Vec2(OwnerRoomPos.x + 895.f, OwnerRoomPos.y + 320.f));

		m_OpenCollider->SetScale(Vec2(80.f, 80.f));
		m_OpenCollider->SetOffsetPos(Vec2(OwnerRoomPos.x + 905.f, OwnerRoomPos.y + 320.f));

		m_InAnimator->Play(L"RightInDoorCloseAnim", false);
	}
}

void MyDoor::tick(float _DT)
{
	Super::tick(_DT);

	if (!(m_OwnerRoom->IsRoomOpen()))
	{
		if (m_OwnerRoom->GetUpDoorColOpen() && m_DoorDir == (int)DOOR_DIR::UP)
		{
			if (m_InAnimator->m_CurAnim->IsFinish())
			{
				m_InAnimator->Play(L"UpInDoorCloseAnim", false);
				m_InAnimator->FindAnim(L"UpInDoorOpenAnim")->Reset();
			}
		}
		if (m_OwnerRoom->GetDownDoorColOpen() && m_DoorDir == (int)DOOR_DIR::DOWN)
		{
			m_InAnimator->Play(L"DownInDoorCloseAnim", false);
			m_InAnimator->FindAnim(L"DownInDoorOpenAnim")->Reset();
		}
		if (m_OwnerRoom->GetLeftDoorColOpen() && m_DoorDir == (int)DOOR_DIR::LEFT)
		{
			m_InAnimator->Play(L"LeftInDoorCloseAnim", false);
			m_InAnimator->FindAnim(L"LeftInDoorOpenAnim")->Reset();
		}
		if (m_OwnerRoom->GetRightDoorColOpen() && m_DoorDir == (int)DOOR_DIR::RIGHT)
		{
			m_InAnimator->Play(L"RightInDoorCloseAnim", false);
			m_InAnimator->FindAnim(L"RightInDoorOpenAnim")->Reset();
		}
	}
	else if(m_OwnerRoom->IsRoomOpen())
	{
		if (m_OwnerRoom->GetUpDoorColOpen() && m_DoorDir == (int)DOOR_DIR::UP)
		{
			m_InAnimator->Play(L"UpInDoorOpenAnim", false);
			m_InAnimator->FindAnim(L"UpInDoorCloseAnim")->Reset();
		}
		if (m_OwnerRoom->GetDownDoorColOpen() && m_DoorDir == (int)DOOR_DIR::DOWN)
		{
			m_InAnimator->Play(L"DownInDoorOpenAnim", false);
			m_InAnimator->FindAnim(L"DownInDoorCloseAnim")->Reset();
		}
		if (m_OwnerRoom->GetLeftDoorColOpen() && m_DoorDir == (int)DOOR_DIR::LEFT)
		{
			m_InAnimator->Play(L"LeftInDoorOpenAnim", false);
			m_InAnimator->FindAnim(L"LeftInDoorCloseAnim")->Reset();
		}
		if (m_OwnerRoom->GetRightDoorColOpen() && m_DoorDir == (int)DOOR_DIR::RIGHT)
		{
			m_InAnimator->Play(L"RightInDoorOpenAnim", false);
			m_InAnimator->FindAnim(L"RightInDoorCloseAnim")->Reset();
		}
	}
}

void MyDoor::BeginOverlap(MyCollider* _OwnCol, MyObject* _OtherObj, MyCollider* _OtherCol)
{
	if (true == m_OwnerRoom->IsRoomOpen())
	{
		wstring Objstr = _OtherObj->GetName();
		wstring Colstr = _OwnCol->GetName();

		// 문과 플레이어 충돌
		if (Colstr == L"OpenUpDoorCollider" && Objstr == L"PlayerShadow")
		{
			MyCameraMgr::GetInst()->MoveUpCamera(0.6f);

			MyPlayer* pPlayer = dynamic_cast<MyPlayer*>(MyLevelMgr::GetInst()->GetCurLevel()->FindObjectByName(L"Player"));
			pPlayer->GetComponent<MyMovement>()->SetVelocity(Vec2(0.f, 0.f));
			Vec2 PlayerPos = pPlayer->GetPos();
			_OtherObj = pPlayer;
			
			_OtherObj->SetPos(Vec2(PlayerPos.x, PlayerPos.y - 238.f));

			if (m_OwnerRoom->GetRoomType() == ROOM_TYPE::START) {
				auto objects = MyLevelMgr::GetInst()->GetCurLevel()->GetLayer((UINT)LAYER::ROOM)->GetObjects();
				dynamic_cast<MyRoom*>(objects[(UINT)ROOM_TYPE::NORMAL2])->SetMonPos();
			}
		}

		else if (Colstr == L"OpenDownDoorCollider" && Objstr == L"PlayerShadow")
		{
			MyCameraMgr::GetInst()->MoveDownCamera(0.6f);

			MyPlayer* pPlayer = dynamic_cast<MyPlayer*>(MyLevelMgr::GetInst()->GetCurLevel()->FindObjectByName(L"Player"));
			pPlayer->GetComponent<MyMovement>()->SetVelocity(Vec2(0.f, 0.f));
			Vec2 PlayerPos = pPlayer->GetPos();
			_OtherObj = pPlayer;

			_OtherObj->SetPos(Vec2(PlayerPos.x, PlayerPos.y + 238.f));
		}

		else if (Colstr == L"OpenLeftDoorCollider" && Objstr == L"PlayerShadow")
		{
			MyCameraMgr::GetInst()->MoveLeftCamera(0.6f);

			MyPlayer* pPlayer = dynamic_cast<MyPlayer*>(MyLevelMgr::GetInst()->GetCurLevel()->FindObjectByName(L"Player"));
			pPlayer->GetComponent<MyMovement>()->SetVelocity(Vec2(0.f, 0.f));
			Vec2 PlayerPos = pPlayer->GetPos();
			_OtherObj = pPlayer;

			_OtherObj->SetPos(Vec2(PlayerPos.x - 252.f, PlayerPos.y));

			if (m_OwnerRoom->GetRoomType() == ROOM_TYPE::START) {
				auto objects = MyLevelMgr::GetInst()->GetCurLevel()->GetLayer((UINT)LAYER::ROOM)->GetObjects();
				dynamic_cast<MyRoom*>(objects[(UINT)ROOM_TYPE::NORMAL])->SetMonPos();
			}
		}

		else if (Colstr == L"OpenRightDoorCollider" && Objstr == L"PlayerShadow")
		{
			MyCameraMgr::GetInst()->MoveRightCamera(0.6f);

			MyPlayer* pPlayer = dynamic_cast<MyPlayer*>(MyLevelMgr::GetInst()->GetCurLevel()->FindObjectByName(L"Player"));
			pPlayer->GetComponent<MyMovement>()->SetVelocity(Vec2(0.f, 0.f));
			Vec2 PlayerPos = pPlayer->GetPos();
			_OtherObj = pPlayer;

			_OtherObj->SetPos(Vec2(PlayerPos.x + 252.f, PlayerPos.y));

			/*if (m_OwnerRoom->GetRoomType() == ROOM_TYPE::NORMAL2) {
				auto objects = MyLevelMgr::GetInst()->GetCurLevel()->GetLayer((UINT)LAYER::ROOM)->GetObjects();
				dynamic_cast<MyRoom*>(objects[(UINT)ROOM_TYPE::BOSS])->PlayBossAnimation();
			}*/
		}

		// 문과 눈물 충돌
		if (Objstr == L"TearsShadow" && 
			((Colstr == L"OpenUpDoorCollider" || Colstr == L"OpenDownDoorCollider" || Colstr == L"OpenLeftDoorCollider"|| Colstr == L"OpenRightDoorCollider")))
		{
			MyShadow* pShadow = dynamic_cast<MyShadow*>(_OtherObj);
			MyTears* pTears = pShadow->GetOwnerTears();
			Vec2 vPos = pTears->GetPos();
			pTears->Destroy();
			_OtherObj->Destroy();

			m_Effect = new MyEffect;
			m_Effect->SetName(L"TearsDestroyAnimation");
			m_Effect->SetPos(vPos);
			m_Effect->SetScale(Vec2(1.f, 1.f));
			MyTaskMgr::GetInst()->AddTask(FTask{ TASK_TYPE::CREATE_OBJECT, (UINT_PTR)LAYER::EFFECT, (UINT_PTR)m_Effect });
		}
	}
	else
	{
		wstring Objstr = _OtherObj->GetName();
		wstring Colstr = _OwnCol->GetName();

		// 문과 눈물 충돌
		if (Objstr == L"TearsShadow" &&
			((Colstr == L"CloseUpDoorCollider" || Colstr == L"CloseDownDoorCollider" || Colstr == L"CloseLeftDoorCollider" || Colstr == L"CloseRightDoorCollider")))
		{
			MyShadow* pShadow = dynamic_cast<MyShadow*>(_OtherObj);
			MyTears* pTears = pShadow->GetOwnerTears();
			Vec2 vPos = pTears->GetPos();
			pTears->Destroy();
			_OtherObj->Destroy();

			m_Effect = new MyEffect;
			m_Effect->SetName(L"TearsDestroyAnimation");
			m_Effect->SetPos(vPos);
			m_Effect->SetScale(Vec2(1.f, 1.f));
			MyTaskMgr::GetInst()->AddTask(FTask{ TASK_TYPE::CREATE_OBJECT, (UINT_PTR)LAYER::EFFECT, (UINT_PTR)m_Effect });
		}
	}
}

void MyDoor::Overlap(MyCollider* _OwnCol, MyObject* _OtherObj, MyCollider* _OtherCol)
{
	if (!(m_OwnerRoom->IsRoomOpen()))
	{
		wstring Objstr = _OtherObj->GetName();

		Vec2 vOwnScale = _OwnCol->GetOffsetScale();
		Vec2 vOwnPos = _OwnCol->GetFinalPos();
		Vec2 vOtherScale = _OtherCol->GetOffsetScale();
		Vec2 vOtherPos = _OtherCol->GetFinalPos();

		float vDiffPosX = vOwnPos.x - vOtherPos.x;
		float vDiffPosY = vOwnPos.y - vOtherPos.y;
		float MoveX = vOtherScale.x - vDiffPosX;
		float MoveY = vOtherScale.y - vDiffPosY;

		wstring Colstr = _OwnCol->GetName();

		if (Colstr == L"CloseUpDoorCollider" && Objstr == L"PlayerShadow")
		{
			MyPlayer* pPlayer = dynamic_cast<MyPlayer*>(MyLevelMgr::GetInst()->GetCurLevel()->FindObjectByName(L"Player"));
			_OtherObj = pPlayer;
			_OtherObj->SetPos(Vec2(_OtherObj->GetPos().x, _OtherObj->GetPos().y + abs(MoveY * 0.03f)));
		}

		if (Colstr == L"CloseDownDoorCollider" && Objstr == L"PlayerShadow")
		{
			MyPlayer* pPlayer = dynamic_cast<MyPlayer*>(MyLevelMgr::GetInst()->GetCurLevel()->FindObjectByName(L"Player"));
			_OtherObj = pPlayer;
			_OtherObj->SetPos(Vec2(_OtherObj->GetPos().x, _OtherObj->GetPos().y - abs(MoveY * 0.03f)));
		}

		if (Colstr == L"CloseLeftDoorCollider" && Objstr == L"PlayerShadow")
		{
			MyPlayer* pPlayer = dynamic_cast<MyPlayer*>(MyLevelMgr::GetInst()->GetCurLevel()->FindObjectByName(L"Player"));
			_OtherObj = pPlayer;
			_OtherObj->SetPos(Vec2(_OtherObj->GetPos().x + abs(MoveX * 0.01f), _OtherObj->GetPos().y));
		}

		if (Colstr == L"CloseRightDoorCollider" && Objstr == L"PlayerShadow")
		{
			MyPlayer* pPlayer = dynamic_cast<MyPlayer*>(MyLevelMgr::GetInst()->GetCurLevel()->FindObjectByName(L"Player"));
			_OtherObj = pPlayer;
			_OtherObj->SetPos(Vec2(_OtherObj->GetPos().x - abs(MoveX * 0.05f), _OtherObj->GetPos().y));
		}
	}

}