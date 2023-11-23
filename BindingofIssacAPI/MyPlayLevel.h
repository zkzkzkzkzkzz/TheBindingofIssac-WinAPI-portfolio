#pragma once
#include "MyLevel.h"

class MyTexture;
class MyRoom;
class MySound;

class MyPlayLevel :
    public MyLevel
{
private:
    MyTexture*      m_Texture;
    Vec2            vLookAt;
    
    MySound* m_BGSound;

    bool m_IsInit;

public:
    void SetToInitTrue() { m_IsInit = true; }
    MySound* GetBGSound() { return m_BGSound; }

public:
    virtual void init() override;
    virtual void enter() override;
    virtual void exit() override;

    virtual void tick() override;
};

