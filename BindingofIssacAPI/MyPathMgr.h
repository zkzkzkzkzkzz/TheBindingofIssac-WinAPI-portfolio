#pragma once

class MyPathMgr
{
private:
	static wchar_t g_szContent[255];


public:
	static void init();
	static const wchar_t* GetContentPath() { return g_szContent; }
};