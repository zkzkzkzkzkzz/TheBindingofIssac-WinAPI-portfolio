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
#include "components.h"

void MyEndingLevel::init()
{

}

void MyEndingLevel::enter()
{

}

void MyEndingLevel::exit()
{
	DeleteAllObjects();
}

void MyEndingLevel::tick()
{
	MyLevel::tick();
}

