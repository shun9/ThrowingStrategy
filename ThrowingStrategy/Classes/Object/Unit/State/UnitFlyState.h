//************************************************/
//* @file  :UnitFlyState.h
//* @brief :���j�b�g�̔�ԏ��
//* @date  :2017/11/16
//* @author:S.Katou
//************************************************/
#pragma once

#include <SL_State.h>
#include "../Unit.h"
#include "../../ObjectStruct.h"

class UnitFlyState : public ShunLib::State<Unit>
{
private:
	//��s�p�f�[�^
	FlyingData m_data;

	//����
	float m_timeLimit;
	float m_timeCnt;

public:
	UnitFlyState():
		m_timeLimit(1.0f),
		m_timeCnt(0.0f)
	{}
	~UnitFlyState() {}

	//�J�n����
	void Enter(Unit* obj);

	//���s����
	void Execute(Unit* obj);

	//�I������
	void Exit(Unit* obj);

	//�f�[�^�ݒ�
	void SetData(const FlyingData& data) { m_data = data; }
};