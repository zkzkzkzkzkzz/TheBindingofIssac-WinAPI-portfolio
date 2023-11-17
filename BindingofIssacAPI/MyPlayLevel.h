#pragma once
#include "MyLevel.h"

class MyTexture;
class MyRoom;

class MyPlayLevel :
    public MyLevel
{
private:
    MyTexture*      m_Texture;
    Vec2            vLookAt;

public:
    virtual void init() override;
    virtual void enter() override;
    virtual void exit() override;

    virtual void tick() override;
};

