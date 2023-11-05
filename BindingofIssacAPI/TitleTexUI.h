#pragma once
#include "MyUI.h"

class MyTexture;
class MyAnimator;

typedef  void(*BtnCallBack)(void);
typedef  void(MyEntity::* DelegateFunc)(void);

class TitleTexUI :
    public MyUI
{
    GENERATED_OBJECT(MyUI);

private:
    MyTexture* m_Menu;
    Vec2       m_CutPos;
  
    BtnCallBack     m_CallBackFunc;
    // 객체의 주소
    MyEntity*       m_Inst;
    // 맴버함수의 주소
    DelegateFunc    m_Delegate;

public:
    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;
    virtual void LBtnClicked(Vec2 _vMousePos) override;

    void SetCutPos(Vec2 _vPos) { m_CutPos = _vPos; }
    Vec2 GetCutPos() { return m_CutPos; }

    void SetCallBack(BtnCallBack _CallBackFunc) { m_CallBackFunc = _CallBackFunc; }
    void SetDeletage(MyEntity* _Inst, DelegateFunc _Func) { m_Inst = _Inst; m_Delegate = _Func; }

public:
    CLONE(TitleTexUI);
    TitleTexUI();
    ~TitleTexUI();
};

