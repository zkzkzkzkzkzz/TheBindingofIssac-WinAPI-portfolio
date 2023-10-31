#pragma once

class MyCollider;


struct COLLIDER_ID
{
	INT_PTR left;
	INT_PTR right;

	bool operator == (const COLLIDER_ID& _Other) const
	{
		if (left == _Other.left && right == _Other.right)
		{
			return true;
		}

		return false;
	}

	bool operator < (const COLLIDER_ID& _Other) const
	{
		if (left < _Other.left)
		{
			return true;
		}
		else if (left > _Other.left)
		{
			return false;
		}
		else
		{
			if (right < _Other.right)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}

	COLLIDER_ID() : left(0), right(0)
	{

	}

	COLLIDER_ID(INT_PTR _left, INT_PTR _right) : left(_left), right(_right)
	{

	}
};

class MyCollisionMgr
{
	SINGLETON(MyCollisionMgr);

private:
	UINT					m_LayerCheck[32];
	map<COLLIDER_ID, bool>	m_mapID;

public:
	void tick();
	void CheckCollision(LAYER _Left, LAYER _Right);
	void UncheckCollision(LAYER _Left, LAYER _Right);

private:
	void CollisionBtwLayer(LAYER _Left, LAYER _Right);
	bool IsCollision(MyCollider* _Left, MyCollider* _Right);
};


