//************************************************/
//* @file  :TitleScene.cpp
//* @brief :タイトルシーン
//* @date  :2018/01/31
//* @author:S.Katou
//************************************************/
#include "TitleScene.h"
#include <SL_KeyManager.h>
#include "SL_SceneManager.h"
#include "../MyGame.h"
#include "../../Main/SL_Window.h"
#include "../../UI/UIConstantNumber.h"
#include "../../UI/UIResourceHolder.h"

using namespace ShunLib;

/// <summary>
/// コンストラクタ
/// </summary>
TitleScene::TitleScene():
	m_optionBoard(UIConstantNumber::TITLE_LAYER,1,2)
{
	//選択肢の設定
	m_optionBoard.AddText(UI_STRING_LIST::STRING_START, TITLE_START);
	m_optionBoard.AddText(UI_STRING_LIST::STRING_END, TITLE_END);

	m_optionBoard.Scale(Vec3(0.4f,0.5f,0.0f));
	m_optionBoard.Offset(10.0f, 0.0f);

	auto window = Window::GetInstance();

	Vec3 pos;
	pos.m_x = (window->Width() - m_optionBoard.BoardWidth()) / 2;
	pos.m_y = (window->Height() + m_optionBoard.BoardHeight()) / 2;
	m_optionBoard.Pos(pos);
}

/// <summary>
/// デストラクタ
/// </summary>
TitleScene::~TitleScene()
{

}

/// <summary>
/// 初期化
/// </summary>
void TitleScene::Initialize()
{
	m_optionBoard.IsEnable(true);
	m_optionBoard.CurrentOption(TITLE_START);
}

/// <summary>
/// 更新
/// </summary>
void TitleScene::Update()
{
	//選択肢の更新
	m_optionBoard.Update();

	//選択肢が決定されたら
	if (m_optionBoard.IsDesided()){
		switch (m_optionBoard.CurrentOption())
		{
		//プレイシーンへ移行
		case TITLE_START:
			SceneManager::GetInstance()->ChangeScene(MyGame::SCENE::PLAY);
			break;

		//終了
		case TITLE_END:
			PostQuitMessage(0);
			break;

		default:
			break;
		}
	}
}

/// <summary>
/// 描画
/// </summary>
void TitleScene::Render()
{

}

/// <summary>
/// 終了
/// </summary>
void TitleScene::Finalize()
{
	m_optionBoard.IsEnable(false);
}
