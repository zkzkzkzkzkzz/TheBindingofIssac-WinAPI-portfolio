#pragma once
#include "MyObject.h"


class MyEffect :
    public MyObject
{
    GENERATED_OBJECT(MyObject);

private:
    MyTexture*  m_Atlas;
    MyAnimator* m_EffectAnimator;
    float       m_EffectTime;

public:
    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;

public:
    float GetEffectTime() { return m_EffectTime; }

public:
    CLONE_DISABLE(MyEffect);
    MyEffect();
    MyEffect(const MyEffect& _Origin) = delete;
    ~MyEffect();

    friend class MyTears;
};

