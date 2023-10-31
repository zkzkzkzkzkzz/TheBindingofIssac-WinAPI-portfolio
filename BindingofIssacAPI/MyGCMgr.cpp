#include "pch.h"
#include "MyGCMgr.h"

#include "MyEntity.h"

MyGCMgr::MyGCMgr()
{

}

MyGCMgr::~MyGCMgr()
{
	for (size_t i = 0; i < m_Entity.size(); ++i)
	{
		if (nullptr != m_Entity[i])
		{
			delete m_Entity[i];
		}
	}
}

void MyGCMgr::tick()
{
	if (m_Entity.size() < 10)
	{
		return;
	}

	for (size_t i = 0; i < m_Entity.size(); ++i)
	{
		if (nullptr != m_Entity[i])
		{
			delete m_Entity[i];
		}
	}

	// 남아있는 벡터 공간 해제
	m_Entity.clear();
}
