//************************************************/
//* @file  :SL_CameraState.h
//* @brief :�`��p�J�����̏�Ԃ܂Ƃ�
//* @date  :2017/11/16
//* @author:S.Katou
//************************************************/
#pragma once
#include <SL_State.h>
#include "SL_Camera.h"

namespace ShunLib
{
	//�����Ȃ����
	//�������Ȃ�
	class CameraNonMoveState:public State<MainCamera>
	{
	public:
		CameraNonMoveState() {}
		~CameraNonMoveState() {}

		//�J�n����
		void Enter(MainCamera* camera);

		//���s����
		void Execute(MainCamera* camera);

		//�I������
		void Exit(MainCamera* camera);
	};

	//�I�u�W�F�N�g��ǐՂ�����
	class CameraFollowState :public State<MainCamera>
	{
	private:
		static const float FOLLOW_DISTANSE;
		static const float FOLLOW_HEIGHT;

	public:
		CameraFollowState() {}
		~CameraFollowState() {}

		//�J�n����
		void Enter(MainCamera* camera);

		//���s����
		void Execute(MainCamera* camera);

		//�I������
		void Exit(MainCamera* camera);
	};

}
