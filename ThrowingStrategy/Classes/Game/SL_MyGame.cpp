//************************************************/
//* @file  :SL_MyGame.cpp
//* @brief :ゲームクラス
//* @date  :2017/10/26
//* @author:S.Katou
//************************************************/
#include "SL_MyGame.h"
#include "Scene\SL_SceneManager.h"

/// <summary>
/// 初期化処理
/// </summary>
void ShunLib::MyGame::Initialize()
{
	auto scene = ShunLib::SceneManager::GetInstance();

}

/// <summary>
/// 更新処理
/// </summary>
void ShunLib::MyGame::Update()
{
	auto scene = ShunLib::SceneManager::GetInstance();

	m_timer.Tick([&]()
	{
		scene->Update(m_timer);
	});
}

/// <summary>
/// 描画処理
/// </summary>
void ShunLib::MyGame::Render()
{
	auto scene = ShunLib::SceneManager::GetInstance();
	scene->Render();

}

/// <summary>
/// 終了処理
/// </summary>
void ShunLib::MyGame::Finalize()
{
	ShunLib::SceneManager::Destroy();
}
