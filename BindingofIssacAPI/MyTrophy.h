#pragma once
#include "MyObject.h"

class MyTexture;
class MyCollider;

class MyTrophy :
    public MyObject
{
    GENERATED_OBJECT(MyObject);

private:
    MyTexture* m_Atlas;
    MyCollider* m_Collider;

public:
    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;

public:
    virtual void BeginOverlap(MyCollider* _OwnCol, MyObject* _OtherObj, MyCollider* _OtherCol);

public:
    CLONE_DISABLE(MyTrophy);
    MyTrophy();
    MyTrophy(const MyTrophy& _Origin) = delete;
    ~MyTrophy();
};

