#pragma once

#include "MyLevel.h"

class MyTexture;
class TitleTexUI;

constexpr int MaxMenuSize = 5;

class MyTitleLevel :
	public MyLevel
{
private:
    MyTexture*  m_Texture;
    Vec2        vLookAt;
    int         m_CurScreen;

    vector<TitleTexUI*> m_vecMenu;
    int                 m_curIdx;
    TitleTexUI*         m_Curmenu;

private:
    void MoveCursor(int _Idx);

public:
    void SetCurScreen(TITLE_TYPE _type) { m_CurScreen = (int)_type; }
    int GetCurScreen() { return m_CurScreen; }

public:
    virtual void init() override;
    virtual void enter() override;
    virtual void exit() override;

    virtual void tick() override;
};

