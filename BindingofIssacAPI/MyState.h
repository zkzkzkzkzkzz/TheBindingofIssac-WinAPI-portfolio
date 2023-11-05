#pragma once
#include "MyEntity.h"

#include "MyStateMachine.h"

#include "MyObject.h"
#include "MyAnimator.h"

#include "MyLevelMgr.h"
#include "MyLevel.h"

#include "MyPlayer.h"

class MyState :
    public MyEntity
{
private:
    MyStateMachine* m_pSM;
    UINT            m_StateID;


public:
    MyStateMachine* GetOwnerSM() { return m_pSM; }
    UINT GetStateID() { return m_StateID; }

public:
    virtual void finaltick(float _DT) = 0;
    virtual void Enter() = 0;
    virtual void Exit() = 0;

public:
    virtual MyState* Clone() = 0;

public:
    MyState();
    ~MyState();

    friend class MyStateMachine;
};

