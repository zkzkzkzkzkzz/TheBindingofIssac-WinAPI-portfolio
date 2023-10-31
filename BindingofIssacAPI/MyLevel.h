#pragma once

#include "MyEntity.h"
#include "MyLayer.h"

class MyObject;

class MyLevel
	: public MyEntity
{
private:
	MyLayer* m_Layer[(UINT_PTR)LAYER::END];

public:
	virtual void init() = 0;
	virtual void enter() = 0;
	virtual void exit() = 0;

	virtual void begin();
	virtual void tick();
	virtual void render(HDC _dc);

	// 레벨이 소유하고 있는 모든 레이어를 순회하면서 T 타입에 해당하는 객체를 찾아서 결과(_Out) 벡터에 담아준다.
	template<typename T>
	void GetObjects(vector<T*>& _Out);

	// 레벨이 소유하고 있는 특정 레이어의 오브젝트 목록을 반환한다.
	const vector<MyObject*>& GetObjects(LAYER _LayerType) { return m_Layer[(UINT)_LayerType]->m_vecObjects; }

	MyLayer* GetLayer(int LayerIdx)
	{
		assert(!(LayerIdx < 0 || (UINT)LAYER::END <= LayerIdx));
		return m_Layer[LayerIdx];
	}

protected:
	void AddObject(LAYER _LayerType, MyObject* _Object);
	void DeleteAllObjects();
	void DeleteObjectsByLayer(LAYER _Layer);

public:
	MyObject* FindObjectByName(const wstring& _Name);

public:
	CLONE_DISABLE(MyLevel);
	MyLevel();
	MyLevel(const MyLevel& _Origin) = delete;
	~MyLevel();

	friend class MyLevelMgr;
	friend class MyTaskMgr;
};

template<typename T>
inline void MyLevel::GetObjects(vector<T*>& _Out)
{
	for (UINT j = 0; j < (UINT)LAYER::END; ++j)
	{
		for (size_t i = 0; i < m_Layer[j]->m_vecObjects.size(); ++i)
		{
			T* pObj = dynamic_cast<T*>(m_Layer[j]->m_vecObjects[i]);

			if (nullptr != pObj)
			{
				_Out.push_back(pObj);
			}
		}
	}
}
