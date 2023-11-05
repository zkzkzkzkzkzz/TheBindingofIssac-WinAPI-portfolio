#include "pch.h"
#include "MyIssacIdle.h"

#include "MyAssetMgr.h"
#include "MyAnimator.h"

MyIssacIdle::MyIssacIdle()
	: m_pTarget(nullptr)
{
}

MyIssacIdle::~MyIssacIdle()
{
}

void MyIssacIdle::finaltick(float _DT)
{
	if (nullptr == m_pTarget)
	{
		return;
	}

}

void MyIssacIdle::Enter()
{
	m_pTarget = dynamic_cast<MyPlayer*>(MyLevelMgr::GetInst()->GetCurLevel()->FindObjectByName(L"Player"));

	MyAnimator* pAnimator = m_pTarget->GetComponent<MyAnimator>();
}

void MyIssacIdle::Exit()
{
}



