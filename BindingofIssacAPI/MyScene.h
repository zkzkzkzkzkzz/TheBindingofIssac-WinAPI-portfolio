#pragma once
#include "MyObject.h"

class MyTexture;
class MyAnimator;
class MySound;

class MyScene :
    public MyObject
{
    GENERATED_OBJECT(MyObject);

private:
    MyTexture* m_Atlas;
    MyAnimator* m_Animator;

    float m_SceneTime;

    MySound* m_DOpenSound;
    MySound* m_DCloseSound;
    MySound* m_BossFight;
    MySound* m_Summon;

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

    friend class MyDoor;
};

