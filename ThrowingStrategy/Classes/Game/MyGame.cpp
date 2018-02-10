//************************************************/
//* @file  :SL_MyGame.cpp
//* @brief :ゲームクラス
//* @date  :2018/01/23
//* @author:S.Katou
//************************************************/
#include "MyGame.h"

#include <SL_Model.h>
#include <SL_Texture.h>

#include "Scene\SL_SceneManager.h"
#include "Scene\PlayScene.h"
#include "Scene\TitleScene.h"
#include "../Main/SL_Graphics.h"
#include "../Main/SL_MyStepTimer.h"
#include "../Physics/Collision/SL_CollisionManager.h"
#include "../UI/UIManager.h"
#include "../UI/UIConstantNumber.h"
#include "../Util/Debugger/DebuggerUI.h"
#include "../Util/SL_Camera.h"

using namespace ShunLib;

/// <summary>
/// コンストラクタ
/// </summary>
MyGame::MyGame(){
	auto window = ShunLib::Window::GetInstance();

	//カメラ設定
	auto camera = MainCamera::GetInstance();
	ProjData pData;
	pData.aspect = static_cast<float>(window->Width() / window->Height());
	camera->Proj(pData);

	auto holder = ObjectHolder::GetInstance();

	//オブジェクトリストの全体のサイズを調整
	holder->ResizeList(ObjectConstantNumber::OBJECT_LIST_END, 2);

	//必要数の多いオブジェクトのサイズを個別に調整
	holder->ResizeLayer(ObjectConstantNumber::UNIT, 1000);
	holder->ResizeLayer(ObjectConstantNumber::BLOCK, 100);
}

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
	scene->AddScene(SCENE::TITLE, new TitleScene);
	scene->AddScene(SCENE::PLAY, new PlayScene);
	scene->ChangeScene(SCENE::TITLE);
}

/// <summary>
/// 更新処理
/// </summary>
void MyGame::Update()
{
	//カメラ更新
	auto camera = MainCamera::GetInstance();
	camera->Update();

	//シーン更新
	auto timer = MyStepTimer::GetInstance();
	timer->Tick([&]()
	{
		SceneManager::GetInstance()->Update();

		//UI更新
		UIManager::GetInstance()->Update();

		//当たり判定の更新
		CollisionManager::GetInstance()->Update();
	});
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

	//フェードの描画
	scene->FadeRender();

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
