#include "pch.h"
#include "MyMonster.h"

#include "components.h"

MyMonster::MyMonster()
	: IsBoss(false)
	, m_MonsterCount(0)
	, m_Animator(nullptr)
	, m_Atlas(nullptr)
{
	++m_MonsterCount;
}

MyMonster::MyMonster(const MyMonster& _Origin)
	: MyObject(_Origin)
	, IsBoss(false)
	, m_MonsterCount(0)
	, m_Animator(nullptr)
	, m_Atlas(_Origin.m_Atlas)
{
	++m_MonsterCount;
}

MyMonster::~MyMonster()
{
	m_Animator = GetComponent<MyAnimator>();
}


void MyMonster::begin()
{
}

void MyMonster::tick(float _DT)
{
	Super::tick(_DT);
}

void MyMonster::render(HDC _dc)
{
	Super::render(_dc);
}

void MyMonster::BeginOverlap(MyCollider* _OwnCol, MyObject* _OtherObj, MyCollider* _OtherCol)
{
	--m_MonsterCount;
	Destroy();
}

