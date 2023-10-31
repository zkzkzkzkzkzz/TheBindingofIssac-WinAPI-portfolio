#include "pch.h"
#include "MyLogMgr.h"

#include "MyTimeMgr.h"

MyLogMgr::MyLogMgr() : m_LogMaxLife(5.f)
{

}

MyLogMgr::~MyLogMgr()
{

}

void MyLogMgr::tick(HDC _dc)
{
	list<FLog>::iterator iter = m_LogList.begin();

	for (; iter != m_LogList.end();)
	{
		(*iter).Acctime += DT;

		if (m_LogMaxLife < (*iter).Acctime)
		{
			iter = m_LogList.erase(iter);
		}
		else
		{
			++iter;
		}
	}

	iter = m_LogList.begin();
	POINT LT = { 10 , 10 };

	int i = 0;

	for (; iter != m_LogList.end(); ++iter, ++i)
	{
		switch ((*iter).Level)
		{
		case LOG_LEVEL::LOG:
			SetTextColor(_dc, RGB(0, 0, 0));
			TextOut(_dc, LT.x, LT.y + i * 15, (*iter).Message.c_str(), int((*iter).Message.length()));
			break;

		case LOG_LEVEL::WARNING:
			SetTextColor(_dc, RGB(255, 255, 0));
			break;

		case LOG_LEVEL::ERR:
			SetTextColor(_dc, RGB(255, 0, 0));
			break;

		default:
			break;
		}

		TextOut(_dc, LT.x, LT.y + i * 15, (*iter).Message.c_str(), int((*iter).Message.length()));
	}
}