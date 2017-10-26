//************************************************/
//* @file  :SL_Scene.h
//* @brief :�V�[��
//* @date  :2017/10/26
//* @author:S.Katou
//************************************************/
#pragma once
#include "../../../StepTimer.h"

namespace ShunLib
{
	class IScene
	{
	public:
		IScene() {};
		virtual ~IScene() {};

		//�������@�X�V�@�`��@�I��
		virtual void Initialize() = 0;
		virtual void Update    (DX::StepTimer& timer) = 0;
		virtual void Render    () = 0;
		virtual void Finalize  () = 0;
	};
}