#pragma once
#include "MyState.h"

class MyPlayer;

class NMIdle :
    public MyState
{
private:
    MyPlayer* m_pTarget;

public:
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(NMIdle);
    NMIdle();
    ~NMIdle();
};

