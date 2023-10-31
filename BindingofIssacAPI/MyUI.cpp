#include "pch.h"
#include "MyUI.h"

MyUI::MyUI()
	: m_ParentUI(nullptr)
{

}

MyUI::MyUI(const MyUI& _Origin)
	: MyObject(_Origin)
	, m_ParentUI(nullptr)
{
	for (size_t i = 0; i < _Origin.m_vecChildUI.size(); ++i)
	{
		AddChildUI(_Origin.m_vecChildUI[i]->Clone());
	}
}

MyUI::~MyUI()
{
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		delete m_vecChildUI[i];
	}
}

void MyUI::tick(float _DT)
{
	Super::tick(_DT);

	// 최종 좌표 연산하기
	m_vFinalPos = GetPos();

	if (nullptr != m_ParentUI)
	{
		m_vFinalPos += m_ParentUI->GetFinalPos();
	}

	// 자식 UI 들 Tick 호출
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->tick(_DT);
	}
}

void MyUI::render(HDC _dc)
{
	Super::render(_dc);

	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->render(_dc);
	}
}
