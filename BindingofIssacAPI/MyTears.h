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

    float m_Speed;
    float m_Angle;

public:
    virtual void tick(float _DT) override;

    void SetAngle(float _theta) { m_Angle = _theta; }
    void SetSpeed(float _Speed) { m_Speed = _Speed; }

    float GetSpeed() { return m_Speed; }
    float GetAngle() { return m_Angle; };

public:
    CLONE(MyTears);
    MyTears();
    MyTears(const MyTears& _Origin);
    ~MyTears();
};

