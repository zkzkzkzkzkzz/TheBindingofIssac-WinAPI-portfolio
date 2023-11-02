#include "pch.h"
#include "MyPlayer.h"

#include "MyEngine.h"
#include "MyAssetMgr.h"
#include "MyTexture.h"

#include "components.h"

MyPlayer::MyPlayer()
	: m_AnimatorHead(nullptr)
	, m_AnimatorBody(nullptr)
	//, m_Movement(nullptr)
	//, m_Collider(nullptr)
{
	MyTexture* pAtlas = MyAssetMgr::GetInst()->LoadTexture(L"PlayerAtlas", L"texture\\Character\\Issac.png");

	m_AnimatorBody = AddComponent<MyAnimator>(L"BodyAnimator");
	m_AnimatorHead = AddComponent<MyAnimator>(L"HeadAnimator");

	m_AnimatorBody->LoadAnimation(L"animdata\\BIdleDown.txt");
	m_AnimatorHead->LoadAnimation(L"animdata\\HIdleDown.txt");

	m_AnimatorBody->Play(L"BIdleDown", true);
	m_AnimatorHead->Play(L"HIdleDown", true);
}

MyPlayer::MyPlayer(const MyPlayer& _Origin)
	: MyObject(_Origin)
	, m_AnimatorHead(nullptr)
	, m_AnimatorBody(nullptr)
	//, m_Movement(nullptr)
	//, m_Collider(nullptr)
{
	m_AnimatorHead = GetComponent<MyAnimator>();
	//m_Movement = GetComponent<MyMovement>();
	//m_Collider = GetComponent<MyCollider>();
}

MyPlayer::~MyPlayer()
{
	
}

void MyPlayer::tick(float _DT)
{
	Super::tick(_DT);

	Vec2 vPos = GetPos();

	SetPos(vPos);
}
