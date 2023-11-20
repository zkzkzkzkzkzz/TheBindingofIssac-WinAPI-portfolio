#pragma once
#include "MyObject.h"

class MyTexture;
class MyAnimator;

class MyEndingScene :
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
    CLONE_DISABLE(MyEndingScene);
    MyEndingScene();
    MyEndingScene(const MyEndingScene& _Origin) = delete;
    ~MyEndingScene();
};

