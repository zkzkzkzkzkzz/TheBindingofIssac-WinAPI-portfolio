#include "pch.h"
#include "MyEntity.h"

UINT_PTR MyEntity::g_NextID = 0;


MyEntity::MyEntity()
	: m_ID(g_NextID++)
	, m_bDead(false)
{
}

MyEntity::MyEntity(const MyEntity& _other)
	: m_ID(g_NextID++)
	, m_bDead(false)
{
}

MyEntity::~MyEntity()
{
}
