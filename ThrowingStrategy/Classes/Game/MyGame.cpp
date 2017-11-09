//************************************************/
//* @file  :SL_MyGame.cpp
//* @brief :ゲームクラス
//* @date  :2017/11/09
//* @author:S.Katou
//************************************************/
#include "MyGame.h"

#include <SL_Model.h>
#include <SL_Texture.h>
#include <SL_KeyManager.h>

#include "../Main/SL_Graphics.h"
#include "../Main/SL_MyStepTimer.h"
#include "Scene\SL_SceneManager.h"
#include "Scene\PlayScene.h"
#include "../Physics/Collision/SL_CollisionManager.h"

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
	
	//キー更新
	auto key = ShunLib::KeyManager::GetInstance();
	key->Update();

	//シーン更新
	timer->Tick([&]()
	{
		scene->Update();
		ShunLib::CollisionManager::GetInstance()->Update();
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
	ShunLib::CollisionManager::Destroy();
	ShunLib::SceneManager::Destroy();
}
