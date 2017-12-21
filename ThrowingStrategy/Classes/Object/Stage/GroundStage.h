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


protected:
	//������ �X�V �I��
	void Initialize()override;
	void Update    ()override {}
	void Finalize  ()override;

	//��Q���̐ݒu
	void SettingObstacle()override;

	//�I�u�W�F�N�g�̐ݒu
	void SettingBlueObject()override;
	void SettingRedObject()override;
};