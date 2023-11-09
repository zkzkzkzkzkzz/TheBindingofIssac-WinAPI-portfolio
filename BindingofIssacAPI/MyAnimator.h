#pragma once
#include "MyComponent.h"

class MyAnim;
class MyTexture;

class MyAnimator :
    public MyComponent
{
private:
    // Animator 가 보유하고 있는 Animation 목록, 탐색을 위해서 Map 으로 
    map<wstring, MyAnim*>   m_mapAnim;

    // 현재 재생중인 Animation
    MyAnim*                 m_CurAnim;

    // 반복 재생 여부
    bool                    m_bRepeat;

public:
    void Play(const wstring& _strName, bool _bRepeat);
    void Stop();


    // Animation 찾기
    MyAnim* FindAnim(const wstring& _strName);

    // 애니메이션 생성
    void CreateAnimation(const wstring& _strName, MyTexture* _Altas, Vec2 _vLeftTop, Vec2 _vCutSize
        , Vec2 _vOffset, float _duration, int _MaxFrm);

    void SaveAnimations(const wstring& _strRelativePath);
    void LoadAnimation(const wstring& _strRelativePath);

public:
    virtual void finaltick(float _DT) override;
    virtual void render(HDC _dc) override;

public:
    CLONE(MyAnimator);
    MyAnimator(MyObject* _Owner);
    MyAnimator(const MyAnimator& _Origin);
    ~MyAnimator();
};

