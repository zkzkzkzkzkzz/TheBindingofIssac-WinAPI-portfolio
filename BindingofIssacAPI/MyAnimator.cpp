#include "pch.h"
#include "MyAnimator.h"

#include "MyPathMgr.h"
#include "MyAnim.h"
		  
#include "MyLogMgr.h"


MyAnimator::MyAnimator(MyObject* _Owner)
	: MyComponent(_Owner)
	, m_CurAnim(nullptr)
	, m_bRepeat(false)
{
}

MyAnimator::MyAnimator(const MyAnimator& _Origin)
	: MyComponent(_Origin)
	, m_CurAnim(nullptr)
	, m_bRepeat(_Origin.m_bRepeat)
{
	for (const auto& pair : _Origin.m_mapAnim)
	{
		MyAnim* pAnim = pair.second->Clone();
		pAnim->m_pAnimator = this;
		m_mapAnim.insert(make_pair(pair.first, pAnim));
	}

	if (nullptr != _Origin.m_CurAnim)
	{
		m_CurAnim = FindAnim(_Origin.m_CurAnim->GetName());
	}
}

MyAnimator::~MyAnimator()
{
	for (const auto& pair : m_mapAnim)
	{
		delete pair.second;
	}
}

void MyAnimator::finaltick(float _DT)
{
	if (IsValid(m_CurAnim))
	{
		if (m_bRepeat && m_CurAnim->IsFinish())
		{
			m_CurAnim->Reset();
		}

		m_CurAnim->finaltick();
	}
}

void MyAnimator::render(HDC _dc)
{
	if (IsValid(m_CurAnim))
	{
		m_CurAnim->render(_dc);
	}
}

void MyAnimator::Play(const wstring& _strName, bool _bRepeat)
{
	m_bRepeat = _bRepeat;
	m_CurAnim = FindAnim(_strName);
    //m_CurAnim->Reset();
}

void MyAnimator::Stop()
{
}

MyAnim* MyAnimator::FindAnim(const wstring& _strName)
{
	map<wstring, MyAnim*>::iterator iter = m_mapAnim.find(_strName);

	if (iter == m_mapAnim.end())
	{
		return nullptr;
	}

	return iter->second;
}

void MyAnimator::CreateAnimation(const wstring& _strName, MyTexture* _Altas,
	Vec2 _vLeftTop, Vec2 _vCutSize, Vec2 _vOffset, float _Duration, int _MaxFrm)
{
	MyAnim* pAnim = FindAnim(_strName);
	if (IsValid(pAnim))
	{
		return;
	}

	pAnim = new MyAnim;
	pAnim->m_pAnimator = this;
	pAnim->Create(_strName, _Altas, _vLeftTop, _vCutSize, _vOffset, _Duration, _MaxFrm);
	m_mapAnim.insert(make_pair(_strName, pAnim));
}

void MyAnimator::SaveAnimations(const wstring& _strRelativePath)
{
	wstring strFolderPath = MyPathMgr::GetContentPath();
	strFolderPath += _strRelativePath;

	for (const auto& pair : m_mapAnim)
	{
		wstring strFilePath = strFolderPath + L"\\" + pair.first + L".txt";
		if (!pair.second->Save(strFilePath))
		{
			LOG(ERR, L"Animation Save 실패");
		}
	}
}

void MyAnimator::LoadAnimation(const wstring& _strRelativePath)
{
	wstring strFilePath = MyPathMgr::GetContentPath();
	strFilePath += _strRelativePath;

	MyAnim* pNewAnim = new MyAnim;

	if (!pNewAnim->Load(strFilePath))
	{
		LOG(ERR, L"Animation Load 실패");
		delete pNewAnim;
		return;
	}

	pNewAnim->m_pAnimator = this;
	m_mapAnim.insert(make_pair(pNewAnim->GetName(), pNewAnim));
}


