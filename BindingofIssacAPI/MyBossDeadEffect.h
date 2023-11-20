#pragma once
#include "MyEffect.h"

class MyTexture;
class MyAnimator;

class MyBossDeadEffect :
    public MyEffect
{
    GENERATED_OBJECT(MyObject);

private:
    MyTexture* m_Atlas;
    MyAnimator* m_Animator;
    float       m_EffectTime;

public:
    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;

public:
    float GetEffectTime() { return m_EffectTime; }

public:
    CLONE_DISABLE(MyBossDeadEffect);
    MyBossDeadEffect();
    MyBossDeadEffect(const MyBossDeadEffect& _Origin) = delete;
    ~MyBossDeadEffect();
};

