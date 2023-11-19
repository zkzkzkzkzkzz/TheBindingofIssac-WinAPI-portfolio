#include "pch.h"
#include "NMAttack.h"

#include "MyLevelMgr.h"

#include "MyMonster.h"
#include "Pooter.h"
#include "MyMonsterTears.h"

NMAttack::NMAttack()
	: m_pTarget(nullptr)
	, m_PrevDir((int)AttDir::NONE)
{
}

NMAttack::~NMAttack()
{
}


void NMAttack::finaltick(float _DT)
{
	// 플레이어의 위치를 알아낸다.
	Vec2 vPlayerPos = m_pTarget->GetPos();

	// 몬스터 본인의 위치를 알아낸다.
	Pooter* pMonster = dynamic_cast<Pooter*>(GetOwnerSM()->GetOwner());
	if (nullptr == pMonster)
	{
		return;
	}
	Vec2 vMonsterPos = pMonster->GetPos();

	float fDist = vPlayerPos.Distance(vMonsterPos);

	//float* pAttackRange = (float*)GetOwnerSM()->GetDataFromBlackboard(L"Attack Range");
	//float AttackRange = *pAttackRange;

	//if (AttackRange < fDist)
	//{
	//	GetOwnerSM()->ChangeState((UINT)NormalMons_STATE::TRACE);
	//	return;
	//}

	// 플레이어를 추적한다.
	// 1. 몬스터가 이동할 방향을 알아낸다. (플레이어위치 - 몬스터 위치)
	Vec2 vDir = vPlayerPos - vMonsterPos;

	if (vPlayerPos != vMonsterPos)
	{
		// 플레이어가 몬스터보다 왼쪽에 있을 때
		if (vPlayerPos.x < vMonsterPos.x)
		{
			// 아직 눈물을 쏘지 않았을 경우
			if (m_PrevDir == (int)AttDir::NONE)
			{
				pMonster->GetComponent<MyAnimator>()->Play(L"PooterLeftAttackAnim", false);

				m_PrevDir = (int)AttDir::LEFT;

				if (pMonster->GetComponent<MyAnimator>()->GetCurAnim()->IsFinish())
				{
					MyMonsterTears* pTears = new MyMonsterTears;

					Vec2 TearsPos = pMonster->GetPos();
					TearsPos.x -= 4.f;
					TearsPos.y -= 10.f;

					pTears->SetSpeed(250.f);
					pTears->SetScale(Vec2(1.4f, 1.4f));
					pTears->SetOffsetPos(Vec2(-14.f, -15.f));
					pTears->SetPos(TearsPos);

					MyTaskMgr::GetInst()->AddTask(FTask{ TASK_TYPE::CREATE_OBJECT, (UINT_PTR)LAYER::MONSTEARS, (UINT_PTR)pTears });

					pTears->fire();

					GetOwnerSM()->ChangeState((UINT)NormalMons_STATE::TRACE);
					pMonster->GetComponent<MyAnimator>()->FindAnim(L"PooterLeftAttackAnim")->Reset();
					pMonster->SetAccTime(0.f);
				}
			}
			// 한번이라도 눈물을 쏜 경우
			else
			{
				// 이전에도 왼쪽으로 쐈을 경우
				if (m_PrevDir == (int)AttDir::LEFT)
				{
					pMonster->GetComponent<MyAnimator>()->Play(L"PooterLeftAttackAnim", false);

					m_PrevDir = (int)AttDir::LEFT;

					if (pMonster->GetComponent<MyAnimator>()->GetCurAnim()->IsFinish())
					{
						MyMonsterTears* pTears = new MyMonsterTears;

						Vec2 TearsPos = pMonster->GetPos();
						TearsPos.x -= 4.f;
						TearsPos.y -= 10.f;

						pTears->SetSpeed(250.f);
						pTears->SetScale(Vec2(1.4f, 1.4f));
						pTears->SetOffsetPos(Vec2(-14.f, -15.f));
						pTears->SetPos(TearsPos);

						MyTaskMgr::GetInst()->AddTask(FTask{ TASK_TYPE::CREATE_OBJECT, (UINT_PTR)LAYER::MONSTEARS, (UINT_PTR)pTears });

						pTears->fire();

						GetOwnerSM()->ChangeState((UINT)NormalMons_STATE::TRACE);
						pMonster->GetComponent<MyAnimator>()->FindAnim(L"PooterLeftAttackAnim")->Reset();
						pMonster->SetAccTime(0.f);
					}
				}
				// 이전에 오른쪽으로 쐈을 경우
				else if (m_PrevDir == (int)AttDir::RIGHT)
				{
					// 아직 오른쪽 애니메이션 재생 중일 때
					if (!pMonster->GetComponent<MyAnimator>()->GetCurAnim()->IsFinish())
					{
					}
					else
					{
						pMonster->GetComponent<MyAnimator>()->Play(L"PooterLeftAttackAnim", false);

						m_PrevDir = (int)AttDir::LEFT;

						if (pMonster->GetComponent<MyAnimator>()->GetCurAnim()->IsFinish())
						{
							MyMonsterTears* pTears = new MyMonsterTears;

							Vec2 TearsPos = pMonster->GetPos();
							TearsPos.x -= 4.f;
							TearsPos.y -= 10.f;

							pTears->SetSpeed(250.f);
							pTears->SetScale(Vec2(1.4f, 1.4f));
							pTears->SetOffsetPos(Vec2(-14.f, -15.f));
							pTears->SetPos(TearsPos);

							MyTaskMgr::GetInst()->AddTask(FTask{ TASK_TYPE::CREATE_OBJECT, (UINT_PTR)LAYER::MONSTEARS, (UINT_PTR)pTears });

							pTears->fire();

							GetOwnerSM()->ChangeState((UINT)NormalMons_STATE::TRACE);
							pMonster->GetComponent<MyAnimator>()->FindAnim(L"PooterLeftAttackAnim")->Reset();
							pMonster->SetAccTime(0.f);
						}
					}
				}
			}
		}
		// 플레이어가 몬스터보다 오른쪽에 있을 때
		else if (vPlayerPos.x > vMonsterPos.x)
		{
			// 아직 눈물을 쏘지 않았을 경우
			if (m_PrevDir == (int)AttDir::NONE)
			{
				pMonster->GetComponent<MyAnimator>()->Play(L"PooterRightAttackAnim", false);

				m_PrevDir = (int)AttDir::RIGHT;

				if (pMonster->GetComponent<MyAnimator>()->GetCurAnim()->IsFinish())
				{
					MyMonsterTears* pTears = new MyMonsterTears;

					Vec2 TearsPos = pMonster->GetPos();
					TearsPos.x -= 4.f;
					TearsPos.y -= 10.f;

					pTears->SetSpeed(250.f);
					pTears->SetScale(Vec2(1.4f, 1.4f));
					pTears->SetOffsetPos(Vec2(-14.f, -15.f));
					pTears->SetPos(TearsPos);

					MyTaskMgr::GetInst()->AddTask(FTask{ TASK_TYPE::CREATE_OBJECT, (UINT_PTR)LAYER::MONSTEARS, (UINT_PTR)pTears });

					pTears->fire();

					GetOwnerSM()->ChangeState((UINT)NormalMons_STATE::TRACE);
					pMonster->GetComponent<MyAnimator>()->FindAnim(L"PooterRightAttackAnim")->Reset();
					pMonster->SetAccTime(0.f);
				}
			}
			// 한번이라도 눈물을 쏜 경우
			else
			{
				// 이전에도 오른쪽으로 쐈을 경우
				if (m_PrevDir == (int)AttDir::RIGHT)
				{
					pMonster->GetComponent<MyAnimator>()->Play(L"PooterRightAttackAnim", false);

					m_PrevDir = (int)AttDir::RIGHT;

					if (pMonster->GetComponent<MyAnimator>()->GetCurAnim()->IsFinish())
					{
						MyMonsterTears* pTears = new MyMonsterTears;

						Vec2 TearsPos = pMonster->GetPos();
						TearsPos.x -= 4.f;
						TearsPos.y -= 10.f;

						pTears->SetSpeed(250.f);
						pTears->SetScale(Vec2(1.4f, 1.4f));
						pTears->SetOffsetPos(Vec2(-14.f, -15.f));
						pTears->SetPos(TearsPos);

						MyTaskMgr::GetInst()->AddTask(FTask{ TASK_TYPE::CREATE_OBJECT, (UINT_PTR)LAYER::MONSTEARS, (UINT_PTR)pTears });

						pTears->fire();

						GetOwnerSM()->ChangeState((UINT)NormalMons_STATE::TRACE);
						pMonster->GetComponent<MyAnimator>()->FindAnim(L"PooterRightAttackAnim")->Reset();
						pMonster->SetAccTime(0.f);
					}
				}
				// 이전에 왼쪽으로 쐈을 경우
				else if (m_PrevDir == (int)AttDir::LEFT)
				{
					// 아직 왼쪽 애니메이션 재생 중일 때
					if (!pMonster->GetComponent<MyAnimator>()->GetCurAnim()->IsFinish())
					{

					}
					else
					{
						pMonster->GetComponent<MyAnimator>()->Play(L"PooterRightAttackAnim", false);

						m_PrevDir = (int)AttDir::RIGHT;

						if (pMonster->GetComponent<MyAnimator>()->GetCurAnim()->IsFinish())
						{
							MyMonsterTears* pTears = new MyMonsterTears;

							Vec2 TearsPos = pMonster->GetPos();
							TearsPos.x -= 4.f;
							TearsPos.y -= 10.f;

							pTears->SetSpeed(250.f);
							pTears->SetScale(Vec2(1.4f, 1.4f));
							pTears->SetOffsetPos(Vec2(-14.f, -15.f));
							pTears->SetPos(TearsPos);

							MyTaskMgr::GetInst()->AddTask(FTask{ TASK_TYPE::CREATE_OBJECT, (UINT_PTR)LAYER::MONSTEARS, (UINT_PTR)pTears });

							pTears->fire();

							GetOwnerSM()->ChangeState((UINT)NormalMons_STATE::TRACE);
							pMonster->GetComponent<MyAnimator>()->FindAnim(L"PooterRightAttackAnim")->Reset();
							pMonster->SetAccTime(0.f);
						}
					}
				}
			}
		}
	}
}

void NMAttack::Enter()
{
	m_pTarget = dynamic_cast<MyPlayer*>(MyLevelMgr::GetInst()->GetCurLevel()->FindObjectByName(L"Player"));
}

void NMAttack::Exit()
{
}


