//************************************************/
//* @file  :Player.h
//* @brief :�v���C���[
//* @date  :2017/12/12
//* @author:S.Katou
//************************************************/
#pragma once
#include "../StateObject.h"
#include "../../Physics/Collision/SL_Collider.h"

class Unit;

class Player : public StateObject<Player>
{
public:
	using PLAYER_CONSTANT = ObjectConstantNumber::PLAYER_CONSTANT;

private:
	//�{�̂̓����蔻��
	ShunLib::SphereCollider* m_collider;

public:
	Player();
	~Player();

	//�������@�I��
	void Initialize()override;
	void Finalize()override;

	//���j�b�g�𐮗񂷂�
	void AlignUnits();

	
	//�����Ă��郆�j�b�g�̐�
	int HavingUnitNum();

	//�����Ă��郆�j�b�g�̈ꗗ
	std::vector<Unit*>& HavingUnitList();

	/*--Getter--*/
	ShunLib::SphereCollider* Collider() { return m_collider; }
};