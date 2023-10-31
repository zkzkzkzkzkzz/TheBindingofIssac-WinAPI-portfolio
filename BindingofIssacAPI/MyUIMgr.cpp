#include "pch.h"
#include "MyUIMgr.h"

#include "MyKeyMgr.h"

#include "MyLevelMgr.h"
#include "MyLevel.h"
#include "MyLayer.h"
#include "MyUI.h"
		  
#include "MyLogMgr.h"

MyUIMgr::MyUIMgr()
	: m_FocuedUI(nullptr)
{

}

MyUIMgr::~MyUIMgr()
{

}

void MyUIMgr::tick()
{
	Vec2 vMousePos = MyKeyMgr::GetInst()->GetMousePos();
	bool bLBtnTap = KEY_TAP(LBTN);
	bool bLbtnReleased = KEY_RELEASED(LBTN);

	MyLevel* pLevel = MyLevelMgr::GetInst()->GetCurLevel();
	if (nullptr == pLevel)
		return;

	// UILayer 가져오기
	MyLayer* pUILayer = pLevel->GetLayer((int)LAYER::UI);
	vector<MyObject*>& vecUI = pUILayer->m_vecObjects;
	vector<MyObject*>::reverse_iterator iter = vecUI.rbegin();


	for (iter; iter != vecUI.rend(); ++iter)
	{
		MyUI* pUI = dynamic_cast<MyUI*>(*iter);
		if (nullptr == pUI)
		{
			LOG(ERR, L"UI Layer 에 UI 가 아닌 오브젝트가 들어 있음");
			continue;
		}

		if (pUI->m_bMouseOn)
		{
			m_FocuedUI = pUI;

			pUI = GetPriorityCheck(pUI);

			if (pUI->m_bMouseOn_Prev != pUI->m_bMouseOn)
			{
				pUI->OnHovered(vMousePos);
			}
			else
			{
				pUI->MouseOn(vMousePos);
			}

			if (bLbtnReleased)
			{
				pUI->LBtnUp(vMousePos);

				if (pUI->m_bMouseLBtnDown)
				{
					pUI->LBtnClicked(vMousePos);
				}
			}

			if (bLBtnTap)
			{
				pUI->LBtnDown(vMousePos);
				pUI->m_bMouseLBtnDown = true;

				// reverse iterator 로 vector 내에서 erase 하기
				std::advance(iter, 1);
				vecUI.erase(iter.base());

				vecUI.push_back(m_FocuedUI);
			}

			if (bLbtnReleased)
			{
				pUI->m_bMouseLBtnDown = false;
			}

			break;
		}
		else
		{
			if (pUI->m_bMouseOn_Prev != pUI->m_bMouseOn)
			{
				pUI->OnUnHovered(vMousePos);
			}

			if (bLbtnReleased)
			{
				pUI->m_bMouseLBtnDown = false;
			}
		}
	}
}

MyUI* MyUIMgr::GetPriorityCheck(MyUI* _ParentUI)
{
	MyUI* pPriorityUI = nullptr;

	static list<MyUI*> queue;
	queue.clear();

	queue.push_back(_ParentUI);

	while (!queue.empty())
	{
		MyUI* pUI = queue.front();
		queue.pop_front();

		for (size_t i = 0; i < pUI->m_vecChildUI.size(); ++i)
		{
			queue.push_back(pUI->m_vecChildUI[i]);
		}

		if (pUI->m_bMouseOn)
		{
			pPriorityUI = pUI;
		}
	}

	return pPriorityUI;
}