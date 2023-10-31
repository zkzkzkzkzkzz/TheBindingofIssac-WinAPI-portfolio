#pragma once

class MyLevel;

class MyLevelMgr
{
	SINGLETON(MyLevelMgr);
private:
	MyLevel* m_pCurLevel;
	MyLevel* m_arrLevels[(UINT)LEVEL_TYPE::END];

public:
	MyLevel* GetCurLevel() { return m_pCurLevel; }

private:
	void ChangeLevel(LEVEL_TYPE _Type);

public:
	void init();
	void tick();
	void render(HDC _dc);

	friend class MyTaskMgr;
};