#pragma once

#include "MyEntity.h"


class MyObject;

class MyComponent :
    public MyEntity
{
private:
    MyObject* m_pOwner;

public:
    MyObject* GetOwner() { return m_pOwner; }


public:
    virtual void tick(float _DT) {}
    virtual void finaltick(float _DT) = 0;
    virtual void render(HDC _dc) {}

public:
    virtual MyComponent* Clone() = 0;

public:
    MyComponent(MyObject* _Owner);
    ~MyComponent();

    friend class MyObject;
};


