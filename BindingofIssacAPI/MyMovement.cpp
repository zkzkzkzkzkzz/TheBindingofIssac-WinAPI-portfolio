#include "pch.h"
#include "MyMovement.h"


#include "MyObject.h"

MyMovement::MyMovement(MyObject* _Owner)
	: MyComponent(_Owner)
	, m_Mass(1.f)
	, m_InitSpeed(0.f)
	, m_MaxSpeed(0.f)
	, m_FrictionScale(0.f)
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


	//// 물체에 적용되고있는 힘이 없으면 마찰력을 적용시킨다.
	//if (m_Force.IsZero() && m_Velocity.x != 0.f)
	//{
	//	float fFriction = -m_Velocity.x;
	//	fFriction /= abs(fFriction);

	//	fFriction *= m_FrictionScale;

	//	float fFrictionAccel = (fFriction / m_Mass) * _DT;
	//	if (abs(m_Velocity.x) < abs(fFrictionAccel))
	//	{
	//		m_Velocity = Vec2(0.f, m_Velocity.y);
	//	}
	//	else
	//	{
	//		m_Velocity.x += fFrictionAccel;
	//	}
	//}
	//
	//if (m_Force.IsZero() && m_Velocity.y != 0.f)
	//{
	//	float fFriction = -m_Velocity.y;
	//	fFriction /= abs(fFriction);

	//	fFriction *= m_FrictionScale;

	//	float fFrictionAccel = (fFriction / m_Mass) * _DT;
	//	if (abs(m_Velocity.y) < abs(fFrictionAccel))
	//	{
	//		m_Velocity = Vec2(m_Velocity.x, 0.f);
	//	}
	//	else
	//	{
	//		m_Velocity.y += fFrictionAccel;
	//	}
	//}

	Vec2 vObjPos = GetOwner()->GetPos();
	vObjPos += m_Velocity * _DT;
	GetOwner()->SetPos(vObjPos);

	// 힘 리셋
	m_Force = Vec2(0.f, 0.f);
}