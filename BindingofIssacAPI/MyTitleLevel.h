#pragma once

#include "MyLevel.h"

class MyTexture;

class MyTitleLevel :
	public MyLevel
{
private:
    MyTexture*  m_Texture;
    Vec2        vLookAt;
    int         m_CurScreen;

    // 초기 이동 속도
    float       m_Speed;

public:
    void SetCurScreen(TITLE_TYPE _type) { m_CurScreen = (int)_type; }
    int GetCurScreen() { return m_CurScreen; }

public:
    virtual void init() override;
    virtual void enter() override;
    virtual void exit() override;

    virtual void tick() override;
};

