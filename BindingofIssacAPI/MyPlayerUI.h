#pragma once
#include "MyUI.h"

class MyTexture;

enum class UI_TYPE
{
    HEART,
    PICKUP,
    FONT,
};

class MyPlayerUI :
    public MyUI
{
    GENERATED_OBJECT(MyUI);

private:
    MyTexture* m_Atlas;
    MyTexture* m_Atlas2;
    MyTexture* m_Atlas3;

    // 자를 위치 좌상단 좌표
    Vec2       m_CutPos;
    // 얼마나 자를 것인가
    Vec2       m_CutSize;

    UI_TYPE m_Type;
    
    bool m_IsCutScene;

public:
    void SetCutScene(bool _b = false) { m_IsCutScene = _b; }
    bool IsCutScene() { return m_IsCutScene; }

public:
    void SetCutPos(Vec2 _vPos) { m_CutPos = _vPos; }
    void SetCutSize(Vec2 _vSize) { m_CutSize = _vSize; }
    Vec2 GetCutPos() { return m_CutPos; }
    Vec2 GetCutSize() { return m_CutSize; }

    void SetUIType(UI_TYPE _Type) { m_Type = _Type; }

public:
    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;

public:
    CLONE(MyPlayerUI);
    MyPlayerUI();
    ~MyPlayerUI();
};

