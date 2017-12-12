//************************************************/
//* @file  :DefenseTarget.h
//* @brief :�h�q�Ώ�
//* @date  :2017/12/12
//* @author:S.Katou
//************************************************/
#pragma once
#include "../StateObject.h"
#include "../../Physics/Collision/SL_Collider.h"

class DefenseTarget : public StateObject<DefenseTarget>
{
public:
	using DEFENSE_TARGET_CONSTANT = ObjectConstantNumber::DEFENSE_TARGET_CONSTANT;

private:
	//�{�̂̓����蔻��
	ShunLib::BoxCollider* m_collider;

public:
	DefenseTarget();
	~DefenseTarget();

	//�������@�I��
	void Initialize()override;
	void Finalize()override;

	//�X�V
	void Update()override;
};