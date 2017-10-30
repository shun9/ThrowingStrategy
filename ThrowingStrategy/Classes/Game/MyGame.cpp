//************************************************/
//* @file  :SL_MyGame.cpp
//* @brief :ゲームクラス
//* @date  :2017/10/26
//* @author:S.Katou
//************************************************/
#include "MyGame.h"

#include <SL_Model.h>
#include <SL_Texture.h>
#include "Scene\SL_SceneManager.h"
#include "../Main/SL_Graphics.h"
#include "Scene\PlayScene.h"
#include "../Main/SL_MyStepTimer.h"

/// <summary>
/// 初期化処理
/// </summary>
void MyGame::Initialize()
{
	//グラフィック関連
	auto graphics = ShunLib::Graphics::GetInstance();
	ShunLib::Model::SetDevice(graphics->Device(), graphics->DeviceContext());
	ShunLib::Texture::SetDevice(graphics->Device(), graphics->DeviceContext());

	//シーン関連
	auto scene = ShunLib::SceneManager::GetInstance();
	scene->AddScene(SCENE::PLAY, new PlayScene);
	scene->ChangeScene(SCENE::PLAY);
}

/// <summary>
/// 更新処理
/// </summary>
void MyGame::Update()
{
	auto scene = ShunLib::SceneManager::GetInstance();
	auto timer = ShunLib::MyStepTimer::GetInstance();

	timer->Tick([&]()
	{
		scene->Update();
	});
}

/// <summary>
/// 描画処理
/// </summary>
void MyGame::Render()
{
	auto scene = ShunLib::SceneManager::GetInstance();
	scene->Render();
}

/// <summary>
/// 終了処理
/// </summary>
void MyGame::Finalize()
{
	ShunLib::SceneManager::Destroy();
}
