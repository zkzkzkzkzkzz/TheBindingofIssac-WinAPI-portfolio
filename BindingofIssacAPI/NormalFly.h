#pragma once
#include "MyMonster.h"

class MyTexture;
class MyAnimator;
class MyMovement;
class MyCollider;
class MyStateMachine;

class NormalFly :
    public MyMonster
{
    GENERATED_OBJECT(MyMonster);

private:
    MyTexture*      m_Atlas;
    MyAnimator*     m_Animator;
    MyMovement*     m_Movement;
    MyCollider*     m_Collider;
    MyStateMachine* m_AI;

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
