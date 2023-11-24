#pragma once
#include "MyMonster.h"

class MyTexture;
class MyAnimator;
class MyMovement;
class MyCollider;
class MyStateMachine;
class MyRoom;

class NormalFly :
    public MyMonster
{
    GENERATED_OBJECT(MyMonster);

private:
    MyTexture*      m_Atlas;
    MyTexture*      m_MonsterShadow;
    MyAnimator*     m_Animator;
    MyCollider*     m_Collider;
    MyStateMachine* m_AI;
    FMonInfo        m_Info;
    //MyRoom*         m_OwnerRoom;

public:
    virtual void begin() override;
    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;

public:
    virtual void BeginOverlap(MyCollider* _OwnCol, MyObject* _OtherObj, MyCollider* _OtherCol) override;

public:
    CLONE(NormalFly);
    NormalFly();
    NormalFly(const NormalFly& _Origin);
    ~NormalFly();
};

