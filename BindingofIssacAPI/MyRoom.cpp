#include "pch.h"
#include "MyRoom.h"
#include "MyAssetMgr.h"
#include "MyCameraMgr.h"
#include "MyKeyMgr.h"
#include "MyLevelMgr.h"
#include "MyPlayLevel.h"
#include "MyLevel.h"
#include "MyPlayer.h"
#include "MyMonster.h"
#include "NormalFly.h"
#include "MyTears.h"
#include "MyDoor.h"
#include "MyShadow.h"
#include "MyEffect.h"
#include "MyScene.h"
#include "MyTexture.h"
#include "components.h"


MyRoom::MyRoom()
	: m_isOpen(true)
	, m_IsBoss(false)
	, m_StartImg(nullptr)
	, m_NormalImg(nullptr)
	, m_TreasureImg(nullptr)
	, m_BossImg(nullptr)
	, m_CurImg(nullptr)
	, m_Collider(nullptr)
	, m_Effect(nullptr)
	, m_CurRoomType(ROOM_TYPE::START)
	, UpDoorColOpen(false)
	, DownDoorColOpen(false)
	, LeftDoorColOpen(false)
	, RightDoorColOpen(false)
	, m_RoomClear(false)
	, m_MonsterCount(0)
{
	m_StartImg = MyAssetMgr::GetInst()->LoadTexture(L"StartRoom", L"texture\\Room\\Basement_0.png");
	m_NormalImg = MyAssetMgr::GetInst()->LoadTexture(L"NormalRoom", L"texture\\Room\\Basement_1.png");
	m_TreasureImg = MyAssetMgr::GetInst()->LoadTexture(L"TreasureRoom", L"texture\\Room\\Basement_3.png");
	m_BossImg = MyAssetMgr::GetInst()->LoadTexture(L"BossRoom", L"texture\\Room\\Basement_4.png");
}

MyRoom::MyRoom(const MyRoom& _Origin)
	: MyObject(_Origin)
	, m_isOpen(_Origin.m_isOpen)
	, m_IsBoss(_Origin.m_IsBoss)
	, m_RoomClear(_Origin.m_RoomClear)
	, m_StartImg(_Origin.m_StartImg)
	, m_NormalImg(_Origin.m_NormalImg)
	, m_TreasureImg(_Origin.m_TreasureImg)
	, m_BossImg(_Origin.m_BossImg)
	, m_Effect(nullptr)
	, m_CurImg(nullptr)
	, m_Collider(nullptr)
{
	m_CurImg = GetCurImg();
	m_Collider = GetComponent<MyCollider>();
}

MyRoom::~MyRoom()
{

}

