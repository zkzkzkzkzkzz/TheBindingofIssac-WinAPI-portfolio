#pragma once
#include "MyObject.h"

class MyTexture;
class MyAnimator;

class MyScene :
    public MyObject
{
    GENERATED_OBJECT(MyObject);

private:
    MyTexture* m_Atlas;
    MyAnimator* m_Animator;

    float m_SceneTime;

public:
    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;

public:
    float GetSceneTime() { return m_SceneTime; }

public:
    CLONE_DISABLE(MyScene);
    MyScene();
    MyScene(const MyScene& _Origin) = delete;
    ~MyScene();
};

