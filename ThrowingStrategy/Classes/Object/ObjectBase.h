//************************************************/
//* @file  :ObjectBase.h
//* @brief :�Q�[���I�u�W�F�N�g�̊��N���X
//* @date  :2017/12/21
//* @author:S.Katou
//************************************************/
#pragma once
#include "../NewShunLib/SL_ObjectNode.h"
#include "ObjectConstantNumber.h"
#include "ObjectData.h"

class ObjectBase : public ShunLib::ObjectNode
{
public:
	using OBJECT_LIST = ObjectConstantNumber::OBJECT_LIST;

protected:
	//�I�u�W�F�N�g�̃Q�[���p�f�[�^
	ObjectData m_data;

public:
	//�R���X�g���N�^
	//�I�u�W�F�N�g�̎�ނ�n��
	ObjectBase(OBJECT_LIST type);

	//�f�X�g���N�^
	virtual ~ObjectBase();

	//�ړ�������
	void Move();

	/*--Getter & Setter--*/
	ObjectData& Data() { return m_data; }

protected:
	//������ �X�V �`�� �I��
	//�`��̂݋��ʏ���
	virtual void Initialize()override = 0;
	virtual void Update    ()override = 0;
	virtual void Render    ()override;
	virtual void Finalize  ()override = 0;
};