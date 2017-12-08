//************************************************/
//* @file  :Stage.cpp
//* @brief :�X�e�[�W�̊��N���X�Ɛݒu����I�u�W�F�N�g
//* @date  :2017/12/07
//* @author:S.Katou
//************************************************/
#include "Stage.h"
#include "StageObject.h"
#include "../ObjectFactory.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="type">�X�e�[�W�̎��</param>
Stage::Stage(STAGE_TYPE type):
	m_stageType(type),
	ObjectBase(OBJECT_LIST::STAGE)
{

}

Stage::~Stage()
{

}