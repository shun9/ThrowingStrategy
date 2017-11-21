//************************************************/
//* @file  :Player.cpp
//* @brief :�v���C���[
//* @date  :2017/11/13
//* @author:S.Katou
//************************************************/
#include "Player.h"

#include <functional>
#include <SL_MacroConstants.h>
#include <SL_Math.h>
#include "State\PlayerMoveState.h"

void Player::Initialize()
{
	this->Type(OBJECT_LIST::PLAYER);
	this->Team(TEAM::RED);
	this->ChangeState(new PlayerMoveState);
	StateObject::Initialize();

	//�����蔻��̐ݒ�
	m_collider = new ShunLib::SphereCollider();
	m_collider->Parent(this);
	m_collider->Offset(ShunLib::Vec3(0.0f, 1.0f, 0.0f));
	m_collider->SetCallBack([&](ObjectBase* obj) { this->CollisionCallBack(obj); });
	
	//�����蔻��̌`��̐ݒ�
	m_collider->Shape()->Scale(1.0f);
}

void Player::Finalize()
{
	StateObject::Finalize();

	SAFE_DELETE(m_collider);
}

/// <summary>
/// �����Ă��郆�j�b�g�̐���Ԃ�
/// </summary>
int Player::HavingUnitNum()
{
	return std::count_if(
		this->Children().begin(),
		this->Children().end(),
		[](ObjectBase* obj)	{return obj->Type() == UNIT; }
	);
}

void Player::CollisionCallBack(ObjectBase* obj){
}
