#include "pch.h"
#include "MyObject.h"

#include "MyEngine.h"

#include "MyComponent.h"
#include "MyTaskMgr.h"

MyObject::MyObject()
	: m_iLayerIdx(-1)
{
}

MyObject::MyObject(const MyObject& _Origin)
	: MyEntity(_Origin)
	, m_Pos(_Origin.m_Pos)
	, m_Scale(_Origin.m_Scale)
	, m_OffsetPos(_Origin.m_OffsetPos)
	, m_iLayerIdx(-1)
{
	for (size_t i = 0; i < _Origin.m_vecComponent.size(); ++i)
	{
		MyComponent* pCom = _Origin.m_vecComponent[i]->Clone();
		pCom->m_pOwner = this;
		m_vecComponent.push_back(pCom);
	}
}

MyObject::~MyObject()
{
	for (size_t i = 0; i < m_vecComponent.size(); ++i)
	{
		if (nullptr != m_vecComponent[i])
			delete m_vecComponent[i];
	}
}

void MyObject::tick(float _DT)
{
	for (size_t i = 0; i < m_vecComponent.size(); ++i)
	{
		m_vecComponent[i]->tick(_DT);
	}
}

void MyObject::finaltick(float _DT)
{
	for (size_t i = 0; i < m_vecComponent.size(); ++i)
	{
		m_vecComponent[i]->finaltick(_DT);
	}
}

void MyObject::render(HDC _dc)
{
	for (size_t i = 0; i < m_vecComponent.size(); ++i)
	{
		m_vecComponent[i]->render(_dc);
	}

	if (!DEBUG_RENDER)
	{
		return;
	}

	SELECT_PEN(_dc, PEN_TYPE::RED_PEN);

	Vec2 vRenderPos = GetRenderPos();
	MoveToEx(_dc, int(vRenderPos.x - 7.f), (int)vRenderPos.y, nullptr);
	LineTo(_dc, int(vRenderPos.x + 7.f), (int)vRenderPos.y);

	MoveToEx(_dc, int(vRenderPos.x), int(vRenderPos.y - 7.f), nullptr);
	LineTo(_dc, int(vRenderPos.x), int(vRenderPos.y + 7.f));
}

void MyObject::Destroy()
{
	FTask task;
	task.Type = TASK_TYPE::DELETE_OBJECT;
	task.Param1 = (INT_PTR)this;

	MyTaskMgr::GetInst()->AddTask(task);
}


void MyObject::SetDead()
{
	m_bDead = true;

	for (size_t i = 0; i < m_vecComponent.size(); ++i)
	{
		m_vecComponent[i]->m_bDead = true;
	}
}