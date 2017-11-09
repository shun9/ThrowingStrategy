//************************************************/
//* @file  :ObjectConstantNumber.h
//* @brief :�I�u�W�F�N�g�֘A�̒萔
//* @date  :2017/11/02
//* @author:S.Katou
//************************************************/
#pragma once

//�I�u�W�F�N�g�̃p�����[�^�[���擾����
#define OBJ_PARAM(type) ObjectParamHolder::GetInstance()->GetParam(type)

//�I�u�W�F�N�g�ꗗ
enum OBJECT_LIST
{
	PLAYER = 0,     //�v���C���[
	COMMANDER,      //�w����
	UNIT,           //��������郆�j�b�g
	OBJECT_LIST_END,//�I�u�W�F�N�g�̎�ސ�
};

//�`�[������
enum TEAM
{
	NONE = -1,    //�`�[������
	RED  = 0,
	BLUE,
	TEAM_END,     //�`�[����
};