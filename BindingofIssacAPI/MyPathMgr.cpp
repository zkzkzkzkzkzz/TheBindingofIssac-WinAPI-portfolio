#include "pch.h"
#include "MyPathMgr.h"


wchar_t MyPathMgr::g_szContent[255] = {};


void MyPathMgr::init()
{
	// 실행파일 경로
	GetCurrentDirectory(255, g_szContent);

	// MessageBox(nullptr, g_szContent, L"Current Directory Check", MB_OK);

	size_t Len = wcslen(g_szContent);

	for (size_t i = Len - 1; i >= 0; --i)
	{
		if ('\\' == g_szContent[i])
		{
			g_szContent[i + 1] = '\0';
			break;
		}
	}

	wcscat_s(g_szContent, 255, L"content\\");
}