#include "pch.h"
#include "NMIdle.h"

#include "MyLevelMgr.h"

#include "MyMonster.h"

NMIdle::NMIdle()
{
}

NMIdle::~NMIdle()
{
}

void NMIdle::finaltick(float _DT)
{
	if (nullptr == m_pTarget)
	{
		return;
	}

	float* pDetectRange = (float*)GetOwnerSM()->GetDataFromBlackboard(L"Detect Range");
	float DetectRange = *pDetectRange;

	Vec2 vPlayerPos = m_pTarget->GetPos();
	MyMonster* pMonster = dynamic_cast<MyMonster*>(GetOwnerSM()->GetOwner());
	if (nullptr == pMonster)
		return;

	Vec2 vMonsterPos = pMonster->GetPos();

	float fDist = vPlayerPos.Distance(vMonsterPos);

	if (fDist < DetectRange)
	{
		GetOwnerSM()->ChangeState((UINT)NormalMons_STATE::TRACE);
	}
}

void NMIdle::Enter()
{
	m_pTarget = dynamic_cast<MyPlayer*>(MyLevelMgr::GetInst()->GetCurLevel()->FindObjectByName(L"Player"));
}

void NMIdle::Exit()
{
}
