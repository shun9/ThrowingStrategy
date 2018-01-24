//************************************************/
//* @file  :StandardStage.h
//* @brief :�M�~�b�N�̖����X�e�[�W
//* @date  :2018/01/24
//* @author:S.Katou
//************************************************/
#pragma once
#include "Stage.h"

class StandardStage : public Stage
{
public:
	using Vec3 = ShunLib::Vec3;

public:
	StandardStage() :
		Stage(STAGE_TYPE::STANDARD) {}
	~StandardStage() {}

protected:
	//������ �X�V �I��
	void Initialize()override;
	void Update()override {}
	void Finalize()override;

	//��Q���̐ݒu
	void SettingObstacle()override;

	//�I�u�W�F�N�g�̐ݒu
	void SettingBlueObject()override;
	void SettingRedObject()override;

private:
	//�ǂ̐ݒu
	void SettingWall();

	//�X�e�[�W�̘g�ݒu
	void SettingFrameOfStage();
};
