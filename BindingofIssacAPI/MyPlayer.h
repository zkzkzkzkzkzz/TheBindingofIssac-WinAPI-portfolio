#pragma once
#include "MyObject.h"

class MyAnimator;
class MyMovement;
class MyCollider;
class MyShadow;

class MyPlayer :
    public MyObject
{
    GENERATED_OBJECT(MyObject);

private:
    MyAnimator* m_AnimatorHead;
    MyAnimator* m_AnimatorBody;
    MyMovement* m_Movement;
    MyCollider* m_Collider;
    MyShadow*   m_Shadow;

    // 눈물 딜레이
    float   m_Acctime;
    float   m_Duration;
    int     m_TearsCount;

    int     m_IsDamaged;
    float   m_DamagedMaxTime;
    float   m_DamagedAccTime;
    

public:
    virtual void begin() override;
    virtual void tick(float _DT) override;

public:
    virtual void BeginOverlap(MyCollider* _OwnCol, MyObject* _OtherObj, MyCollider* _OtherCol);
    virtual void EndOverlap(MyCollider* _OwnCol, MyObject* _OtherObj, MyCollider* _OtherCol);
    
public:
    CLONE(MyPlayer);
    MyPlayer();
    MyPlayer(const MyPlayer& _Origin);
    ~MyPlayer();
};

