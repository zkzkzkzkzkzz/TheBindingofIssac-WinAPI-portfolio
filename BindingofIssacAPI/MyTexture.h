#pragma once
#include "MyAsset.h"


class MyTexture :
    public MyAsset
{
private:
    HBITMAP     m_hBit;
    HDC         m_hDC;
    BITMAP      m_Info;

public:
    HDC GetDC() { return m_hDC; }
    HBITMAP GetBitmap() { return m_hBit; }
    UINT GetWidth() { return m_Info.bmWidth; }
    UINT GetHeight() { return m_Info.bmHeight; }

private:
    virtual bool Load(const wstring& _strFilePath) override;

    void Create(UINT _Width, UINT Height);

private:
    MyTexture();
    ~MyTexture();

    friend class MyAssetMgr;
};

