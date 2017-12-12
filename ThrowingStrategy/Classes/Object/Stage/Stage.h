//************************************************/
//* @file  :Stage.h
//* @brief :�X�e�[�W�̊��N���X
//* @date  :2017/11/16
//* @author:S.Katou
//************************************************/
#pragma once
#include <vector>
#include "../ObjectBase.h"

//�X�e�[�W�̊��
class Stage : public ObjectBase
{
public:
	using STAGE_TYPE = ObjectConstantNumber::STAGE_LIST;

protected:
	//�X�e�[�W�̎��
	ObjectConstantNumber::STAGE_LIST m_stageType;

public:
	Stage(STAGE_TYPE type);
	virtual ~Stage();

protected:
	//��Q���̐ݒu
	virtual void SettingObstacle() = 0;

	//�I�u�W�F�N�g�̐ݒu
	virtual void SettingBlueObject() = 0;
	virtual void SettingRedObject() = 0;
};

