#pragma once
#include "MyMonster.h"

class MyTexture;
class MyAnimator;
class MyPlayer;

enum class HOST_STATE
{
    IDLE,
    ATT,
};

class Host :
    public MyMonster
{
    GENERATED_OBJECT(MyMonster);

private:
    MyTexture* m_MonsterShadow;
    MyCollider* m_Collider;
    MyAnimator* m_Animator;

    FMonInfo m_Info;
    HOST_STATE m_HostState;
    MyPlayer* m_Target;

    float m_AccTime;

public:
    void IdleToAtt();
    void AttToIdle();

public:
    virtual void begin() override;
    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;

public:
    virtual void BeginOverlap(MyCollider* _OwnCol, MyObject* _OtherObj, MyCollider* _OtherCol) override;

public:
    CLONE(Host);
    Host();
    ~Host();
};

