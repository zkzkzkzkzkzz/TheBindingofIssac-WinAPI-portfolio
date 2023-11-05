#pragma once
#include "MyState.h"

class MyPlayer;

class MyIssacIdle :
    public MyState
{
private:
    MyPlayer* m_pTarget;

public:
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(MyIssacIdle);
    MyIssacIdle();
    ~MyIssacIdle();
};

