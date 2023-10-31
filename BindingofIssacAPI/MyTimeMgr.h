#pragma once


class MyTimeMgr
{
	SINGLETON(MyTimeMgr);

private:
	// LARGE_INTEGER는 그냥 8바이트 long long 취급
	LARGE_INTEGER	m_Frequency;
	LARGE_INTEGER	m_PrevCount;
	LARGE_INTEGER	m_CurCount;

	// 델타타임 = 현재 프레임과 이전 프레임의 시간값 차이
	float			m_DeltaTime;

	UINT			m_FPSTime;
	float			m_CurTime;
	int				m_RealTime;

public:
	float GetDeltaTime() { return m_DeltaTime; }

public:
	void init();
	void tick();
};