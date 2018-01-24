//************************************************/
//* @file  :Commander.cpp
//* @brief :指揮官
//* @date  :2017/12/13
//* @author:S.Katou
//************************************************/
#include "Commander.h"
#include "CommanderMoveState.h"

#include <SL_MacroConstants.h>
#include "../../Physics/Collision/SL_CollisionManager.h"

/// <summary>
/// コンストラクタ
/// </summary>
Commander::Commander() :
	StateObject(this, OBJECT_LIST::COMMANDER),
	m_capacity(1)
{
	using namespace ShunLib;

	//当たり判定の設定 基本的にプレイヤーと同じ
	m_collider = new SphereCollider(COLLIDER_LAYER::RIGID);
	m_collider->Parent(this);
	m_collider->Offset(ObjectConstantNumber::PLAYER_CONSTANT::COLLIDER_OFFSET);

	//当たり判定の形状の設定
	m_collider->Shape()->Scale(ObjectConstantNumber::PLAYER_CONSTANT::COLLIDER_SIZE);
}

/// <summary>
/// デストラクタ
/// </summary>
Commander::~Commander()
{
	SAFE_DELETE(m_collider);
}

/// <summary>
/// 初期化
/// </summary>
void Commander::Initialize()
{
	StateObject::Initialize();

	//初期状態を設定
	this->ChangeState(new CommanderMoveState);
}

/// <summary>
/// 終了
/// </summary>
void Commander::Finalize()
{
	StateObject::Finalize();
}
