#pragma once
#include "MyComponent.h"

#include "MyLogMgr.h"

class MyState;

class MyStateMachine :
    public MyComponent
{
private:
    map<UINT, MyState*>  m_mapState;
    MyState* m_pCurState;

    map<wstring, void*> m_mapBlackboard;


public:
    void AddState(UINT _id, MyState* _State);
    MyState* FindState(UINT _id);
    void ChangeState(UINT _NextID);

    template<typename T>
    void AddDataToBlackboard(const wstring& _strKey, const T& _Data);

    void* GetDataFromBlackboard(const wstring _strKey);




public:
    virtual void finaltick(float _DT) override;


public:
    CLONE(MyStateMachine);

    MyStateMachine(MyObject* _Owner);
    MyStateMachine(const MyStateMachine& _Origin);
    ~MyStateMachine();
};

template<typename T>
inline void MyStateMachine::AddDataToBlackboard(const wstring& _strKey, const T& _Data)
{
    map<wstring, void*>::iterator iter = m_mapBlackboard.find(_strKey);
    if (iter != m_mapBlackboard.end())
    {
        LOG(ERR, L"!!블랙보드에 해당 데이터 키 이미 있음!!");
        return;
    }

    T* pData = new T;
    *pData = _Data;
    m_mapBlackboard.insert(make_pair(_strKey, pData));
}

