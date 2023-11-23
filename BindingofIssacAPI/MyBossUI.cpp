#include "pch.h"
#include "MyBossUI.h"

#include "MyAssetMgr.h"
#include "BossMonster.h"
#include "components.h"

MyBossUI::MyBossUI()
	: m_Animator(nullptr)
	, m_BossHP(11)
	, m_IsUIRender(true)
{
	m_Animator = AddComponent<MyAnimator>(L"BossHPAnimator");
	m_Animator->LoadAnimation(L"animdata\\BossHPAnim01.txt");
	m_Animator->LoadAnimation(L"animdata\\BossHPAnim02.txt");
	m_Animator->LoadAnimation(L"animdata\\BossHPAnim03.txt");
	m_Animator->LoadAnimation(L"animdata\\BossHPAnim04.txt");
	m_Animator->LoadAnimation(L"animdata\\BossHPAnim05.txt");
	m_Animator->LoadAnimation(L"animdata\\BossHPAnim06.txt");
	m_Animator->LoadAnimation(L"animdata\\BossHPAnim07.txt");
	m_Animator->LoadAnimation(L"animdata\\BossHPAnim08.txt");
	m_Animator->LoadAnimation(L"animdata\\BossHPAnim09.txt");
	m_Animator->LoadAnimation(L"animdata\\BossHPAnim10.txt");
}

MyBossUI::~MyBossUI()
{

}

void MyBossUI::tick(float _DT)
{
	if (m_IsUIRender)
	{
		Super::tick(_DT);

		m_BossHP = GetBossHP();

		if (m_BossHP == 10)
		{
			m_Animator->Play(L"BossHPAnim01", false);
		}
		else if (m_BossHP == 9)
		{
			m_Animator->Play(L"BossHPAnim02", false);
		}
		else if (m_BossHP == 8)
		{
			m_Animator->Play(L"BossHPAnim03", false);
		}
		else if (m_BossHP == 7)
		{
			m_Animator->Play(L"BossHPAnim04", false);
		}
		else if (m_BossHP == 6)
		{
			m_Animator->Play(L"BossHPAnim05", false);
		}
		else if (m_BossHP == 5)
		{
			m_Animator->Play(L"BossHPAnim06", false);
		}
		else if (m_BossHP == 4)
		{
			m_Animator->Play(L"BossHPAnim07", false);
		}
		else if (m_BossHP == 3)
		{
			m_Animator->Play(L"BossHPAnim08", false);
		}
		else if (m_BossHP == 2)
		{
			m_Animator->Play(L"BossHPAnim09", false);
		}
		else if (m_BossHP == 1)
		{
			m_Animator->Play(L"BossHPAnim10", false);
		}
		else
		{
			m_Animator->Play(L"BossHPAnim10", false);
			m_IsUIRender = false;
			Destroy();
		}
	}
}

void MyBossUI::render(HDC _dc)
{
	if (m_IsUIRender)
	{
		Super::render(_dc);
	}
}

