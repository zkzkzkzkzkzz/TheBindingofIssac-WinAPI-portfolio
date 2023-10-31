#pragma once


class MyEntity;

class MyGCMgr
{
	SINGLETON(MyGCMgr);

private:
	vector<MyEntity*> m_Entity;

public:
	void AddEntity(MyEntity* _Entity)
	{
		m_Entity.push_back(_Entity);
	}

public:
	void tick();
};
