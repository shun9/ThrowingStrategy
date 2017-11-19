//************************************************/
//* @file  :SL_CameraState.h
//* @brief :描画用カメラの状態まとめ
//* @date  :2017/11/16
//* @author:S.Katou
//************************************************/
#pragma once
#include <SL_State.h>
#include "SL_Camera.h"

namespace ShunLib
{
	//動かない状態
	//何もしない
	class CameraNonMoveState:public State<MainCamera>
	{
	public:
		CameraNonMoveState() {}
		~CameraNonMoveState() {}

		//開始処理
		void Enter(MainCamera* camera);

		//実行処理
		void Execute(MainCamera* camera);

		//終了処理
		void Exit(MainCamera* camera);
	};

	//オブジェクトを追跡する状態
	class CameraFollowState :public State<MainCamera>
	{
	private:
		static const float FOLLOW_DISTANSE;
		static const float FOLLOW_HEIGHT;

	public:
		CameraFollowState() {}
		~CameraFollowState() {}

		//開始処理
		void Enter(MainCamera* camera);

		//実行処理
		void Execute(MainCamera* camera);

		//終了処理
		void Exit(MainCamera* camera);
	};

}
