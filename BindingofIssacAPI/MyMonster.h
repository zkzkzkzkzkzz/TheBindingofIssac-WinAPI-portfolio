#pragma once
#include "MyObject.h"

class MyCollider;
class MyMovement;
class MyStateMachine;
class MyTexture;
class MyAnimator;

class MyMonster :
    public MyObject
{
    GENERATED_OBJECT(MyObject);

protected:
    bool    m_IsDead;

private:
    bool    IsBoss;
    Vec2    m_vInitPos;
    float   m_fDuration;
    float   m_AccTime;
    
    MyTexture*  m_Atlas;
    MyAnimator* m_Animator;

public:
    bool IsMonsterDead() { return m_IsDead; }
    void SetToInitPos();
    void SetInitPos(Vec2 _pos) { m_vInitPos = _pos; }

public:
    virtual void begin() override;
    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;

public:
    virtual void BeginOverlap(MyCollider* _OwnCol, MyObject* _OtherObj, MyCollider* _OtherCol) override;

public:
    CLONE(MyMonster);
    MyMonster();
    MyMonster(const MyMonster& _Origin);
    ~MyMonster();

};

