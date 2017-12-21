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
#include "../Physics/Collision/SL_CollisionManager.h"
#include "../Util/SL_GamePadManager.h"
#include "../UI/UIManager.h"
#include "Scene\SL_SceneManager.h"
#include "Scene\PlayScene.h"
#include "../Util/Debugger/DebuggerUI.h"

using namespace ShunLib;

/// <summary>
/// 初期化処理
/// </summary>
void MyGame::Initialize()
{
	//グラフィック関連
	auto graphics = Graphics::GetInstance();
	Model::SetDevice(graphics->Device(), graphics->DeviceContext());
	Texture::SetDevice(graphics->Device(), graphics->DeviceContext());

	//シーン関連
	auto scene = SceneManager::GetInstance();
	scene->AddScene(SCENE::PLAY, new PlayScene);
	scene->ChangeScene(SCENE::PLAY);
}

/// <summary>
/// 更新処理
/// </summary>
void MyGame::Update()
{
	auto scene = SceneManager::GetInstance();
	auto timer = MyStepTimer::GetInstance();

	//キー更新
	KeyManager::GetInstance()->Update();

	//ゲームパッド更新
	GamePadManager::GetInstance()->Update();

	//UI更新
	UIManager::GetInstance()->Update();

	//シーン更新
	timer->Tick([&]()
	{
		scene->Update();
		CollisionManager::GetInstance()->Update();
	});

	/*--仮のリセット処理--*/
	if (KeyManager::GetInstance()->IsTracker(KeyManager::KEY_CODE::ENTER)){
		CollisionManager::Destroy();
		this->Finalize();
		this->Initialize();
	}
}

/// <summary>
/// 描画処理
/// </summary>
void MyGame::Render()
{
	auto scene = ShunLib::SceneManager::GetInstance();
	scene->Render();
	CollisionManager::GetInstance()->Render();

	//UI描画
	UIManager::GetInstance()->Render();

	//デバッグ用UI描画
	DebuggerUI::GetInstance()->Render();
}

/// <summary>
/// 終了処理
/// </summary>
void MyGame::Finalize()
{
	auto scene = SceneManager::GetInstance();
	scene->DeleteAllScene();
}
