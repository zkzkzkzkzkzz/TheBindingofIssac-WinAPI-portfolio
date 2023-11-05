#include "pch.h"
#include "MyCameraMgr.h"

#include "MyEngine.h"
#include "MyKeyMgr.h"
#include "MyTimeMgr.h"
		  
#include "MyAssetMgr.h"
#include "MyTexture.h"


MyCameraMgr::MyCameraMgr()
	: m_Veil(nullptr)
	, m_Alpha(0.f)
	, m_fSpeed(13000.f)
	, m_CurSpeed(0.f)
	, damping(0.97f)
	, dampingCount(0)
{
	Vec2 vResol = MyEngine::GetInst()->GetResolution();
	m_Veil = MyAssetMgr::GetInst()->CreateTexture(L"VeilTex", vResol.x, vResol.y);
}

MyCameraMgr::~MyCameraMgr()
{
}

void MyCameraMgr::tick()
{
	if (KEY_PRESSED(J))
	{
		m_vLookAt.x -= 960.f * DT;
	}

	if (KEY_PRESSED(L))
	{
		m_vLookAt.x += 960.f * DT;
	}

	if (KEY_PRESSED(I))
	{
		m_vLookAt.y -= 960.f * DT;
	}

	if (KEY_PRESSED(K))
	{
		m_vLookAt.y += 960.f * DT;
	}

	// 화면 해상도의 중심위치를 알아낸다.
	Vec2 vResolution = MyEngine::GetInst()->GetResolution();
	Vec2 vCenter = vResolution / 2.f;

	// 해상도 중심과, 카메라가 현재 보고있는 좌표의 차이값을 구한다.
	m_vDiff = m_vLookAt - vCenter;

	// 카메라 이벤트가 없으면 리턴
	if (m_EventList.empty())
	{
		return;
	}

	// 카메라 이벤트가 존재한다면
	FCamEvent& evnt = m_EventList.front();

	if (evnt.Type == CAM_EFFECT::FADE_IN)
	{
		evnt.AccTime += DT;

		if (evnt.Duration <= evnt.AccTime)
		{
			m_Alpha = 0;
			m_EventList.pop_front();
		}
		else
		{
			float fRatio = evnt.AccTime / evnt.Duration;
			float alpha = 1.f - fRatio;
			m_Alpha = (UINT)(alpha * 255);
		}
	}

	else if (evnt.Type == CAM_EFFECT::FADE_OUT)
	{
		evnt.AccTime += DT;

		if (evnt.Duration <= evnt.AccTime)
		{
			m_EventList.pop_front();
			m_Alpha = 255;
		}
		else
		{
			float fRatio = evnt.AccTime / evnt.Duration;
			float alpha = fRatio;
			m_Alpha = (UINT)(alpha * 255);
		}
	}

	else if (evnt.Type == CAM_EFFECT::SCROLLDOWN)
	{
		evnt.AccTime += DT;

		float BtwTime = evnt.Duration - evnt.AccTime;

		if (m_vLookAt.y >= 960.f)
		{
			SetLookAt(Vec2(480.f, 960.f));
		}

		if (BtwTime <= 0.f)
		{
			SetLookAt(Vec2(480.f, 960.f));
			m_EventList.pop_front();
		}
		else if (BtwTime > 0.3f)
		{
			m_vLookAt.y += 7000.f * DT * BtwTime;

			if (m_vLookAt.y >= 960.f)
			{
				SetLookAt(Vec2(480.f, 960.f));
			}
		}
		else if (BtwTime > 0.f && BtwTime <= 0.3f)
		{
			m_vLookAt.y += 100.f * DT * BtwTime;

			if (m_vLookAt.y >= 960.f)
			{
				SetLookAt(Vec2(480.f, 960.f));
			}
 		}
	}

	else if (evnt.Type == CAM_EFFECT::SCROLLUP)
	{
		evnt.AccTime += DT;

		float BtwTime = evnt.Duration - evnt.AccTime;

		if (m_vLookAt.y <= 320.f)
		{
			SetLookAt(Vec2(480.f, 320.f));
		}

		if (BtwTime <= 0.f)
		{
			SetLookAt(Vec2(480.f, 320.f));
			m_EventList.pop_front();
		}
		else if (BtwTime > 0.3f)
		{
			m_vLookAt.y -= 7000.f * DT * BtwTime;

			if (m_vLookAt.y <= 320.f)
			{
				SetLookAt(Vec2(480.f, 320.f));
			}
		}
		else if (BtwTime > 0.f && BtwTime <= 0.3f)
		{
			m_vLookAt.y -= 100.f * DT * BtwTime;

			if (m_vLookAt.y <= 320.f)
			{
				SetLookAt(Vec2(480.f, 320.f));
			}
		}
	}

}

void MyCameraMgr::render(HDC _dc)
{
	if (0 == m_Alpha)
	{
		return;
	}

	BLENDFUNCTION blend = {};
	blend.BlendOp = AC_SRC_OVER;
	blend.BlendFlags = 0;

	blend.SourceConstantAlpha = m_Alpha; // 0 ~ 255
	blend.AlphaFormat = 0; // 0

	AlphaBlend(_dc
		, 0, 0, m_Veil->GetWidth(), m_Veil->GetHeight()
		, m_Veil->GetDC()
		, 0, 0
		, m_Veil->GetWidth(), m_Veil->GetHeight()
		, blend);
}