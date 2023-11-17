#pragma once
#include "MyObject.h"

class MyTexture;
class MyAnimator;
class MyCollider;
class MyRoom;
class MyEffect;

class MyDoor :
    public MyObject
{
    GENERATED_OBJECT(MyObject);

private:
    MyTexture*  m_Atlas;
    MyAnimator* m_OutAnimator;
    MyAnimator* m_InAnimator;
    MyCollider* m_OpenCollider;
    MyCollider* m_CloseCollider;

    MyRoom* m_OwnerRoom;

    int     m_DoorDir;
    bool    UpDoorColOpen;
    bool    DownDoorColOpen;
    bool    LeftDoorColOpen;
    bool    RightDoorColOpen;

    MyEffect* m_Effect;

public:
    virtual void begin() override;
    virtual void tick(float _DT) override;

public:
    virtual void BeginOverlap(MyCollider* _OwnCol, MyObject* _OtherObj, MyCollider* _OtherCol) override;
    virtual void Overlap(MyCollider* _OwnCol, MyObject* _OtherObj, MyCollider* _OtherCol) override;

public:
    void SetDoorDir(DOOR_DIR _Dir) { m_DoorDir = (int)_Dir; }
    int GetDoorDir() { return m_DoorDir; }

public:
    CLONE(MyDoor);
    MyDoor();
    MyDoor(MyRoom* _Owner);
    ~MyDoor();
};

