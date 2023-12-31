#pragma once
#include "MyObject.h"
class MyTexture;
class MyAnimator;
class MyCollider;
class MyPlayer;
class MyShadow;
class MyMonsterEffect;
class MySound;

class MyMonsterTears :
    public MyObject
{
    GENERATED_OBJECT(MyObject);

private:
    MyTexture*  m_Atlas;
    MyAnimator* m_Animator;
    MyMovement* m_Movement;
    MyCollider* m_Collider;
    MyShadow*   m_Shadow;

    float   m_Speed;
    float   m_Angle;
    float   m_Duration;
    float   m_Acctime;
    bool    m_IsDestroy;

    MyMonsterEffect*    m_Effect;
    MyPlayer*           m_pTarget;
    Vec2                m_TargetPos;

    MySound* m_MTSound;

public:
    virtual void begin() override;
    virtual void tick(float _DT) override;

    void fire();
    void TearsDestroy();

public:
    void SetAngle(float _theta) { m_Angle = _theta; }
    void SetSpeed(float _Speed) { m_Speed = _Speed; }

    float GetSpeed() { return m_Speed; }
    float GetAngle() { return m_Angle; };

public:
    virtual void BeginOverlap(MyCollider* _OwnCol, MyObject* _OtherObj, MyCollider* _OtherCol) override;

public:
    CLONE(MyMonsterTears);
    MyMonsterTears();
    MyMonsterTears(const MyMonsterTears& _Origin);
    ~MyMonsterTears();
};

