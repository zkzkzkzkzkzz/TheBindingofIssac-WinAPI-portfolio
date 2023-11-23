#include "pch.h"
#include "MyTimeMgr.h"

#include "MyEngine.h"

MyTimeMgr::MyTimeMgr()
	: m_Frequency{}
	, m_PrevCount{}
	, m_CurCount{}
	, m_CurTime(0.f)
	, m_RealTime(0)
{

}

MyTimeMgr::~MyTimeMgr()
{

}

void MyTimeMgr::init()
{
	// 성능 카운터의 빈도를 검색한다(해당 타이머가 초당 몇 번의 주기를 완료하는가)
	// 인자로 LARGE_INTEGER 구조체 변수의 포인터를 가진다
	QueryPerformanceFrequency(&m_Frequency);

	// 시간 간격 측정
	QueryPerformanceCounter(&m_PrevCount);
}

void MyTimeMgr::tick()
{
	QueryPerformanceCounter(&m_CurCount);

	// 컴퓨터의 성능과 상관없이 1초동안 동일한 작업을 해야한다
	m_DeltaTime = float(m_CurCount.QuadPart - m_PrevCount.QuadPart) / float(m_Frequency.QuadPart);

	m_PrevCount = m_CurCount;

	m_CurTime += m_DeltaTime;

	// 델타타임을 누적시켜 1초가 지났을 때 if구문 실행
	if (1.f <= m_CurTime)
	{
		//wchar_t szText[100] = {};
		//swprintf_s(szText, 100, L"DeltaTime : %f, FPS : %d , Real Time : %d", m_DeltaTime, m_FPSTime, m_RealTime);
		//SetWindowText(MyEngine::GetInst()->GetMainWind(), szText);

		m_FPSTime = 0;
		m_CurTime = 0.f;
		m_RealTime += 1;
	}

	++m_FPSTime;
}
