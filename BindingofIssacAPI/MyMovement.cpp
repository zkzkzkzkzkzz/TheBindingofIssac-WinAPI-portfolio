#include "pch.h"
#include "MyMovement.h"


#include "MyObject.h"

MyMovement::MyMovement(MyObject* _Owner)
	: MyComponent(_Owner)
	, m_Mass(1.f)
	, m_InitSpeed(0.f)
	, m_MaxSpeed(0.f)
	, m_FrictionScale(0.f)
	, m_Gravity(0.f)
	, m_UsingGravity(false)
	, m_RotateSpeed(PI)
{

}

MyMovement::~MyMovement()
{

}

void MyMovement::finaltick(float _DT)
{
	m_Accel = m_Force / m_Mass;

	// 정지에 가까운 상태일 경우
	if (m_Velocity.Length() < 0.1f)
	{
		if (!m_Accel.IsZero())
		{
			Vec2 vAccelDir = m_Accel;
			vAccelDir.Normalize();
			m_Velocity = vAccelDir;
		}
	}
	else
	{
		m_Velocity += m_Accel * _DT;
	}

	// 최대 속도 제한
	if (abs(m_Velocity.x) >= m_MaxSpeed)
	{
		m_Velocity.x = (m_Velocity.x / abs(m_Velocity.x)) * m_MaxSpeed;

		if (abs(m_Velocity.x) + abs(m_Velocity.y) >= m_MaxSpeed)
		{
			m_Velocity.Normalize();
			m_Velocity *= m_MaxSpeed;
		}
	}
	if (abs(m_Velocity.y) >= m_MaxSpeed)
	{
		m_Velocity.y = (m_Velocity.y / abs(m_Velocity.y)) * m_MaxSpeed;

		if (abs(m_Velocity.x) + abs(m_Velocity.y) >= m_MaxSpeed)
		{
			m_Velocity.Normalize();
			m_Velocity *= m_MaxSpeed;
		}
	}


	float fFrictionX = -m_Velocity.x;
	if (fFrictionX != 0.f)
	{
		fFrictionX /= abs(fFrictionX);

		fFrictionX *= m_FrictionScale;

		float fFrictionAccelX = (fFrictionX / m_Mass) * _DT;
		if (abs(m_Velocity.x) < abs(fFrictionAccelX))
		{
			m_Velocity = Vec2(0.f, m_Velocity.y);
		}
		else
		{
			m_Velocity.x += fFrictionAccelX;
		}
	}

	float fFrictionY = -m_Velocity.y;
	if (fFrictionY != 0.f)
	{
		fFrictionY /= abs(fFrictionY);

		fFrictionY *= m_FrictionScale;

		float fFrictionAccelY = (fFrictionY / m_Mass) * _DT;
		if (abs(m_Velocity.y) < abs(fFrictionAccelY))
		{
			m_Velocity = Vec2(m_Velocity.x, 0.f);
		}
		else
		{
			m_Velocity.y += fFrictionAccelY;
		}
	}

	m_Gravity = GetGravity();

	if (m_UsingGravity)
	{
		Vec2 vDir = Rotate(Vec2(0.f, m_Gravity), m_RotateSpeed * _DT);

		m_Velocity.y += vDir.y;
	}

	Vec2 vObjPos = GetOwner()->GetPos();
	vObjPos += m_Velocity * _DT;
	GetOwner()->SetPos(vObjPos);

	// 힘 리셋
	m_Force = Vec2(0.f, 0.f);
}
