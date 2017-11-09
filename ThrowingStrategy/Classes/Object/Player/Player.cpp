//************************************************/
//* @file  :Player.cpp
//* @brief :ÉvÉåÉCÉÑÅ[
//* @date  :2017/11/02
//* @author:S.Katou
//************************************************/
#include "Player.h"

#include <functional>
#include <SL_MacroConstants.h>
#include "State\PlayerMoveState.h"
#include "../../Main/SL_MyStepTimer.h"

void Player::Initialize()
{
	this->Type(PLAYER);
	this->ChangeState(new PlayerMoveState);
	StateObject::Initialize();

	m_collider = new ShunLib::SphereCollider();
	m_collider->Parent(this);

	m_collider->SetCallBack([&](ObjectBase* obj) { this->CollisionCallBack(obj); });
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
