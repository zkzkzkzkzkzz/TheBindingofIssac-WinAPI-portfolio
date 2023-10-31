#include "pch.h"
#include "MyAssetMgr.h"

#include "MyPathMgr.h"
#include "MyTexture.h"
#include "MySound.h"


MyAssetMgr::MyAssetMgr()
{

}

MyAssetMgr::~MyAssetMgr()
{
	for (const auto& pair : m_mapTex)
	{
		delete pair.second;
	}

	for (const auto& pair : m_mapSound)
	{
		delete pair.second;
	}
}

MyTexture* MyAssetMgr::LoadTexture(const wstring& _strKey, const wstring& _strRelativePath)
{
	// 입력된 키에 해당하는 텍스쳐가 있는지 확인한다.
	MyTexture* pTexture = FindTexture(_strKey);
	if (nullptr != pTexture)
	{
		// 이미 있는 텍스쳐면 찾은걸 반환해준다.
		return pTexture;
	}

	// 입력된 키에 해당하는 텍스쳐가 없으면 로딩해서 반환해준다.
	wstring strContentPath = MyPathMgr::GetContentPath();
	wstring strFilePath = strContentPath + _strRelativePath;

	pTexture = new MyTexture;

	if (!pTexture->Load(strFilePath))
	{
		// 텍스쳐 로드가 실패한 경우(경로 문제 등등..)
		delete pTexture;
		return nullptr;
	}

	// Asset 에 키값과 경로값을 알려준다.
	pTexture->m_strKey = _strKey;
	pTexture->m_strRelativePath = _strRelativePath;

	m_mapTex.insert(make_pair(_strKey, pTexture));

	return pTexture;
}

MyTexture* MyAssetMgr::CreateTexture(const wstring& _strKey, UINT _width, UINT _height)
{
	// 입력된 키에 해당하는 텍스쳐가 있는지 확인한다.
	MyTexture* pTexture = FindTexture(_strKey);
	if (nullptr != pTexture)
	{
		// 이미 있는 텍스쳐면 찾은걸 반환해준다.
		return pTexture;
	}

	pTexture = new MyTexture;
	pTexture->Create(_width, _height);

	// Asset 에 키값과 경로값을 알려준다.
	pTexture->m_strKey = _strKey;
	m_mapTex.insert(make_pair(_strKey, pTexture));
	return pTexture;
}

MyTexture* MyAssetMgr::FindTexture(const wstring& _strKey)
{
	map<wstring, MyTexture*>::iterator iter = m_mapTex.find(_strKey);

	if (iter == m_mapTex.end())
	{
		return nullptr;
	}

	return iter->second;
}

MySound* MyAssetMgr::LoadSound(const wstring& _strKey, const wstring& _strRelativePath)
{
	// 입력된 키에 해당하는 텍스쳐가 있는지 확인한다.
	MySound* pSound = FindSound(_strKey);
	if (nullptr != pSound)
	{
		// 이미 있는 텍스쳐면 찾은걸 반환해준다.
		return pSound;
	}

	// 입력된 키에 해당하는 텍스쳐가 없으면 로딩해서 반환해준다.
	wstring strContentPath = MyPathMgr::GetContentPath();
	wstring strFilePath = strContentPath + _strRelativePath;

	pSound = new MySound;

	if (!pSound->Load(strFilePath))
	{
		// 텍스쳐 로드가 실패한 경우(경로 문제 등등..)
		delete pSound;
		return nullptr;
	}

	// Asset 에 키값과 경로값을 알려준다.
	pSound->m_strKey = _strKey;
	pSound->m_strRelativePath = _strRelativePath;

	m_mapSound.insert(make_pair(_strKey, pSound));

	return pSound;
}

MySound* MyAssetMgr::FindSound(const wstring& _strKey)
{
	map<wstring, MySound*>::iterator iter = m_mapSound.find(_strKey);

	if (iter == m_mapSound.end())
	{
		return nullptr;
	}

	return iter->second;
}
