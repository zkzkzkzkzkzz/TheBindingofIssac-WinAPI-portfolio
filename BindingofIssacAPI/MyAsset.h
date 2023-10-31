#pragma once
#include "MyEntity.h"

class MyAsset :
    public MyEntity
{
private:
    wstring     m_strKey;
    wstring     m_strRelativePath;


public:
    const wstring& GetKey() { return m_strKey; }
    const wstring& GetRelativePath() { return m_strRelativePath; }

private:
    virtual bool Load(const wstring& _strFilePath) = 0;

public:
    CLONE_DISABLE(MyAsset);
    MyAsset();
    MyAsset(const MyAsset& _Origin) = delete;
    ~MyAsset();

    friend class MyAssetMgr;
};

