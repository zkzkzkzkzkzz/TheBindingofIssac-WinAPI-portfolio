#pragma once
#include "MyObject.h"

class MyTexture;
class MyAnimator;

class MyTears :
    public MyObject
{
    GENERATED_OBJECT(MyObject);

private:
    MyTexture*  m_Atlas;
    MyAnimator* m_Animator;
    MyMovement* m_Movement;

    float   m_Speed;
    float   m_Angle;
    Vec2    m_vAngle;
    float   m_Duration;
    float   m_Acctime;
    bool    m_IsDestroy;

public:
    virtual void tick(float _DT) override;
    
    void fire();
    void TearsDestroy();

    void SetAngle(float _theta) { m_Angle = _theta; }
    void SetSpeed(float _Speed) { m_Speed = _Speed; }
    void SetvAngle(Vec2 _vDir) { m_vAngle = _vDir; }
    Vec2 GetvAngle() { return m_vAngle; }

    float GetSpeed() { return m_Speed; }
    float GetAngle() { return m_Angle; };

public:
    CLONE(MyTears);
    MyTears();
    MyTears(const MyTears& _Origin);
    ~MyTears();
};

