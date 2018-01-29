//************************************************/
//* @file  :TitleScene.h
//* @brief :タイトルシーン
//* @date  :2018/01/24
//* @author:S.Katou
//************************************************/
#pragma once
#include "SL_IScene.h"

class TitleScene :public ShunLib::IScene
{
public:
	TitleScene();
	~TitleScene();

	//初期化　更新　描画　終了
	virtual void Initialize();
	virtual void Update();
	virtual void Render();
	virtual void Finalize();
};