//************************************************/
//* @file  :SL_Application.h
//* @brief :アプリケーションの基底クラス
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

		//メインループ
		void Run();

	protected:
		//初期化　更新　描画　終了
		virtual void Initialize() = 0;
		virtual void Update    () = 0;
		virtual void Render    () = 0;
		virtual void Finalize  () = 0;
	};

}