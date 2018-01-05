//************************************************/
//* @file  :MyGame.h
//* @brief :ゲームクラス
//* @date  :2018/01/01
//* @author:S.Katou
//************************************************/
#pragma once
#include "SL_Application.h"

#include <SL_ObjectHolder.h>
#include "../Object/ObjectConstantNumber.h"
#include "../../StepTimer.h"

class MyGame :public ShunLib::Application
{
public:
	enum SCENE{
		PLAY,
	};

public:
	MyGame() {
		ShunLib::ObjectHolder::GetInstance()->ResizeList(
			ObjectConstantNumber::OBJECT_LIST_END,
			100
		);
	}
	~MyGame() {}

protected:
	//初期化　更新　描画　終了
	void Initialize()override;
	void Update()override;
	void Render()override;
	void Finalize()override;
};
