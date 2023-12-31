#pragma once
#include "MyMonster.h"
#include <ctime>
#include <thread>
#include <chrono>

class MyTexture;
class MyAnimator;
class MyMovement;
class MyCollider;
class MyRoom;

class FloatingKnight :
    public MyMonster
{
    GENERATED_OBJECT(MyMonster);

private:
    MyTexture*  m_Atlas;
    MyTexture*  m_MonsterShadow;
    MyCollider* m_HeadCollider;
    MyCollider* m_TailCollider;
    MyAnimator* m_Animator;
    MyMovement* m_Movement;
    
    FMonInfo m_Info;

    float m_StartMoveTime;
    float m_MoveTime;
    float m_ChangeDirTime;
    FKDir m_StartDir;

public:
    void ChangeDirectionU();
    void ChangeDirectionD();
    void ChangeDirectionL();
    void ChangeDirectionR();

    void SetStartDir(FKDir _dir);
    FKDir GetStartDir() { return m_StartDir; }

public:
    virtual void begin() override;
    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;

public:
    virtual void BeginOverlap(MyCollider* _OwnCol, MyObject* _OtherObj, MyCollider* _OtherCol) override;

public:
    CLONE(FloatingKnight);
    FloatingKnight();
    ~FloatingKnight();
};

