//************************************************/
//* @file  :Player.cpp
//* @brief :�v���C���[
//* @date  :2017/12/13
//* @author:S.Katou
//************************************************/
#include "Player.h"

#include <SL_MacroConstants.h>
#include "State\PlayerState.h"
#include "../../UI/HPGauge/HPGauge.h"
#include "../../UI/PowerGauge/PowerGauge.h"
#include "../../UI/ThrowCursor/ThrowCursor.h"
#include "../../Util/Visitor/Visitor.h"
#include "../../Game/Scene/SL_SceneManager.h"
#include "../../Physics/Collision/SL_CollisionManager.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
Player::Player()
	:StateObject(this,OBJECT_LIST::PLAYER)
{
	using namespace ShunLib;

	//�����蔻��̐ݒ�
	m_collider = new SphereCollider(COLLIDER_LAYER::RIGID);
	m_collider->Parent(this);
	m_collider->Offset(PLAYER_CONSTANT::COLLIDER_OFFSET);

	//�����蔻��̌`��̐ݒ�
	m_collider->Shape()->Scale(PLAYER_CONSTANT::COLLIDER_SIZE);

	//HP�Q�[�W�̐ݒ�
	m_hpGauge = new HPGauge;
	m_hpGauge->Parent(this);
	m_hpGauge->Offset(PLAYER_CONSTANT::HP_GAUGE_OFFSET);

	//�p���[�Q�[�W�̐ݒ�
	m_powerGauge = new PowerGauge;
	m_powerGauge->Parent(this);
	m_powerGauge->Offset(PLAYER_CONSTANT::HP_GAUGE_OFFSET);
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
Player::~Player()
{
	SAFE_DELETE(m_collider);
	SAFE_DELETE(m_hpGauge);
	SAFE_DELETE(m_powerGauge);
}

/// <summary>
/// ����������
/// </summary>
void Player::Initialize()
{
	//������Ԃ�ݒ�
	ChangeState(new PlayerMoveState);

	//�����蔻����g�p����
	m_collider->IsEnable(true);

	//���N���X�̏�����
	StateObject::Initialize();
}

/// <summary>
/// �I������
/// </summary>
void Player::Finalize()
{
	//���̏I��
	StateObject::Finalize();

	//�����蔻����g�p���Ȃ�
	m_collider->IsEnable(false);
}


/// <summary>
/// ���j�b�g�𑵂���
/// </summary>
void Player::AlignUnits()
{
	SearchUnitVisitor v;
	this->Accept(&v);
	auto list = v.List();
	for (int i = 0; i < (int)list.size(); i++){
		list[i]->LocalPos(PLAYER_CONSTANT::HAVING_OFFSET(i));
	}
}

/// <summary>
/// �����Ă��郆�j�b�g�̐���Ԃ�
/// </summary>
int Player::HavingUnitNum()
{
	SearchUnitVisitor v;
	this->Accept(&v);
	return v.Count();
}


/// <summary>
/// �����Ă��郆�j�b�g�̈ꗗ��Ԃ�
/// </summary>
std::vector<Unit*>& Player::HavingUnitList()
{
	SearchUnitVisitor v;
	this->Accept(&v);
	return v.List();
}