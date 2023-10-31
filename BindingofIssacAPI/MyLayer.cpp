#include "pch.h"
#include "MyLayer.h"

#include "MyObject.h"
#include "MyGCMgr.h"



MyLayer::MyLayer()
{
}

MyLayer::~MyLayer()
{
	DeleteAllObjects();
}

void MyLayer::begin()
{
	for (size_t i = 0; i < m_vecObjects.size(); ++i)
	{
		m_vecObjects[i]->begin();
	}
}

void MyLayer::tick(float _DT)
{
	for (size_t i = 0; i < m_vecObjects.size(); ++i)
	{
		m_vecObjects[i]->tick(_DT);
	}
}

void MyLayer::finaltick(float _DT)
{
	for (size_t i = 0; i < m_vecObjects.size(); ++i)
	{
		m_vecObjects[i]->finaltick(_DT);
	}
}

void MyLayer::render(HDC _dc)
{
	vector<MyObject*>::iterator iter = m_vecObjects.begin();

	for (; iter != m_vecObjects.end();)
	{
		if ((*iter)->IsDead())
		{
			MyGCMgr::GetInst()->AddEntity((*iter));
			iter = m_vecObjects.erase(iter);
		}
		else
		{
			(*iter)->render(_dc);
			++iter;
		}
	}
}


void MyLayer::DeleteAllObjects()
{
	for (size_t i = 0; i < m_vecObjects.size(); ++i)
	{
		delete m_vecObjects[i];
	}

	m_vecObjects.clear();
}