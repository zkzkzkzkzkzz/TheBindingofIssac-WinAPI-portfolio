#pragma once
#include "MyObject.h"

class MyTexture;
class MyCollider;

class MyShadow :
    public MyObject
{
    GENERATED_OBJECT(MyObject);

private:
    MyTexture*  m_ShadowTex;
    MyCollider* m_Collider;

public:
    virtual void begin() override;
    virtual void tick(float _DT) override;
    virtual void render(HDC _dc);

public:
    CLONE(MyShadow);
    MyShadow();
    MyShadow(const MyShadow& _Origin);
    ~MyShadow();
};

