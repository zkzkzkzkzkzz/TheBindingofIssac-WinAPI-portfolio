#pragma once


class MyLogMgr
{
	SINGLETON(MyLogMgr);

private:
	list<FLog>	m_LogList;

	// 로그가 출력될 수 있는 최대 시간
	float		m_LogMaxLife;

public:
	void SetLogMaxLife(float _LogMaxLife) { m_LogMaxLife = _LogMaxLife; }
	void AddLog(const FLog& _log) { m_LogList.push_front(_log); }

public:
	void tick(HDC _dc);
};


#define LOG(Level, Message)		{\
									string funcname = __FUNCTION__;\
									wchar_t szBuffer[100] = {};\
									swprintf_s(szBuffer, L"Function : %s { Line : %d } : %s",\
									wstring(funcname.begin(), funcname.end()).c_str(), __LINE__,\
									Message);\
									MyLogMgr::GetInst()->AddLog(FLog{LOG_LEVEL::Level, szBuffer});\
								}