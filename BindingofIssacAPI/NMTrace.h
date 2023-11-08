#pragma once
#include "MyState.h"

#include "MyPlayer.h"

class NMTrace :
    public MyState
{
private:
    MyPlayer* m_pTarget;

public:
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(NMTrace);
    NMTrace();
    ~NMTrace();
};

