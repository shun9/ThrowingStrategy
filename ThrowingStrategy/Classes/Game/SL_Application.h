//************************************************/
//* @file  :SL_Application.h
//* @brief :�A�v���P�[�V�����̊��N���X
//* @date  :2017/10/26
//* @author:S.Katou
//************************************************/
#pragma once

namespace ShunLib
{
	class Application
	{
	public:
		Application() {}
		virtual ~Application() {}

		//���C�����[�v
		void Run();

	protected:
		//�������@�X�V�@�`��@�I��
		virtual void Initialize() = 0;
		virtual void Update    () = 0;
		virtual void Render    () = 0;
		virtual void Finalize  () = 0;
	};

}