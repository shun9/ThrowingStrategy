//************************************************/
//* @file  :StateObject.h
//* @brief :��Ԃ����I�u�W�F�N�g
//* @date  :2017/10/30
//* @author:S.Katou
//************************************************/
#pragma once
#include "ObjectBase.h"

#include <memory>
#include <SL_StateMachine.h>
#include <SL_Math.h>

template<class T>
class StateObject : public ObjectBase
{
protected:
	std::unique_ptr<ShunLib::StateMachine<T>> m_stateMachine;

public:
	//�R���X�g���N�^�@��Ԃ��g�p����I�u�W�F�N�g��n��
	StateObject(T* obj) {
		m_stateMachine = std::make_unique<ShunLib::StateMachine<T>>(obj);
	}
	virtual ~StateObject() {}

	//�X�V
	void Update()override {
		//�X�e�[�g�}�V��������΍X�V
		if (m_stateMachine){
			m_stateMachine->Update();
		}
	}

	//��Ԑؑ�
	void ChangeState(ShunLib::State<T>* state) { m_stateMachine->ChangeState(state); }

	//�������@�X�V�@�I��
	virtual void Initialize() = 0;
	virtual void Finalize()   = 0;
};

