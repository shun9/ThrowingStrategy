//************************************************/
//* @file  :TitleScene.h
//* @brief :タイトルシーン
//* @date  :2018/01/24
//* @author:S.Katou
//************************************************/
#pragma once
#include "SL_IScene.h"
#include "../../UI/OptionBoard.h"

class TitleScene :public ShunLib::IScene
{
public:
	//タイトル画面での選択肢
	enum TITLE_OPTION {
		TITLE_START = 0,
		TITLE_END,
		TITLE_OPTION_END
	};

private:
	//選択肢
	OptionBoard m_optionBoard;

public:
	TitleScene();
	~TitleScene();

	//初期化　更新　描画　終了
	virtual void Initialize();
	virtual void Update();
	virtual void Render();
	virtual void Finalize();
};