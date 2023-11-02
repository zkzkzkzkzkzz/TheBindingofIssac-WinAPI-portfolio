#pragma once
#include "MyObject.h"

class MyTexture;

enum class ROOM_TYPE
{
    START,
    NORMAL,
    TREASURE,
    BOSS,
    END,
};

class MyRoom :
    public MyObject
{
    GENERATED_OBJECT(MyObject);

private:
    int        m_MonsterCount;
    bool       m_isOpen;
    bool       m_IsBoss;

    MyTexture* m_StartImg;
    MyTexture* m_NormalImg;
    MyTexture* m_TreasureImg;
    MyTexture* m_BossImg;
    MyTexture* m_CurImg;

public:
	virtual void begin() override;
	virtual void tick(float _DT) override;
	virtual void render(HDC _dc);

public:
    void SetRoomImg(MyTexture* _Img) { m_CurImg = _Img; }
    MyTexture* GetNormalImg() { return m_NormalImg; }
    MyTexture* GetTreasureImg() { return m_TreasureImg; }
    MyTexture* GetBossImg() { return m_BossImg; }
    MyTexture* GetCurImg() { return m_CurImg; }

public:
    CLONE(MyRoom);
    MyRoom();
    MyRoom(const MyRoom& _Origin);
	~MyRoom();
};

