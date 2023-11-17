#pragma once
#include "MyObject.h"

class MyTexture;
class MyCollider;
class MyTears;
class MyMonsterTears;

class MyShadow :
    public MyObject
{
    GENERATED_OBJECT(MyObject);

private:
    MyTexture*      m_ShadowTex;
    MyCollider*     m_Collider;
    MyTears*        m_OwnerTears;
    MyMonsterTears* m_MonsOwnerTears;

public:
    MyTears* GetOwnerTears() { return m_OwnerTears; }

public:
    virtual void begin() override;
    virtual void tick(float _DT) override;
    virtual void render(HDC _dc);

public:
    CLONE(MyShadow);
    MyShadow();
    MyShadow(MyTears* _Owner);
    MyShadow(MyMonsterTears* _Owner);
    MyShadow(const MyShadow& _Origin);
    ~MyShadow();
};

