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

private:
    bool    IsBoss;
    int     m_MonsterCount;

    MyTexture*  m_Atlas;
    MyAnimator* m_Animator;

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

