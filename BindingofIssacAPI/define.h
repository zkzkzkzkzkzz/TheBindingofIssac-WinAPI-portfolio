#pragma once

#define SINGLETON(ClassType) public:\
								static ClassType* GetInst()\
								{\
									static ClassType inst;\
									return &inst;\
								}\
							public:\
								ClassType* operator = (const ClassType& _Origin) = delete;\
							private:\
								ClassType();\
								ClassType(const ClassType& _Origin) = delete;\
								~ClassType();

#define KEY_CHECK(Key, State) MyKeyMgr::GetInst()->GetKeyState(KEY::Key) == KEY_STATE::State

#define KEY_TAP(Key)		KEY_CHECK(Key, TAP)
#define KEY_PRESSED(Key)	KEY_CHECK(Key, PRESSED)
#define KEY_RELEASED(Key)	KEY_CHECK(Key, RELEASED)
#define KEY_NONE(Key)		KEY_CHECK(Key, NONE)

#define PI 3.14159265358979f

#define DT MyTimeMgr::GetInst()->GetDeltaTime()

#define GENERATED_OBJECT(Type)	typedef Type Super;

#define DEBUG_RENDER	MyEngine::GetInst()->DebugRender()
#define SELECT_PEN(DC,TYPE)	FSelectPen TempPenSelect(DC,TYPE)
#define SELECT_BRUSH(DC, hBrush)	FSelectBrush TempBrushSelect(DC, hBrush)

#define CLONE(type) virtual type* Clone() {return new type(*this);}
#define CLONE_DISABLE(type) virtual type* Clone() {return nullptr;}


enum class KEY
{
	_0,
	_1,
	_2,
	_3,
	_4,
	_5,
	_6,
	_7,
	_8,
	_9,

	NUM0,
	NUM1,
	NUM2,
	NUM3,
	NUM4,
	NUM5,
	NUM6,
	NUM7,
	NUM8,
	NUM9,

	Q,
	W,
	E,
	R,
	T,
	Y,
	U,
	I,
	O,
	P,

	A,
	S,
	D,
	F,
	G,
	H,
	J,
	K,
	L,

	Z,
	X,
	C,
	V,
	B,
	N,
	M,

	TAB,
	LSHIFT,
	LALT,
	LCTRL,
	SPACE,

	ESC,
	ENTER,
	BACK,

	LEFT,
	RIGHT,
	UP,
	DOWN,

	LBTN,
	RBTN,

	KEY_END,
};

enum class KEY_STATE
{
	NONE,
	TAP,
	PRESSED,
	RELEASED,
};

enum class LAYER
{
	DEFAULT,
	MAP,
	ROOM,
	DOOR,
	SHADOW,
	PLAYER,
	MONSTER,
	TEARS,
	MONSTEARS,
	BOSS,
	EFFECT,
	TROPHY,

	BOSS_UI = 30,
	UI = 31,
	END = 32,
};

enum class TASK_TYPE
{
	// Param1 : Layer Type, Param2 : Object Address
	CREATE_OBJECT,

	// Param1 : Object Address
	// 삭제는 오브젝트의 주소만 받아도 됨
	DELETE_OBJECT,

	// Param1 : LEVEL_TYPE
	LEVEL_CHANGE,
};

enum class PEN_TYPE
{
	RED_PEN,
	GREEN_PEN,
	BLUE_PEN,
	END,
};

enum class LOG_LEVEL
{
	LOG,
	WARNING,
	ERR,
};

enum class LEVEL_TYPE
{
	TITLE_LEVEL,
	LOAD_LEVEL,
	PLAY_LEVEL,
	ENDING_LEVEL,
	END,
};

enum class TITLE_TYPE
{
	//OPENING,
	TITLE,
	MENU,
	END,
};

enum class Issac_STATE
{
	IDLE,
	MOVE,
	ATTACK,
};

enum class NormalMons_STATE
{
	IDLE,
	TRACE,
	ATTACK,
};

enum class DOOR_DIR
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
};

enum class FKDir
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
};