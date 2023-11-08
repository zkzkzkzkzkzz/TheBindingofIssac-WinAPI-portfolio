#include "pch.h"
#include "MyPlayLevel.h"

#include "MyEngine.h"

#include "MyAssetMgr.h"
#include "MyKeyMgr.h"
#include "MyLevelMgr.h"
#include "MyCameraMgr.h"

#include "MyObject.h"
#include "MyPlayer.h"
#include "NormalFly.h"
#include "MyRoom.h"
#include "MyBackGround.h"
#include "MyTexture.h"

#include "components.h"

void MyPlayLevel::init()
{
	// 시작 방
	MyRoom* pRoom = new MyRoom;
	pRoom->SetPos(Vec2(0.f, 0.f));
	pRoom->SetScale(Vec2(2.f, 2.f));
	AddObject(LAYER::ROOM, pRoom);

	// 왼쪽 방
	pRoom = pRoom->Clone();
	pRoom->SetRoomImg(pRoom->GetNormalImg());
	pRoom->SetPos(Vec2(-960.f, 0.f));
	AddObject(LAYER::ROOM, pRoom);

	// 오른쪽 방
	pRoom = pRoom->Clone();
	pRoom->SetRoomImg(pRoom->GetNormalImg());
	pRoom->SetPos(Vec2(960.f, 0.f));
	AddObject(LAYER::ROOM, pRoom);

	// 위쪽 방
	pRoom = pRoom->Clone();
	pRoom->SetRoomImg(pRoom->GetNormalImg());
	pRoom->SetPos(Vec2(0.f, -640.f));
	AddObject(LAYER::ROOM, pRoom);

	// 아래쪽 방
	pRoom = pRoom->Clone();
	pRoom->SetRoomImg(pRoom->GetNormalImg());
	pRoom->SetPos(Vec2(0.f, 640.f));
	AddObject(LAYER::ROOM, pRoom);

	// 플레이어 생성
	MyPlayer* pPlayer = new MyPlayer;
	pPlayer->SetPos(Vec2(480.f, 320.f));
	pPlayer->SetScale(Vec2(1.f, 1.f)); 
	AddObject(LAYER::PLAYER, pPlayer);

	// 일반 파리 몬스터 생성
	NormalFly* pFly = new NormalFly;
	pFly->SetPos(Vec2(100.f, 100.f));
	pFly->SetScale(Vec2(2.f, 2.f));
	AddObject(LAYER::MONSTER, pFly);
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
