#pragma once
#include "MyLevel.h"

class MyTexture;
class MyAnimator;
class MySound;

class MyLoadLevel :
    public MyLevel
{
private:
    MyTexture*  m_Atlas;
    MyAnimator* m_Animator;
    Vec2        vLookAt;

    MySound* m_Loading;

    float m_SceneTime;
    bool m_IsInit;
    bool m_IsFade;

public:
    virtual void init() override;
    virtual void enter() override;
    virtual void exit() override;

    virtual void tick() override;
};

