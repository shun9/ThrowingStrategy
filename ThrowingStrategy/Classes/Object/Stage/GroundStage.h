//************************************************/
//* @file  :GroundStage.h
//* @brief :�n�ʂ݂̂̃X�e�[�W
//* @date  :2017/12/07
//* @author:S.Katou
//************************************************/
#pragma once
#include "Stage.h"

class GroundStage : public Stage
{
public:
	GroundStage():
		Stage(STAGE_TYPE::GROUND){};
	~GroundStage() {};

	//������
	void Initialize()override;

	//�I�� 
	void Finalize()override;

protected:
	//��Q���̐ݒu
	void SettingObstacle()override;

	//�I�u�W�F�N�g�̐ݒu
	void SettingBlueObject()override;
	void SettingRedObject()override;
};