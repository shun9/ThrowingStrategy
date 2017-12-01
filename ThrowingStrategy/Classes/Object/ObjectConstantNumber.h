//************************************************/
//* @file  :ObjectConstantNumber.h
//* @brief :�I�u�W�F�N�g�֘A�̒萔
//* @date  :2017/11/16
//* @author:S.Katou
//************************************************/
#pragma once
#include <SL_Lerp.h>

//�I�u�W�F�N�g�ꗗ
enum OBJECT_LIST
{
	ROOT = 0,		//���[�g�I�u�W�F�N�g
	PLAYER,			//�v���C���[
	COMMANDER,      //�w����
	UNIT,           //��������郆�j�b�g
	BLOCK,          //�u���b�N
	DEFENSE_TARGET,	//�h�q�Ώ�
	SUMMONER,		//���j�b�g����������I�u�W�F�N�g
	STAGE,			//�X�e�[�W

	OBJECT_LIST_END,//�I�u�W�F�N�g�̎�ސ�
};

//���j�b�g�̎��
enum UNIT_LIST
{
	NORMAL = 0,

	UNIT_LIST_END,
};

//�X�e�[�W�ꗗ
enum STAGE_LIST
{
	GROUND = 0,		//�n�ʂ݂̂̃X�e�[�W

	STAGE_LIST_END,//�X�e�[�W��ސ�
};

//�`�[������
enum TEAM
{
	NONE = -1,    //�`�[������
	RED  = 0,
	BLUE,

	TEAM_END,     //�`�[����
};

//������
enum THROW_TYPE
{
	LINE = 0,

	THROW_TYPE_END,
};