void MyRoom::begin()
{
	Vec2 OwnerRoomPos = GetPos();

	if (nullptr == m_CurImg)
	{
		m_CurImg = m_StartImg;
	}

	m_CurImg = GetCurImg();

	if ((int)m_CurRoomType != 0)
	{
		m_CurRoomType = ROOM_TYPE::START;
	}

	if (true == UpDoorColOpen)
	{
		m_Collider = AddComponent<MyCollider>(L"RoomColliderUp1");
		m_Collider->SetScale(Vec2(425.f, 100.f));
		m_Collider->SetOffsetPos(Vec2(240.f, 60.f));

		m_Collider = AddComponent<MyCollider>(L"RoomColliderUp2");
		m_Collider->SetScale(Vec2(425.f, 100.f));
		m_Collider->SetOffsetPos(Vec2(720.f, 60.f));

		MyDoor* pDoor = new MyDoor(this);
		pDoor->SetScale(Vec2(2.f, 2.f));
		pDoor->SetOffsetPos(Vec2(OwnerRoomPos.x + 446.f, OwnerRoomPos.y + 64.f));
		pDoor->SetDoorDir(DOOR_DIR::UP);
		m_vecDoor.push_back(pDoor);
		MyTaskMgr::GetInst()->AddTask(FTask{ TASK_TYPE::CREATE_OBJECT, (UINT_PTR)LAYER::DOOR, (UINT_PTR)pDoor });
	}
	else if (false == UpDoorColOpen)
	{
		m_Collider = AddComponent<MyCollider>(L"RoomColliderUp3");
		m_Collider->SetScale(Vec2(850.f, 100.f));
		m_Collider->SetOffsetPos(Vec2(480.f, 60.f));
	}

	if (true == DownDoorColOpen)
	{
		m_Collider = AddComponent<MyCollider>(L"RoomColliderDown1");
		m_Collider->SetScale(Vec2(425.f, 100.f));
		m_Collider->SetOffsetPos(Vec2(240.f, 575.f));

		m_Collider = AddComponent<MyCollider>(L"RoomColliderDown2");
		m_Collider->SetScale(Vec2(425.f, 100.f));
		m_Collider->SetOffsetPos(Vec2(720.f, 575.f));

		MyDoor* pDoor = new MyDoor(this);
		pDoor->SetScale(Vec2(2.f, 2.f));
		pDoor->SetOffsetPos(Vec2(OwnerRoomPos.x + 446.f, OwnerRoomPos.y + 543.f));
		pDoor->SetDoorDir(DOOR_DIR::DOWN);
		m_vecDoor.push_back(pDoor);
		MyTaskMgr::GetInst()->AddTask(FTask{ TASK_TYPE::CREATE_OBJECT, (UINT_PTR)LAYER::DOOR, (UINT_PTR)pDoor });
	}
	else if (false == DownDoorColOpen)
	{
		m_Collider = AddComponent<MyCollider>(L"RoomColliderDown3");
		m_Collider->SetScale(Vec2(850.f, 100.f));
		m_Collider->SetOffsetPos(Vec2(480.f, 575.f));
	}

	if (true == LeftDoorColOpen)
	{
		m_Collider = AddComponent<MyCollider>(L"RoomColliderLeft1");
		m_Collider->SetScale(Vec2(100.f, 290.f));
		m_Collider->SetOffsetPos(Vec2(65.f, 140.f));

		m_Collider = AddComponent<MyCollider>(L"RoomColliderLeft2");
		m_Collider->SetScale(Vec2(100.f, 290.f));
		m_Collider->SetOffsetPos(Vec2(65.f, 490.f));

		MyDoor* pDoor = new MyDoor(this);
		pDoor->SetScale(Vec2(2.f, 2.f));
		pDoor->SetOffsetPos(Vec2(OwnerRoomPos.x + 65.f, OwnerRoomPos.y + 285.f));
		pDoor->SetDoorDir(DOOR_DIR::LEFT);
		m_vecDoor.push_back(pDoor);
		MyTaskMgr::GetInst()->AddTask(FTask{ TASK_TYPE::CREATE_OBJECT, (UINT_PTR)LAYER::DOOR, (UINT_PTR)pDoor });
	}
	else if (false == LeftDoorColOpen)
	{
		m_Collider = AddComponent<MyCollider>(L"RoomColliderLeft3");
		m_Collider->SetScale(Vec2(100.f, 580.f));
		m_Collider->SetOffsetPos(Vec2(65.f, 300.f));
	}

	if (true == RightDoorColOpen)
	{
		m_Collider = AddComponent<MyCollider>(L"RoomColliderRight1");
		m_Collider->SetScale(Vec2(100.f, 290.f));
		m_Collider->SetOffsetPos(Vec2(895.f, 140.f));

		m_Collider = AddComponent<MyCollider>(L"RoomColliderRight2");
		m_Collider->SetScale(Vec2(100.f, 290.f));
		m_Collider->SetOffsetPos(Vec2(895.f, 490.f));

		MyDoor* pDoor = new MyDoor(this);
		pDoor->SetScale(Vec2(2.f, 2.f));
		pDoor->SetOffsetPos(Vec2(OwnerRoomPos.x + 842.f, OwnerRoomPos.y + 280.f));
		pDoor->SetDoorDir(DOOR_DIR::RIGHT);
		m_vecDoor.push_back(pDoor);
		MyTaskMgr::GetInst()->AddTask(FTask{ TASK_TYPE::CREATE_OBJECT, (UINT_PTR)LAYER::DOOR, (UINT_PTR)pDoor });
	}
	else if (false == RightDoorColOpen)
	{
		m_Collider = AddComponent<MyCollider>(L"RoomColliderRight3");
		m_Collider->SetScale(Vec2(100.f, 580.f));
		m_Collider->SetOffsetPos(Vec2(895.f, 300.f));
	}
}

void MyRoom::tick(float _DT)
{
	Super::tick(_DT);

	CheckMonsterCount();

	if (IsRoomOpen())
	{
		SetRoomOpen();
	}
	else
	{
		SetRoomClose();
	}

	Vec2 vPos = MyCameraMgr::GetInst()->GetInitPos();

	if ((vPos.x > 400.f && vPos.x < 500.f )&& (vPos.y > 300.f && vPos.y < 400.f))
	{
		m_CurRoomType = ROOM_TYPE::START;
	}
	else if ((vPos.x > -500.f && vPos.x < -400.f) && (vPos.y > 300.f && vPos.y < 400.f))
	{
		m_CurRoomType = ROOM_TYPE::NORMAL;
	}
	else if ((vPos.x > 400.f && vPos.x < 500.f) && (vPos.y > -400.f && vPos.y < -300.f))
	{
		m_CurRoomType = ROOM_TYPE::NORMAL2;
	}
	else if ((vPos.x > 1400.f && vPos.x < 1500.f) && (vPos.y > 300.f && vPos.y < 400.f))
	{
		m_CurRoomType = ROOM_TYPE::NORMAL3;
	}
	else if ((vPos.x > 1400.f && vPos.x < 1500.f) && (vPos.y > -400.f && vPos.y < -300.f))
	{
		m_CurRoomType = ROOM_TYPE::BOSS;
	}
}

