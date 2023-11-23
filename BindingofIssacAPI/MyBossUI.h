#pragma once
#include "MyUI.h"

class MyAnimator;

class MyBossUI :
    public MyUI
{
    GENERATED_OBJECT(MyUI);

private:
    MyAnimator* m_Animator;

    // 자를 위치 좌상단 좌표
    Vec2       m_CutPos;
    // 얼마나 자를 것인가
    Vec2       m_CutSize;

    int m_BossHP;
    bool m_IsUIRender;

public:
    void SetCutPos(Vec2 _vPos) { m_CutPos = _vPos; }
    void SetCutSize(Vec2 _vSize) { m_CutSize = _vSize; }
    Vec2 GetCutPos() { return m_CutPos; }
    Vec2 GetCutSize() { return m_CutSize; }

    void SetBossHP(int _HP) { m_BossHP = _HP; }
    int GetBossHP() { return m_BossHP; }
    void SetUIRender(bool _b) { m_IsUIRender = _b; }

public:
    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;

public:
    CLONE(MyBossUI);
    MyBossUI();
    ~MyBossUI();
};

