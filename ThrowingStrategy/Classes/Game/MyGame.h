//************************************************/
//* @file  :SL_MyGame.h
//* @brief :ゲームクラス
//* @date  :2017/10/26
//* @author:S.Katou
//************************************************/
#pragma once
#include "SL_Application.h"
#include "../../StepTimer.h"

class MyGame :public ShunLib::Application
{
public:
	enum SCENE{
		PLAY,
	};

public:
	MyGame() {}
	~MyGame() {}

protected:
	//初期化　更新　描画　終了
	void Initialize()override;
	void Update()override;
	void Render()override;
	void Finalize()override;
};
