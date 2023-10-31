#include "pch.h"
#include "MyTexture.h"

#include "MyEngine.h"

MyTexture::MyTexture()
	: m_hBit(nullptr)
	, m_hDC(nullptr)
	, m_Info{}
{
}

MyTexture::~MyTexture()
{
	DeleteObject(m_hBit);
	DeleteDC(m_hDC);
}

bool MyTexture::Load(const wstring& _strFilePath)
{
	wchar_t szExt[20] = {};
	_wsplitpath_s(_strFilePath.c_str(), nullptr, 0, nullptr, 0, nullptr, 0, szExt, 20);

	if (!wcscmp(szExt, L".bmp") || !wcscmp(szExt, L".BMP"))
	{
		// 플레이어가 사용할 이미지 비트맵 로딩
		m_hBit = (HBITMAP)LoadImage(nullptr, _strFilePath.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		if (nullptr == m_hBit)
		{
			return false;
		}
	}

	else if (!wcscmp(szExt, L".png") || !wcscmp(szExt, L".PNG"))
	{
		ULONG_PTR gdiplusToken = 0;
		GdiplusStartupInput gidstartupInput = {};
		GdiplusStartup(&gdiplusToken, &gidstartupInput, nullptr);
		Image* pImg = Image::FromFile(_strFilePath.c_str(), false);

		Bitmap* pBitmap = (Bitmap*)pImg->Clone();
		Status stat = pBitmap->GetHBITMAP(Color(0, 0, 0, 0), &m_hBit);

		if (Status::Ok != stat)
			return false;
	}

	m_hDC = CreateCompatibleDC(MyEngine::GetInst()->GetMainDC());
	DeleteObject(SelectObject(m_hDC, m_hBit));
	GetObject(m_hBit, sizeof(BITMAP), &m_Info);

	return true;
}

void MyTexture::Create(UINT _Width, UINT Height)
{
	m_hBit = CreateCompatibleBitmap(MyEngine::GetInst()->GetMainDC(), _Width, Height);
	m_hDC = CreateCompatibleDC(MyEngine::GetInst()->GetMainDC());

	m_hDC = CreateCompatibleDC(MyEngine::GetInst()->GetMainDC());
	DeleteObject(SelectObject(m_hDC, m_hBit));
	GetObject(m_hBit, sizeof(BITMAP), &m_Info);
}