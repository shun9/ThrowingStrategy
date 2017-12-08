//************************************************/
//* @file  :ObjectDataHolder.cpp
//* @brief :���j�b�g�f�[�^�̈ꗗ��ێ�����N���X
//* @date  :2017/11/16
//* @author:S.Katou
//************************************************/
#include "ObjectParamHolder.h"
#include "ObjectConstantNumber.h"

ObjectParamHolder::ObjectParamHolder()
{
	m_dataList.resize(ObjectConstantNumber::OBJECT_LIST_END);

	ObjectParam data;

	//���[�g�I�u�W�F�N�g
	data.maxHP = 99999;
	data.power = 99999.0f;
	data.spd = 99.0f;
	m_dataList[ObjectConstantNumber::ROOT] = data;

	//�v���C���[
	data.maxHP = 100;
	data.power = 20.0f;
	data.spd = 10.0f;
	m_dataList[ObjectConstantNumber::PLAYER] = data;

	//�w����
	data.maxHP = 100;
	data.power = 20.0f;
	data.spd = 10.0f;
	m_dataList[ObjectConstantNumber::COMMANDER] = data;

	//�������j�b�g
	data.maxHP = 10;
	data.power = 3.0f;
	data.spd = 3.0f;
	m_dataList[ObjectConstantNumber::UNIT] = data;

	//�u���b�N
	data.maxHP = 99999;
	data.power = 0.0f;
	data.spd = 0.0f;
	m_dataList[ObjectConstantNumber::BLOCK] = data;

	//�h�q�Ώ�
	data.maxHP = 20000;
	data.power = 0.0f;
	data.spd = 0.0f;
	m_dataList[ObjectConstantNumber::DEFENSE_TARGET] = data;

	//���j�b�g����������I�u�W�F�N�g
	data.maxHP = 10000;
	data.power = 0.0f;
	data.spd = 0.0f;
	m_dataList[ObjectConstantNumber::SUMMONER] = data;

	//�X�e�[�W
	data.maxHP = 99999;
	data.power = 0.0f;
	data.spd = 0.0f;
	m_dataList[ObjectConstantNumber::STAGE] = data;
}
