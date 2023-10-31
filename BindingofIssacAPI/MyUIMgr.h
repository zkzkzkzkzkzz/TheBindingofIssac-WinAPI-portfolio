#pragma once


class MyUI;

class MyUIMgr
{
	SINGLETON(MyUIMgr);
private:
	MyUI* m_FocuedUI;	// 최상위 부모 UI 중에서 포커싱 되어있는 UI

public:
	void tick();

private:
	MyUI* GetPriorityCheck(MyUI* _ParentUI);

};

