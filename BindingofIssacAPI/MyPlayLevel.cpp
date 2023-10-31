#include "pch.h"
#include "MyPlayLevel.h"

#include "MyEngine.h"

#include "MyAssetMgr.h"
#include "MyKeyMgr.h"
#include "MyLevelMgr.h"
#include "MyCameraMgr.h"

#include "MyObject.h"
#include "MyBackGround.h"
#include "TitleUI.h"
#include "MyTexture.h"
#include "components.h"

void MyPlayLevel::init()
{

}

void MyPlayLevel::enter()
{
}

void MyPlayLevel::exit()
{
	DeleteAllObjects();
}

void MyPlayLevel::tick()
{
	MyLevel::tick();
}
