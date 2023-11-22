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
class MySound;

enum class ATT_TYPE
{
    ATT1,
    ATT2,
};

class BossMonster :
    public MyMonster
{
    GENERATED_OBJECT(MyMonster);

private:
    MyTexture*  m_Atlas;
    MyTexture*  m_MonsterShadow;
    MyCollider* m_Collider;
    MyAnimator* m_Animator;
    MyMovement* m_Movement;

    FMonInfo m_Info;
    size_t m_MonsCount;

    float m_StartMoveTime;
    float m_MoveTime;
    float m_ChangeDirTime;
    FKDir m_StartDir;

    float m_AttTime;
    float m_StartAttTime;
    float m_AttDelay;
    ATT_TYPE m_AttType;

    MySound* m_SummonFly;

public:
    void ChangeDirectionU();
    void ChangeDirectionD();
    void ChangeDirectionL();
    void ChangeDirectionR();

    void Attack01();
    void Attack02();
    void SpawnFly();

    void SetStartDir(FKDir _dir);
    FKDir GetStartDir() { return m_StartDir; }

public:
    virtual void begin() override;
    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;

public:
    virtual void BeginOverlap(MyCollider* _OwnCol, MyObject* _OtherObj, MyCollider* _OtherCol) override;

public:
    CLONE(BossMonster);
    BossMonster();
    ~BossMonster();
};

