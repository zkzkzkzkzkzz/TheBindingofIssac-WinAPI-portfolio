#pragma once
#include "MyUI.h"

class MyTexture;
class MyAnimator;

class MyLoadUI :
    public MyUI
{
    GENERATED_OBJECT(MyUI);

private:
    MyTexture* m_Atlas;
    MyAnimator* m_Animator;
    float m_AccTime;

public:
    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;

public:
    CLONE(MyLoadUI);
    MyLoadUI();
    ~MyLoadUI();
};

