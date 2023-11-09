#include "pch.h"
#include "MyRoom.h"

#include "MyAssetMgr.h"
#include "MyTexture.h"
#include "components.h"

MyRoom::MyRoom()
	: m_MonsterCount(0)
	, m_isOpen(true)
	, m_IsBoss(false)
	, m_StartImg(nullptr)
	, m_NormalImg(nullptr)
	, m_TreasureImg(nullptr)
	, m_BossImg(nullptr)
	, m_CurImg(nullptr)
	, m_Collider(nullptr)
{
	m_StartImg = MyAssetMgr::GetInst()->LoadTexture(L"StartRoom", L"texture\\Room\\Basement_0.png");
	m_NormalImg = MyAssetMgr::GetInst()->LoadTexture(L"NormalRoom", L"texture\\Room\\Basement_1.png");
	m_TreasureImg = MyAssetMgr::GetInst()->LoadTexture(L"TreasureRoom", L"texture\\Room\\Basement_3.png");
	m_BossImg = MyAssetMgr::GetInst()->LoadTexture(L"BossRoom", L"texture\\Room\\Basement_4.png");

	m_Collider = AddComponent<MyCollider>(L"RoomColliderUp");
	m_Collider->SetScale(Vec2(730.f, 50.f));
	m_Collider->SetOffsetPos(Vec2(480.f, 90.f));

	m_Collider = AddComponent<MyCollider>(L"RoomColliderDown");
	m_Collider->SetScale(Vec2(730.f, 50.f));
	m_Collider->SetOffsetPos(Vec2(480.f, 550.f));

	m_Collider = AddComponent<MyCollider>(L"RoomColliderLeft");
	m_Collider->SetScale(Vec2(50.f, 410.f));
	m_Collider->SetOffsetPos(Vec2(90.f, 320.f));

	m_Collider = AddComponent<MyCollider>(L"RoomColliderRight");
	m_Collider->SetScale(Vec2(50.f, 410.f));
	m_Collider->SetOffsetPos(Vec2(870.f, 320.f));
}

MyRoom::MyRoom(const MyRoom& _Origin)
	: MyObject(_Origin)
	, m_MonsterCount(_Origin.m_MonsterCount)
	, m_isOpen(_Origin.m_isOpen)
	, m_IsBoss(_Origin.m_IsBoss)
	, m_StartImg(_Origin.m_StartImg)
	, m_NormalImg(_Origin.m_NormalImg)
	, m_TreasureImg(_Origin.m_TreasureImg)
	, m_BossImg(_Origin.m_BossImg)
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
	if (nullptr == m_CurImg)
	{
		m_CurImg = m_StartImg;
	}

	m_CurImg = GetCurImg();
}

void MyRoom::tick(float _DT)
{
	Super::tick(_DT);


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

void MyRoom::Overlap(MyCollider* _OwnCol, MyObject* _OtherObj, MyCollider* _OtherCol)
{
	Vec2 vOwnScale = _OwnCol->GetOffsetScale();
	Vec2 vOwnPos = _OwnCol->GetFinalPos();
	Vec2 vOtherScale = _OtherCol->GetOffsetScale();
	Vec2 vOtherPos = _OtherCol->GetFinalPos();
	
	float vDiffPosX = vOwnPos.x - vOtherPos.x;
	float vDiffPosY = vOwnPos.y - vOtherPos.y;
	float MoveX = vOtherScale.x - vDiffPosX;
	float MoveY = vOtherScale.y - vDiffPosY;

	wstring str = _OwnCol->GetName();

	if (str == L"RoomColliderUp")
	{
		_OtherObj->SetPos(Vec2(_OtherObj->GetPos().x, _OtherObj->GetPos().y + MoveY / 70.f));
	}

	if (str == L"RoomColliderDown")
	{
		_OtherObj->SetPos(Vec2(_OtherObj->GetPos().x, _OtherObj->GetPos().y - MoveY / 15.f));
	}

	if (str == L"RoomColliderLeft")
	{
		_OtherObj->SetPos(Vec2(_OtherObj->GetPos().x + abs(MoveX / 40.f), _OtherObj->GetPos().y));
	}
	
	if (str == L"RoomColliderRight")
	{
		_OtherObj->SetPos(Vec2(_OtherObj->GetPos().x - abs(MoveX / 2.f), _OtherObj->GetPos().y));
	}	
}
