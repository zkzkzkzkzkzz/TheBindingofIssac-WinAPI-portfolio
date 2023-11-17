#pragma once
#include "MyMonster.h"

class MyTexture;
class MyAnimator;
class MyCollider;
class MyMovement;
class MyStateMachine;

class Pooter :
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

    float   m_AttDelayTime;
    float   m_Acctime;

public:
    virtual void begin() override;
    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;

    float GetAttDelayTime() { return m_AttDelayTime; }
    float GetAccTime() { return m_Acctime; }
    void SetAccTime(float _time) { m_Acctime = _time; }

public:
    virtual void BeginOverlap(MyCollider* _OwnCol, MyObject* _OtherObj, MyCollider* _OtherCol) override;

public:
    CLONE(Pooter);
    Pooter();
    Pooter(const Pooter& _Origin);
    ~Pooter();
};
