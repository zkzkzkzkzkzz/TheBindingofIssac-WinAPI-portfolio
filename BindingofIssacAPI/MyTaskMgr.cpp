#include "pch.h"
#include "MyTaskMgr.h"

#include "MyLevelMgr.h"
#include "MyLevel.h"
#include "MyObject.h"
#include "MyComponent.h"

MyTaskMgr::MyTaskMgr()
{

}

MyTaskMgr::~MyTaskMgr()
{

}

void MyTaskMgr::tick()
{
	for (size_t i = 0; i < m_vecTask.size(); ++i)
	{
		switch (m_vecTask[i].Type)
		{
		case TASK_TYPE::CREATE_OBJECT:
		{
			LAYER LayerType = (LAYER)m_vecTask[i].Param1;
			MyObject* Object = (MyObject*)m_vecTask[i].Param2;

			MyLevel* pCurLevel = MyLevelMgr::GetInst()->GetCurLevel();
			pCurLevel->AddObject(LayerType, Object);
			Object->begin();
		}
		break;

		case TASK_TYPE::DELETE_OBJECT:
		{
			MyObject* pDeadObject = (MyObject*)m_vecTask[i].Param1;
			pDeadObject->SetDead();
		}
		break;


		case TASK_TYPE::LEVEL_CHANGE:
		{
			LEVEL_TYPE type = (LEVEL_TYPE)m_vecTask[i].Param1;
			MyLevelMgr::GetInst()->ChangeLevel(type);
		}
		break;
		}
	}

	m_vecTask.clear();
}