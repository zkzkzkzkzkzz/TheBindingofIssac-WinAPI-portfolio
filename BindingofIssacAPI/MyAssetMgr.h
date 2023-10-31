#pragma once

class MyTexture;
class MySound;

class MyAssetMgr
{
	SINGLETON(MyAssetMgr);
private:
	map<wstring, MyTexture*>	m_mapTex;
	map<wstring, MySound*>	m_mapSound;

public:
	MyTexture* LoadTexture(const wstring& _strKey, const wstring& _strRelativePath);
	MyTexture* CreateTexture(const wstring& _strKey, UINT _width, UINT _height);
	MyTexture* FindTexture(const wstring& _strKey);
	
	MySound* LoadSound(const wstring& _strKey, const wstring& _strRelativePath);
	MySound* FindSound(const wstring& _strKey);

};