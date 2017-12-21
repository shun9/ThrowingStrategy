//************************************************/
//* @file  :SL_Scene.h
//* @brief :�V�[��
//* @date  :2017/10/26
//* @author:S.Katou
//************************************************/
#pragma once
#include <SL_Node.h>

namespace ShunLib
{
	class IScene : public Node
	{
	public:
		IScene() {
		};
		virtual ~IScene() {};

		//�������@�X�V�@�`��@�I��
		virtual void Initialize() = 0;
		virtual void Update    () = 0;
		virtual void Render    () = 0;
		virtual void Finalize  () = 0;
	};
}
