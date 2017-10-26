//************************************************/
//* @file  :SL_MyGame.h
//* @brief :�Q�[���N���X
//* @date  :2017/10/26
//* @author:S.Katou
//************************************************/
#pragma once
#include "SL_Application.h"
#include "../../StepTimer.h"

namespace ShunLib
{
	class MyGame:public Application
	{
	public:
		MyGame() {}
		~MyGame() {}

	protected:
		//�������@�X�V�@�`��@�I��
		void Initialize()override;
		void Update    ()override;
		void Render    ()override;
		void Finalize  ()override;

	private:
		DX::StepTimer m_timer;
	};
}