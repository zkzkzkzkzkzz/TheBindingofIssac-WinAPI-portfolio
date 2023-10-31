#pragma once

class MyEntity
{
private:
	static UINT_PTR g_NextID;

private:
	const UINT_PTR	m_ID;
	wstring			m_strName;
	bool			m_bDead;

public:
	UINT_PTR GetID() { return m_ID; }
	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }
	bool IsDead() { return m_bDead; }

public:
	virtual MyEntity* Clone() = 0;

public:
	MyEntity();
	MyEntity(const MyEntity& _other);
	virtual ~MyEntity();

	friend class CTaskMgr;
	friend class MyObject;
};

