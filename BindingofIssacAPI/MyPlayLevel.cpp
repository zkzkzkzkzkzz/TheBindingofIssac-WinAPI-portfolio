#include "pch.h"
#include "MyPlayLevel.h"

#include "MyEngine.h"

#include "MyAssetMgr.h"
#include "MyKeyMgr.h"
#include "MyLevelMgr.h"
#include "MyCameraMgr.h"
#include "MyCollisionMgr.h"

#include "MyObject.h"
#include "MyPlayer.h"
#include "MyShadow.h"
#include "MyDoor.h"
#include "NormalFly.h"
#include "Pooter.h"
#include "FloatingKnight.h"
#include "BossMonster.h"
#include "MyRoom.h"
#include "MyBackGround.h"
#include "MyTexture.h"
#include "components.h"

void MyPlayLevel::init()
{
	// 시작 방
	MyRoom* pRoom = new MyRoom;
	pRoom->SetName(L"StartRoom");
	pRoom->SetPos(Vec2(0.f, 0.f));
	pRoom->SetScale(Vec2(2.f, 2.f));
	pRoom->SetRoomType(ROOM_TYPE::START);
	pRoom->SetUpDoorColOpen(true);
	pRoom->SetDownDoorColOpen(false);
	pRoom->SetLeftDoorColOpen(true);
	pRoom->SetRightDoorColOpen(true);
	AddObject(LAYER::ROOM, pRoom);

	// 왼쪽 방
	MyRoom* pRoom2 = new MyRoom;
	pRoom2->SetRoomImg(pRoom2->GetNormalImg());
	pRoom2->SetName(L"NormalRoom");
	pRoom2->SetPos(Vec2(-960.f, 0.f));
	pRoom2->SetScale(Vec2(2.f, 2.f));
	pRoom2->SetRoomType(ROOM_TYPE::NORMAL);
	pRoom2->SetUpDoorColOpen(false);
	pRoom2->SetDownDoorColOpen(false);
	pRoom2->SetLeftDoorColOpen(false);
	pRoom2->SetRightDoorColOpen(true);
	AddObject(LAYER::ROOM, pRoom2);

	// 위쪽 방
	MyRoom* pRoom3 = new MyRoom;
	pRoom3->SetRoomImg(pRoom3->GetNormalImg());
	pRoom3->SetName(L"NormalRoom2");
	pRoom3->SetPos(Vec2(0.f, -640.f));
	pRoom3->SetScale(Vec2(2.f, 2.f));
	pRoom3->SetRoomType(ROOM_TYPE::NORMAL2);
	pRoom3->SetUpDoorColOpen(true);
	pRoom3->SetDownDoorColOpen(true);
	pRoom3->SetLeftDoorColOpen(false);
	pRoom3->SetRightDoorColOpen(false);
	AddObject(LAYER::ROOM, pRoom3);

	// 오른쪽 방
	MyRoom* pRoom4 = new MyRoom;
	pRoom4->SetRoomImg(pRoom4->GetNormalImg());
	pRoom4->SetName(L"NormalRoom3");
	pRoom4->SetPos(Vec2(960.f, 0.f));
	pRoom4->SetScale(Vec2(2.f, 2.f));
	pRoom4->SetRoomType(ROOM_TYPE::NORMAL2);
	pRoom4->SetUpDoorColOpen(true);
	pRoom4->SetDownDoorColOpen(false);
	pRoom4->SetLeftDoorColOpen(true);
	pRoom4->SetRightDoorColOpen(false);
	pRoom4->SetBossRoom();
	AddObject(LAYER::ROOM, pRoom4);

	// 보스 방
	MyRoom* pRoom5 = new MyRoom;
	pRoom5->SetRoomImg(pRoom5->GetBossImg());
	pRoom5->SetName(L"BossRoom");
	pRoom5->SetPos(Vec2(960.f, -640.f));
	pRoom5->SetScale(Vec2(2.f, 2.f));
	pRoom5->SetRoomType(ROOM_TYPE::BOSS);
	pRoom5->SetUpDoorColOpen(false);
	pRoom5->SetDownDoorColOpen(true);
	pRoom5->SetLeftDoorColOpen(false);
	pRoom5->SetRightDoorColOpen(false);
	pRoom5->SetBossRoom();
	AddObject(LAYER::ROOM, pRoom5);

	// 플레이어 생성
	MyPlayer* pPlayer = new MyPlayer;
	pPlayer->SetPos(Vec2(480.f, 320.f));
	pPlayer->SetScale(Vec2(1.f, 1.f)); 
	pPlayer->SetOffsetPos(Vec2(4.f, -36.f));
	AddObject(LAYER::PLAYER, pPlayer);

	// 일반 파리 몬스터 생성
	NormalFly* pFly = new NormalFly;
	pFly->SetPos(Vec2(-10000.f, -10000.f));
	pFly->SetInitPos(Vec2(-800.f, 200.f));
	pFly->SetScale(Vec2(2.f, 2.f));
	pFly->SetOffsetPos(Vec2(-15.f, -25.f));
	pRoom2->AddMonster(pFly);
	pFly->SetActive(false);
	AddObject(LAYER::MONSTER, pFly);

	// 푸터 생성
	Pooter* pPooter = new Pooter;
	pPooter->SetPos(Vec2(-10000.f, -10000.f));
	pPooter->SetInitPos(Vec2(-700.f, 300.f));
	pPooter->SetScale(Vec2(2.f, 2.f));
	pPooter->SetOffsetPos(Vec2(-18.f, -30.f));
	pPooter->SetActive(false);
	pRoom2->AddMonster(pPooter);
	AddObject(LAYER::MONSTER, pPooter);

	// 부유하는 나이트 생성
	FloatingKnight* pFK = new FloatingKnight;
	pFK->SetPos(Vec2(-10000.f, -10000.f));
	pFK->SetInitPos(Vec2(460.f, -450.f));
	pFK->SetScale(Vec2(2.f, 2.f));
	pFK->SetOffsetPos(Vec2(-15.f, -40.f));
	pFK->SetStartDir(FKDir::DOWN);
	pFK->SetActive(false);
	pRoom3->AddMonster(pFK);
	AddObject(LAYER::MONSTER, pFK);

	FloatingKnight* pFK2 = new FloatingKnight;
	pFK2->SetPos(Vec2(-10000.f, -10000.f));
	pFK2->SetInitPos(Vec2(200.f, -450.f));
	pFK2->SetScale(Vec2(2.f, 2.f));
	pFK2->SetOffsetPos(Vec2(-15.f, -40.f));
	pFK2->SetStartDir(FKDir::RIGHT);
	pFK2->SetActive(false);
	pRoom3->AddMonster(pFK2);
	AddObject(LAYER::MONSTER, pFK2);

	FloatingKnight* pFK3 = new FloatingKnight;
	pFK3->SetPos(Vec2(-10000.f, -10000.f));
	pFK3->SetInitPos(Vec2(600.f, -360.f));
	pFK3->SetScale(Vec2(2.f, 2.f));
	pFK3->SetOffsetPos(Vec2(-15.f, -40.f));
	pFK3->SetStartDir(FKDir::UP);
	pFK3->SetActive(false);
	pRoom3->AddMonster(pFK3);
	AddObject(LAYER::MONSTER, pFK3);

	BossMonster* pBoss = new BossMonster;
	pBoss->SetPos(Vec2(-10000.f, -10000.f));
	pBoss->SetInitPos(Vec2(1440.f, -400.f));
	pBoss->SetScale(Vec2(2.f, 2.f));
	pBoss->SetOffsetPos(Vec2(-15.f, -40.f));
	pBoss->SetActive(false);
	pRoom5->AddMonster(pBoss);
	AddObject(LAYER::BOSS, pBoss);

	// 충돌 설정
	MyCollisionMgr::GetInst()->CheckCollision(LAYER::PLAYER, LAYER::MONSTER);
	MyCollisionMgr::GetInst()->CheckCollision(LAYER::PLAYER, LAYER::MONSTEARS);
	MyCollisionMgr::GetInst()->CheckCollision(LAYER::SHADOW, LAYER::ROOM);
	MyCollisionMgr::GetInst()->CheckCollision(LAYER::SHADOW, LAYER::DOOR);
	MyCollisionMgr::GetInst()->CheckCollision(LAYER::SHADOW, LAYER::TEARS);
	MyCollisionMgr::GetInst()->CheckCollision(LAYER::MONSTER, LAYER::TEARS);
	MyCollisionMgr::GetInst()->CheckCollision(LAYER::BOSS, LAYER::TEARS);
	MyCollisionMgr::GetInst()->CheckCollision(LAYER::BOSS, LAYER::ROOM);
	MyCollisionMgr::GetInst()->CheckCollision(LAYER::BOSS, LAYER::DOOR);
	MyCollisionMgr::GetInst()->CheckCollision(LAYER::MONSTER, LAYER::ROOM);
	MyCollisionMgr::GetInst()->CheckCollision(LAYER::MONSTER, LAYER::DOOR);
}

void MyPlayLevel::enter()
{
	// 카메라 설정
	vLookAt = MyEngine::GetInst()->GetResolution();
	vLookAt /= 2.f;
	MyCameraMgr::GetInst()->SetLookAt(vLookAt);
}

void MyPlayLevel::exit()
{
	DeleteAllObjects();
}

void MyPlayLevel::tick()
{
	MyLevel::tick();
}