void MyRoom::render(HDC _dc)
{
	Vec2 vRenderPos = GetRenderPos();
	Vec2 vScale = GetScale();

	BLENDFUNCTION blend = {};
	blend.BlendOp = AC_SRC_OVER;
	blend.BlendFlags = 0;

	blend.SourceConstantAlpha = 255; // 0 ~ 255
	blend.AlphaFormat = AC_SRC_ALPHA; // 0

	AlphaBlend(_dc
		, (int)vRenderPos.x, (int)vRenderPos.y
		, int(m_CurImg->GetWidth() * vScale.x)
		, int(m_CurImg->GetHeight() * vScale.y)
		, m_CurImg->GetDC()
		, 0, 0
		, m_CurImg->GetWidth()
		, m_CurImg->GetHeight()
		, blend);

	Super::render(_dc);
}

void MyRoom::BeginOverlap(MyCollider* _OwnCol, MyObject* _OtherObj, MyCollider* _OtherCol)
{
	wstring Objstr = _OtherObj->GetName();

	if (Objstr == L"TearsShadow")
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

void MyRoom::Overlap(MyCollider* _OwnCol, MyObject* _OtherObj, MyCollider* _OtherCol)
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

	if ((Colstr == L"RoomColliderUp1" || Colstr == L"RoomColliderUp2" || Colstr == L"RoomColliderUp3") && Objstr == L"PlayerShadow")
	{
		MyPlayer* pPlayer = dynamic_cast<MyPlayer*>(MyLevelMgr::GetInst()->GetCurLevel()->FindObjectByName(L"Player"));
		_OtherObj = pPlayer;
		_OtherObj->SetPos(Vec2(_OtherObj->GetPos().x, _OtherObj->GetPos().y + abs(MoveY * 0.03f)));
	}
	
	if ((Colstr == L"RoomColliderDown1" || Colstr == L"RoomColliderDown2" || Colstr == L"RoomColliderDown3") && Objstr == L"PlayerShadow")
	{
		MyPlayer* pPlayer = dynamic_cast<MyPlayer*>(MyLevelMgr::GetInst()->GetCurLevel()->FindObjectByName(L"Player"));
		_OtherObj = pPlayer;
		_OtherObj->SetPos(Vec2(_OtherObj->GetPos().x, _OtherObj->GetPos().y - abs(MoveY * 0.03f)));
	}

	if ((Colstr == L"RoomColliderLeft1" || Colstr == L"RoomColliderLeft2" || Colstr == L"RoomColliderLeft3") && Objstr == L"PlayerShadow")
	{
		MyPlayer* pPlayer = dynamic_cast<MyPlayer*>(MyLevelMgr::GetInst()->GetCurLevel()->FindObjectByName(L"Player"));
		_OtherObj = pPlayer;
		_OtherObj->SetPos(Vec2(_OtherObj->GetPos().x + abs(MoveX * 0.02f), _OtherObj->GetPos().y));
	}
	
	if ((Colstr == L"RoomColliderRight1" || Colstr == L"RoomColliderRight2" || Colstr == L"RoomColliderRight3") && Objstr == L"PlayerShadow")
	{
		MyPlayer* pPlayer = dynamic_cast<MyPlayer*>(MyLevelMgr::GetInst()->GetCurLevel()->FindObjectByName(L"Player"));
		_OtherObj = pPlayer;
		_OtherObj->SetPos(Vec2(_OtherObj->GetPos().x - abs(MoveX * 0.1f), _OtherObj->GetPos().y));
	}	
}

void MyRoom::SetMonPos()
{
	for (int i = 0; i < m_vecMons.size(); ++i) {
		if (!m_vecMons[i]->IsMonsterDead()) {
			m_vecMons[i]->SetActive(true);
			m_vecMons[i]->SetToInitPos();
		}
	}
}

void MyRoom::PlayBossAnimation()
{
	MyScene* pScene = new MyScene;
	pScene->SetPos(Vec2(960.f, -640.f));
	pScene->SetScale(Vec2(2.f, 2.f));
	pScene->SetOffsetPos(Vec2(250.f, 150.f));
	MyTaskMgr::GetInst()->AddTask(FTask{ TASK_TYPE::CREATE_OBJECT, (UINT_PTR)LAYER::EFFECT, (UINT_PTR)pScene });
}

void MyRoom::CheckMonsterCount()
{
	vector<MyMonster*>::iterator iter = m_vecMons.begin();

	for (; iter != m_vecMons.end();)
	{
		if ((*iter)->IsMonsterDead())
		{
			(*iter)->SetPos(Vec2(-100000.f, -100000.f));
			//(*iter)->SetActive(false);
			iter = m_vecMons.erase(iter);
		}
		else
		{
			++iter;
		}
	}

	if (0 == m_vecMons.size())
	{
		m_RoomClear = true;
		m_isOpen = true;
		return;
	}
	else
	{
		m_RoomClear = false;
		m_isOpen = false;
		return;
	}
}