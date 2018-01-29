//************************************************/
//* @file  :TitleScene.cpp
//* @brief :タイトルシーン
//* @date  :2018/01/24
//* @author:S.Katou
//************************************************/
#include "TitleScene.h"
#include <SL_KeyManager.h>
#include "SL_SceneManager.h"
#include "../MyGame.h"

/// <summary>
/// コンストラクタ
/// </summary>
TitleScene::TitleScene()
{
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

}

/// <summary>
/// 更新
/// </summary>
void TitleScene::Update()
{
	//現在は何もせずプレイシーンへ移行
	ShunLib::SceneManager::GetInstance()->ChangeScene(MyGame::SCENE::PLAY);
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
}
