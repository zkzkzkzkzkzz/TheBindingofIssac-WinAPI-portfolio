#pragma once
#include "MyObject.h"

class MyUI :
    public MyObject
{
    GENERATED_OBJECT(MyObject);
    
private:
    MyUI*               m_ParentUI;
    vector<MyUI*>       m_vecChildUI;
    Vec2                m_vFinalPos;

public:
    void AddChildUI(MyUI* _ChildUI)
    {
        m_vecChildUI.push_back(_ChildUI);
        _ChildUI->m_ParentUI = this;
    }

public:
    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;

    Vec2 GetFinalPos() { return m_vFinalPos; }

public:
    virtual MyUI* Clone() = 0;
    MyUI();
    MyUI(const MyUI& _Origin);
    ~MyUI();
};
