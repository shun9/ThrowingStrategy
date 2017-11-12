//************************************************/
//* @file  :Player.cpp
//* @brief :プレイヤー
//* @date  :2017/11/02
//* @author:S.Katou
//************************************************/
#include "Player.h"

#include <functional>
#include <SL_MacroConstants.h>
#include <SL_Math.h>
#include "State\PlayerMoveState.h"
#include "../../Main/SL_MyStepTimer.h"

void Player::Initialize()
{
	this->Type(PLAYER);
	this->ChangeState(new PlayerMoveState);
	StateObject::Initialize();

	//当たり判定の設定
	m_collider = new ShunLib::SphereCollider();
	m_collider->Parent(this);
	m_collider->Offset(ShunLib::Vec3(0.0f, 1.0f, 0.0f));
	m_collider->SetCallBack([&](ObjectBase* obj) { this->CollisionCallBack(obj); });
	
	//当たり判定の形状の設定
	m_collider->Shape()->Scale(1.0f);
}

void Player::Finalize()
{
	StateObject::Finalize();

	SAFE_DELETE(m_collider);
}

void Player::CollisionCallBack(ObjectBase* obj)
{
	auto timer = ShunLib::MyStepTimer::GetInstance();
	auto pos = this->Pos();
	pos.m_y += 0.1f * timer->GetElapsedSeconds();
	this->Pos(pos);
}
