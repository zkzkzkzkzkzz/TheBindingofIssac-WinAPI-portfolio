#pragma once
#include "MyObject.h"

class MyTexture;
class MyAnimator;

class MyBackGround :
    public MyObject
{
    GENERATED_OBJECT(MyObject);

private:
    MyTexture* m_Atlas;

public:
    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;

public:
    CLONE_DISABLE(MyBackGround);
    MyBackGround();
    MyBackGround(const MyBackGround& _Origin) = delete;
    ~MyBackGround();
};

