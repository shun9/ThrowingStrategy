//************************************************/
//* @file  :ObjectDataHolder.h
//* @brief :�I�u�W�F�N�g�̃Q�[���p�����[�^�̈ꗗ��ێ�����N���X
//* @date  :2017/11/27
//* @author:S.Katou
//************************************************/
#pragma once
#include <memory>
#include <vector>
#include <SL_Singleton.h>
#include <SL_Model.h>

//�I�u�W�F�N�g�̃p�����[�^�[���擾����
#define OBJ_PARAM(type) ObjectParamHolder::GetInstance()->GetParam(type)


//���j�b�g�̃f�[�^
struct ObjectParam
{
public:
	int maxHP;
	float power;
	float spd;
	std::shared_ptr<ShunLib::Model> model;
};

class ObjectParamHolder : public ShunLib::Singleton<ObjectParamHolder>
{
	friend ShunLib::Singleton<ObjectParamHolder>;
private:
	//�f�[�^�ꗗ
	std::vector<ObjectParam> m_dataList;

public:
	//�f�[�^�̎擾
	const ObjectParam& GetParam(int dataNum) {
		return m_dataList.at(dataNum);
	}

private:
	ObjectParamHolder();
	~ObjectParamHolder() {}
};