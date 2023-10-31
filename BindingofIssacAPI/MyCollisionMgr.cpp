#include "pch.h"
#include "MyCollisionMgr.h"

#include "MyLevelMgr.h"
#include "MyLevel.h"
#include "MyObject.h"
#include "MyCollider.h"

MyCollisionMgr::MyCollisionMgr() : m_LayerCheck{}
{

}

MyCollisionMgr::~MyCollisionMgr()
{

}

void MyCollisionMgr::tick()
{
	for (UINT iRow = 0; iRow < 32; ++iRow)
	{
		for (UINT iCol = iRow; iCol < 32; ++iCol)
		{
			if (!(m_LayerCheck[iRow] & (1 << iCol)))
			{
				continue;
			}

			CollisionBtwLayer((LAYER)iRow, (LAYER)iCol);
		}
	}
}

void MyCollisionMgr::CheckCollision(LAYER _Left, LAYER _Right)
{
	int row = 0;
	int col = 0;

	if (_Left < _Right)
	{
		row = (int)_Left;
		col = (int)_Right;
	}
	else
	{
		row = (int)_Right;
		col = (int)_Left;
	}

	m_LayerCheck[row] |= (1 << col);
}

void MyCollisionMgr::UncheckCollision(LAYER _Left, LAYER _Right)
{
	int row = 0;
	int col = 0;

	if (_Left < _Right)
	{
		row = (int)_Left;
		col = (int)_Right;
	}
	else
	{
		row = (int)_Right;
		col = (int)_Left;
	}

	m_LayerCheck[row] &= (1 << col);
}

void MyCollisionMgr::CollisionBtwLayer(LAYER _Left, LAYER _Right)
{
	MyLevel* pCurLevel = MyLevelMgr::GetInst()->GetCurLevel();

	if (nullptr == pCurLevel)
	{
		return;
	}

	const vector<MyCollider*>& vecLeft = pCurLevel->GetLayer((int)_Left)->GetColliders();
	const vector<MyCollider*>& vecRight = pCurLevel->GetLayer((int)_Right)->GetColliders();

	// 서로 다른 레이어끼리 충돌 검사
	if (_Left != _Right)
	{
		for (size_t i = 0; i < vecLeft.size(); ++i)
		{
			for (size_t j = 0; j < vecRight.size(); ++j)
			{
				COLLIDER_ID ID(vecLeft[i]->GetID(), vecRight[j]->GetID());

				map<COLLIDER_ID, bool>::iterator iter = m_mapID.find(ID);

				if (iter == m_mapID.end())
				{
					m_mapID.insert(make_pair(ID, false));
					iter = m_mapID.find(ID);
				}

				// 충돌이 생김
				if (IsCollision(vecLeft[i], vecRight[j]))
				{
					if (false == iter->second)
					{
						// 두 충돌체 모두 살아있는 상태이며 이전에는 충돌하지 않았을 경우
						if (!vecLeft[i]->IsDead() && !vecRight[j]->IsDead())
						{
							vecLeft[i]->BeginOverlap(vecRight[j]);
							vecRight[j]->BeginOverlap(vecLeft[i]);
						}
					}
					else
					{
						// 둘 중에 하나라도 Dead 상태인데 이전에 충돌 중이었을 경우
						if (vecLeft[i]->IsDead() || vecRight[j]->IsDead())
						{
							vecLeft[i]->EndOverlap(vecRight[j]);
							vecRight[j]->EndOverlap(vecLeft[i]);
						}
						else
						{
							// 두 충돌체 모두 살아있으며 이전에도 충돌 중이었을 경우
							vecLeft[i]->Overlap(vecRight[j]);
							vecRight[j]->Overlap(vecLeft[i]);
						}
					}

					iter->second = true;
				}

				// 충돌을 안하고 있음
				else
				{
					// 이전에는 충돌하고 있었다
					if (true == iter->second)
					{
						vecLeft[i]->EndOverlap(vecRight[j]);
						vecRight[j]->EndOverlap(vecLeft[i]);
					}

					iter->second = false;
				}
			}
		}
	}
	// 같은 레이어끼리 충돌 검사
	else
	{

	}
}

bool MyCollisionMgr::IsCollision(MyCollider* _Left, MyCollider* _Right)
{
	float BtwFinalX = (float)fabs(_Left->GetFinalPos().x - _Right->GetFinalPos().x);
	float BtwFinalY = (float)fabs(_Left->GetFinalPos().y - _Right->GetFinalPos().y);
	float LeftScaleX = (float)fabs(_Left->GetOffsetScale().x / 2.f);
	float LeftScaleY = (float)fabs(_Left->GetOffsetScale().y / 2.f);
	float RightScaleX = (float)fabs(_Right->GetOffsetScale().x / 2.f);
	float RightScaleY = (float)fabs(_Right->GetOffsetScale().y / 2.f);

	// 두 충돌체 간 x좌표, y좌표 거리(절대값)가 각 충돌체 스케일값의 절반을 더한 값보다 작거나 같을 때 충돌했다 볼 수 있다
	if ((LeftScaleX + RightScaleX) >= BtwFinalX && (LeftScaleY + RightScaleY) >= BtwFinalY)
	{
		return true;
	}

	//if (fabs(_Left->GetOffsetScale().x / 2.f + _Right->GetOffsetScale().x / 2.f) >= fabs(_Left->GetFinalPos().x - _Right->GetFinalPos().x)
	//	&& fabs(_Left->GetOffsetScale().y / 2.f + _Right->GetOffsetScale().y / 2.f) >= fabs(_Left->GetFinalPos().y - _Right->GetFinalPos().y))
	//{
	//	return true;
	//}

	return false;
}
