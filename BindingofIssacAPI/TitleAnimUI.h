#pragma once
#include "MyUI.h"

class MyTexture;
class MyAnimator;

class TitleAnimUI :
    public MyUI
{
    GENERATED_OBJECT(MyUI);

private:
    MyTexture*  m_Atlas;
    MyAnimator* m_Animator;

public:
    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;

public:
    CLONE(TitleAnimUI);
    TitleAnimUI();
    ~TitleAnimUI();
};
