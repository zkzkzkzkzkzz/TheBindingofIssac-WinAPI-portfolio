#pragma once
class MyKeyMgr
{
	SINGLETON(MyKeyMgr);
private:
	vector<FKeyData>	m_vecKeyData;

	Vec2				m_vMousePos;

public:
	KEY_STATE GetKeyState(KEY _Key) { return m_vecKeyData[(int)_Key].eState; }
	Vec2 GetMousePos() { return m_vMousePos; }

public:
	void init();
	void tick();
};

