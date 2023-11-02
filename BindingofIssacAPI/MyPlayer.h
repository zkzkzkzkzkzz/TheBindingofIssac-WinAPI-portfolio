#pragma once
#include "MyObject.h"

class MyAnimator;
class MyMovement;
class MyCollider;

class MyPlayer :
    public MyObject
{
    GENERATED_OBJECT(MyObject);

private:
    MyAnimator* m_AnimatorHead;
    MyAnimator* m_AnimatorBody;
    MyMovement* m_Movement;
    //MyCollider* m_Collider;

public:
    virtual void tick(float _DT) override;
    
public:
    CLONE(MyPlayer);
    MyPlayer();
    MyPlayer(const MyPlayer& _Origin);
    ~MyPlayer();
};

