#pragma once
#include "MyUI.h"

class MyTexture;
class MyAnimator;

typedef  void(*BtnCallBack)(void);
typedef  void(MyEntity::* DelegateFunc)(void);

class TitleUI :
    public MyUI
{
    GENERATED_OBJECT(MyUI);

private:
    MyTexture*  m_Atlas;
    MyAnimator* m_Animator;

    // 객체의 주소
    MyEntity* m_Inst;
    // 맴버함수의 주소
    DelegateFunc    m_Delegate;

public:
    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;

    void SetDeletage(MyEntity* _Inst, DelegateFunc _Func) { m_Inst = _Inst; m_Delegate = _Func; }

public:
    CLONE(TitleUI);
    TitleUI();
    ~TitleUI();
};

