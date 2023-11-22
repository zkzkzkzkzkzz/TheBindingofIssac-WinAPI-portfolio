#pragma once
#include "MyLevel.h"

class MyTexture;
class MyAnimator;
class MySound;

class MyEndingLevel :
    public MyLevel
{
private:
    MyTexture*  m_Atlas;
    MyAnimator* m_Animator;
    Vec2        vLookAt;
    
    MySound* m_Ending;

public:
    virtual void init() override;
    virtual void enter() override;
    virtual void exit() override;

    virtual void tick() override;
};

