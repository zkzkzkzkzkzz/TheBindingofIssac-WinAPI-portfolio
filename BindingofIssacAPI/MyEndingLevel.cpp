#include "pch.h"
#include "MyEndingLevel.h"

#include "MyEngine.h"

#include "MyAssetMgr.h"
#include "MyKeyMgr.h"
#include "MyLevelMgr.h"
#include "MyCameraMgr.h"
#include "MyTimeMgr.h"

#include "MyObject.h"
#include "MyBackGround.h"
#include "TitleAnimUI.h"
#include "TitleTexUI.h"
#include "MyTexture.h"
#include "MyEndingScene.h"
#include "MySound.h"
#include "components.h"

void MyEndingLevel::init()
{

}

void MyEndingLevel::enter()
{
	// 카메라 설정
	vLookAt = MyEngine::GetInst()->GetResolution();
	vLookAt /= 2.f;
	MyCameraMgr::GetInst()->SetLookAt(vLookAt);

	MyEndingScene* pEnd = new MyEndingScene;
	pEnd->SetPos(Vec2(480.f, 320.f));
	pEnd->SetScale(Vec2(2.f, 2.f));
	pEnd->SetOffsetPos(Vec2(-240.f, -160.f));
	AddObject(LAYER::EFFECT, pEnd);

	m_Ending = MyAssetMgr::GetInst()->LoadSound(L"Ending", L"sound\\epilogue_01m.wav");
	m_Ending->SetVolume(80.f);
	m_Ending->SetPosition(0.f);
	m_Ending->Play();

	m_SceneTime = 0.f;
}

void MyEndingLevel::exit()
{
	DeleteAllObjects();
}

void MyEndingLevel::tick()
{
	MyLevel::tick();

	m_SceneTime += DT;
	 
	if (KEY_TAP(SPACE) || m_SceneTime >= 13.f)
	{
		m_Ending->Stop(true);
		ChangeLevel(LEVEL_TYPE::TITLE_LEVEL);
	}
}

