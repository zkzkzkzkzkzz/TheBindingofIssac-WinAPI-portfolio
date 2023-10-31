#pragma once

#include "MyEntity.h"

class MyObject;
class MyCollider;

class MyLayer
	: public MyEntity
{
private:
	vector<MyObject*> 		m_vecObjects;
	vector<MyCollider*>		m_vecCollider;

public:
	void begin();
	void tick(float _DT);
	void finaltick(float _DT);
	void render(HDC _dc);

	void clear() { m_vecCollider.clear(); }
	void AddObject(MyObject* _Object) { m_vecObjects.push_back(_Object); }
	void RegisterCollider(MyCollider* _Collider) { m_vecCollider.push_back(_Collider); }

	const vector<MyObject*>& GetObjects() { return  m_vecObjects; }

	const vector<MyCollider*>& GetColliders() { return m_vecCollider; }

	void DeleteAllObjects();


public:
	CLONE_DISABLE(MyLayer);
	MyLayer();
	MyLayer(const MyLayer& _Origin) = delete;
	~MyLayer();

	friend class MyLevel;
	friend class MyUIMgr;
};