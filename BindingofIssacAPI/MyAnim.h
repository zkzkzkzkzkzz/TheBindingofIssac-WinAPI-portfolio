#pragma once
#include "MyEntity.h"

class MyTexture;

struct FFrame
{
    Vec2 vLeftTop;  // 아틀라스 내에서 잘라낼 좌상단 위치
    Vec2 vCutSize;  // 잘라낼 크기
    Vec2 vOffset;   // 오브젝트 중심에서 이동 값
    float Duration; // 해당 프레임 노출 시간
};


class MyAnimator;
class MyTears;

class MyAnim :
    public MyEntity
{
private:
    MyAnimator*     m_pAnimator;

    vector<FFrame>  m_vecFrm;
    MyTexture*      m_Atlas;
    int             m_iCurFrm;

    // 누적 시간
    float           m_AccTime;

    // animation 재생 완료 체크
    bool            m_bFinish;


public:
    void finaltick();
    void render(HDC _dc);

public:
    void Create(const wstring& _strName, MyTexture* _Atlas
        , Vec2 _vLeftTop, Vec2 _vCutSize, Vec2 _vOffset, float _Duration, int _MaxFrm);

    bool IsFinish() { return m_bFinish; }

    void Reset()
    {
        m_AccTime = 0.f;
        m_iCurFrm = 0;
        m_bFinish = false;
    }

    bool Save(const wstring& _FilePath);
    bool Load(const wstring& _FilePath);

public:
    CLONE(MyAnim);

    MyAnim();
    ~MyAnim();

    friend class MyAnimator;
    friend class MyTears;
    friend class MyEffect;
};

