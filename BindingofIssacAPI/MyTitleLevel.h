#pragma once

#include "MyLevel.h"

class MyTexture;
class TitleTexUI;
class MySound;

constexpr int MaxMenuSize = 5;

class MyTitleLevel :
	public MyLevel
{
private:
    MyTexture*  m_Texture;
    Vec2        vLookAt;
    MySound*    m_BGSound1;
    MySound*    m_BGSound2;
    MySound*    m_EffectSound;
    MySound*    m_LoadingSound;
    int         m_CurScreen;

    // 메뉴바
    int                 m_curIdx;
    TitleTexUI*         m_Curmenu;

    // 커서
    TitleTexUI*         m_Cursor;
    int                 m_CursorIdx;

    bool m_IsInit;

public:
    void SetCurScreen(TITLE_TYPE _type) { m_CurScreen = (int)_type; }
    int GetCurScreen() { return m_CurScreen; }

public:
    virtual void init() override;
    virtual void enter() override;
    virtual void exit() override;

    virtual void tick() override;
};

