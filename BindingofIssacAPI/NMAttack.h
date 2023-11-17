#pragma once
#include "MyState.h"

#include "MyPlayer.h"

enum class AttDir
{
    NONE,
    LEFT,
    RIGHT,
};

class NMAttack :
    public MyState
{
private:
    MyPlayer* m_pTarget;
    int m_PrevDir;

public:
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(NMAttack);
    NMAttack();
    ~NMAttack();
};

