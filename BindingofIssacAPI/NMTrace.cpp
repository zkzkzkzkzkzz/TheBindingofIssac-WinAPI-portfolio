#include "pch.h"
#include "NMTrace.h"

#include "MyLevelMgr.h"

#include "MyMonster.h"
#include "Pooter.h"
#include "NormalFly.h"

NMTrace::NMTrace()
{
}

NMTrace::~NMTrace()
{
}


void NMTrace::finaltick(float _DT)
{
	// 플레이어의 위치를 알아낸다.
	Vec2 vPlayerPos = m_pTarget->GetPos();

	// 몬스터 본인의 위치를 알아낸다.
	MyMonster* pMonster = dynamic_cast<MyMonster*>(GetOwnerSM()->GetOwner());
	if (nullptr == pMonster)
	{
		return;
	}
	Vec2 vMonsterPos = pMonster->GetPos();


	// 플레이어가 탐지범위를 벗어나면 Idle 상태로 돌아간다.
	// 1. 블랙보드에서 몬스터의 탐지범위를 꺼내온다.
	float* pDetectRange = (float*)GetOwnerSM()->GetDataFromBlackboard(L"Detect Range");
	float DetectRange = *pDetectRange;

	// 2. 플레이어와 몬스터의 거리를 구한다.
	float fDist = vPlayerPos.Distance(vMonsterPos);

	// 3. 플레이어와 몬스터의 거리가 탐지범위 이상이면 Idle 상태로 변경한다.
	if (DetectRange < fDist)
	{
		GetOwnerSM()->ChangeState((UINT)NormalMons_STATE::IDLE);
		return;
	}

	Vec2 vDir = vPlayerPos - vMonsterPos;

	if (Pooter* pPooter = dynamic_cast<Pooter*>(GetOwnerSM()->GetOwner()))
	{	
		float fAcc = pPooter->GetAccTime();
		float fDelay = pPooter->GetAttDelayTime();

		float* pAttackRange = (float*)GetOwnerSM()->GetDataFromBlackboard(L"Attack Range");
		float AttackRange = *pAttackRange;
		// 플레이어가 공격범위 이내로 들어오면 Attack 상태로 변경한다.
		if (AttackRange > fDist && fDelay <= fAcc)
		{
			GetOwnerSM()->ChangeState((UINT)NormalMons_STATE::ATTACK);
			return;
		}

		if (vPlayerPos != vMonsterPos)
		{
			vDir.Normalize();

			// 2. 본인(몬스터) 의 이동속도를 알아낸다.
			float* pSpeed = (float*)GetOwnerSM()->GetDataFromBlackboard(L"Speed");
			float fSpeed = *pSpeed;

			// 3. 플레이어를 향해서 이동한다.
			vMonsterPos += vDir * fSpeed * _DT;
			pMonster->SetPos(vMonsterPos);

			if (vPlayerPos.x <= vMonsterPos.x)
			{
				pMonster->GetComponent<MyAnimator>()->Play(L"PooterLeftAnim", true);
			}
			else if (vPlayerPos.x > vMonsterPos.x)
			{
				pMonster->GetComponent<MyAnimator>()->Play(L"PooterRightAnim", true);
			}
		}
	}
	else if (NormalFly* pFly = dynamic_cast<NormalFly*>(GetOwnerSM()->GetOwner()))
	{

		if (vPlayerPos != vMonsterPos)
		{
			vDir.Normalize();

			// 2. 본인(몬스터) 의 이동속도를 알아낸다.
			float* pSpeed = (float*)GetOwnerSM()->GetDataFromBlackboard(L"Speed");
			float fSpeed = *pSpeed;

			// 3. 플레이어를 향해서 이동한다.
			vMonsterPos += vDir * fSpeed * _DT;
			pMonster->SetPos(vMonsterPos);

			pMonster->GetComponent<MyAnimator>()->Play(L"NormalFlyAnim", true);
		}
	}
}

void NMTrace::Enter()
{
	m_pTarget = dynamic_cast<MyPlayer*>(MyLevelMgr::GetInst()->GetCurLevel()->FindObjectByName(L"Player"));
}

void NMTrace::Exit()
{
}


