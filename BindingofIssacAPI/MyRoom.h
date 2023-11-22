#pragma once
#include "MyObject.h"

class MyTexture;
class MyCollider;
class MyMonster;
class MyEffect;
class MyDoor;

enum class ROOM_TYPE
{
    START,
    NORMAL,
    NORMAL2,
    NORMAL3,
    BOSS,
    TREASURE,
    END,
};

class MyRoom :
    public MyObject
{
    GENERATED_OBJECT(MyObject);

private:
    MyCollider* m_Collider;

    ROOM_TYPE m_CurRoomType;
    
    vector<MyMonster*>  m_vecMons;
    int                 m_MonsterCount;
    bool                m_isOpen;
    bool                m_RoomClear;
    bool                m_IsBoss;

    MyTexture*  m_StartImg;
    MyTexture*  m_NormalImg;
    MyTexture*  m_TreasureImg;
    MyTexture*  m_BossImg;
    MyTexture*  m_CurImg;
    MyEffect*   m_Effect;

    vector<MyDoor*> m_vecDoor;
    bool UpDoorColOpen;
    bool DownDoorColOpen;
    bool LeftDoorColOpen;
    bool RightDoorColOpen;

public:
	virtual void begin() override;
	virtual void tick(float _DT) override;
	virtual void render(HDC _dc);

    virtual void BeginOverlap(MyCollider* _OwnCol, MyObject* _OtherObj, MyCollider* _OtherCol) override;
    virtual void Overlap(MyCollider* _OwnCol, MyObject* _OtherObj, MyCollider* _OtherCol) override;

public:
    void SetRoomImg(MyTexture* _Img) { m_CurImg = _Img; }
    MyTexture* GetNormalImg() { return m_NormalImg; }
    MyTexture* GetTreasureImg() { return m_TreasureImg; }
    MyTexture* GetBossImg() { return m_BossImg; }
    MyTexture* GetCurImg() { return m_CurImg; }

    void SetRoomType(ROOM_TYPE _Room) { m_CurRoomType = _Room; }
    ROOM_TYPE GetRoomType() { return m_CurRoomType; }

    void SetMonPos();
    void SetRoomOpen() { m_isOpen = true; }
    void SetRoomClose() { m_isOpen = false; }
    bool IsRoomOpen() { return m_isOpen; }
    void SetBossRoom() { m_IsBoss = true; }

    void PlayBossAnimation();

    void AddMonster(MyMonster* _Mons)
    {
        m_vecMons.push_back(_Mons);
        ++m_MonsterCount;
    }

    void CheckMonsterCount();

public:
    void SetUpDoorColOpen(bool _b) { UpDoorColOpen = _b; }
    void SetDownDoorColOpen(bool _b) { DownDoorColOpen = _b; }
    void SetLeftDoorColOpen(bool _b) { LeftDoorColOpen = _b; }
    void SetRightDoorColOpen(bool _b) { RightDoorColOpen = _b; }

    bool GetUpDoorColOpen() { return UpDoorColOpen; }
    bool GetDownDoorColOpen() { return DownDoorColOpen; }
    bool GetLeftDoorColOpen() { return LeftDoorColOpen; }
    bool GetRightDoorColOpen() { return RightDoorColOpen; }

public:
    CLONE(MyRoom);
    MyRoom();
    MyRoom(const MyRoom& _Origin);
	~MyRoom();

    friend class MyDoor;
    friend class NormalFly;
    friend class MyPlayLevel;
    friend class BossMonster;
};

