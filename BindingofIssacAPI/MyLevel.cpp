#include "pch.h"
#include "MyLevel.h"

#include "MyTimeMgr.h"
#include "MyLayer.h"
#include "MyObject.h"


MyLevel::MyLevel()
{
	for (UINT i = 0; i < (UINT)LAYER::END; ++i)
	{
		m_Layer[i] = new MyLayer;
	}
}

MyLevel::~MyLevel()
{
	for (UINT i = 0; i < (UINT)LAYER::END; ++i)
	{
		if (nullptr != m_Layer[i])
			delete m_Layer[i];
	}
}

void MyLevel::begin()
{
	for (UINT i = 0; i < (UINT)LAYER::END; ++i)
	{
		m_Layer[i]->begin();
	}
}

void MyLevel::tick()
{
	for (UINT i = 0; i < (UINT)LAYER::END; ++i)
	{
		m_Layer[i]->clear();
	}


	for (UINT i = 0; i < (UINT)LAYER::END; ++i)
	{
		m_Layer[i]->tick(DT);
	}

	for (UINT i = 0; i < (UINT)LAYER::END; ++i)
	{
		m_Layer[i]->finaltick(DT);
	}
}

void MyLevel::render(HDC _dc)
{
	for (UINT i = 0; i < (UINT)LAYER::END; ++i)
	{
		m_Layer[i]->render(_dc);
	}
}

void MyLevel::AddObject(LAYER _LayerType, MyObject* _Object)
{
	// 레이어에 오브젝트를 집어넣는다.
	m_Layer[(UINT)_LayerType]->AddObject(_Object);

	// 레이어 인덱스값을 오브젝트에 세팅해준다(오브젝트가 자신이 소속된 레이어 인덱스를 알게 한다)
	_Object->m_iLayerIdx = (int)_LayerType;
}

void MyLevel::DeleteAllObjects()
{
	for (UINT i = 0; i < (UINT)LAYER::END; ++i)
	{
		m_Layer[i]->DeleteAllObjects();
	}
}

void MyLevel::DeleteObjectsByLayer(LAYER _Layer)
{
	m_Layer[(UINT)_Layer]->DeleteAllObjects();
}

MyObject* MyLevel::FindObjectByName(const wstring& _Name)
{
	for (UINT i = 0; i < (UINT)LAYER::END; ++i)
	{
		const vector<MyObject*>& vecObjects = m_Layer[i]->GetObjects();
		for (size_t j = 0; j < vecObjects.size(); ++j)
		{
			if (vecObjects[j]->GetName() == _Name)
			{
				return vecObjects[j];
			}
		}
	}

	return nullptr;
}
