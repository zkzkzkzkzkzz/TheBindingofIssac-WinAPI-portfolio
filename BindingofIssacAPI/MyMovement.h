#pragma once
#include "MyComponent.h"

class MyMovement :
    public MyComponent
{
private:
    // 누적된 힘
    Vec2    m_Force;

    // 현재 가속도
    Vec2    m_Accel;

    // 속도
    Vec2    m_Velocity;

    // 질량
    float   m_Mass;

    // 보장된 초기 속력
    float   m_InitSpeed;

    // 최대 속력
    float   m_MaxSpeed;

    // 마찰 크기
    float   m_FrictionScale;

    // 중력
    float   m_Gravity;

    bool    m_UsingGravity;

    float   m_RotateSpeed;

    Vec2    m_vDir;

public:
    void AddForce(Vec2 _vForce)
    {
        m_Force += _vForce;
    }

    Vec2 GetForce()
    {
        return m_Force;
    }

    void SetVelocity(Vec2 _vVelocity)
    {
        m_Velocity = _vVelocity;
    }

    void AddVelocity(Vec2 _vAdd)
    {
        m_Velocity += _vAdd;
    }

    Vec2 GetVelocity()
    {
        return m_Velocity;
    }

    void SetMass(float _Mass)
    {
        m_Mass = _Mass;
    }

    float GetMass()
    {
        return m_Mass;
    }

    void SetInitSpeed(float _Speed)
    {
        m_InitSpeed = _Speed;
    }

    void SetMaxSpeed(float _Speed)
    {
        m_MaxSpeed = _Speed;
    }

    float GetInitSpeed()
    {
        return m_InitSpeed;
    }

    float GetMaxSpeed()
    {
        return m_MaxSpeed;
    }

    void SetFrictionScale(float _F)
    {
        m_FrictionScale = _F;
    }

    float GetFrictionScale()
    {
        return m_FrictionScale;
    }

    void SetGravity(float _f)
    {
        m_Gravity = _f;
    }

    float GetGravity()
    {
        return m_Gravity;
    }

    void UseGravity(bool _b)
    {
        m_UsingGravity = _b;
    }


public:
    virtual void finaltick(float _DT) override;

    void TearsGravity();

public:
    CLONE(MyMovement);

    MyMovement(MyObject* _Owner);
    ~MyMovement();
};


