//************************************************/
//* @file  :Stage.h
//* @brief :�X�e�[�W�̊��N���X�Ɛݒu����I�u�W�F�N�g
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
	Stage();
	virtual ~Stage();

	void SetStageType(STAGE_LIST type);
};

