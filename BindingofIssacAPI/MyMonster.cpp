#include "pch.h"
#include "MyMonster.h"

#include "MyAssetMgr.h"
#include "MySpawnEffect.h"
#include "components.h"

MyMonster::MyMonster()
	: IsBoss(false)
	, m_IsDead(false)
	, m_Animator(nullptr)
	, m_Atlas(nullptr)
	, m_fDuration(10000.f)
	
{
}

MyMonster::MyMonster(const MyMonster& _Origin)
	: MyObject(_Origin)
	, IsBoss(false)
	, m_IsDead(false)
	, m_Animator(nullptr)
	, m_Atlas(_Origin.m_Atlas)
{
	m_Animator = GetComponent<MyAnimator>();
}

MyMonster::~MyMonster()
{
}


void MyMonster::SetToInitPos()
{
	MySpawnEffect* pSpawn = new MySpawnEffect;
	pSpawn->SetPos(m_vInitPos);
	pSpawn->SetScale(Vec2(2.f, 2.f));
	pSpawn->SetOffsetPos(Vec2(-30.f, -40.f));
	MyTaskMgr::GetInst()->AddTask(FTask{ TASK_TYPE::CREATE_OBJECT, (UINT_PTR)LAYER::EFFECT, (UINT_PTR)pSpawn });
	m_fDuration = m_AccTime + 0.3f;
	
}

void MyMonster::begin()
{
}

void MyMonster::tick(float _DT)
{
	if (m_IsDead == true)
	{
		return;
	}
	m_AccTime += _DT;
	if (m_fDuration <= m_AccTime) {
		SetPos(m_vInitPos);
		m_fDuration = 10000.f;
	}
	Super::tick(_DT);
}

void MyMonster::render(HDC _dc)
{
	if (m_IsDead == true)
	{
		return;
	}
	Super::render(_dc);
}

void MyMonster::BeginOverlap(MyCollider* _OwnCol, MyObject* _OtherObj, MyCollider* _OtherCol)
{
	//Destroy();
}

