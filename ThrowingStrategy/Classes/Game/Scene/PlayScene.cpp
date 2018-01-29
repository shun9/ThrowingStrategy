//************************************************/
//* @file  :PlayScene.cpp
//* @brief :プレイシーン
//* @date  :2017/11/02
//* @author:S.Katou
//************************************************/
#include "PlayScene.h"
#include <SL_KeyManager.h>
#include "SL_SceneManager.h"
#include "../MyGame.h"
#include "../../Main/SL_Window.h"
#include "../../Util/SL_Camera.h"
#include "../../Object/Stage/Stage.h"
#include "../../Object/ObjectFactory.h"
#include "../../Object/ObjectConstantNumber.h"

PlayScene::PlayScene()
{
	auto window = ShunLib::Window::GetInstance();

	//カメラ設定
	auto camera = ShunLib::MainCamera::GetInstance();
	ProjData pData;
	pData.aspect = static_cast<float>(window->Width() / window->Height());
	camera->Proj(pData);
}

PlayScene::~PlayScene()
{

}

/// <summary>
/// 初期化処理
/// </summary>
void PlayScene::Initialize()
{
	//オブジェクト生成
	auto factory = ObjectFactory::GetInstance();

	auto stage = factory->CreateStage(ObjectConstantNumber::STAGE_LIST::STANDARD);
	this->AddChild(stage);
}

/// <summary>
/// 更新処理
/// </summary>
void PlayScene::Update()
{
	//カメラ更新
	auto camera = ShunLib::MainCamera::GetInstance();
	camera->Update();

	//Enterキーで仮リセット処理
	auto key = ShunLib::KeyManager::GetInstance();
	if (key->IsTracker(ShunLib::KeyManager::KEY_CODE::ENTER)) {
		ShunLib::SceneManager::GetInstance()->ChangeScene(MyGame::SCENE::TITLE);
	}
}

/// <summary>
/// 描画処理
/// </summary>
void PlayScene::Render()
{
}

/// <summary>
/// 終了処理
/// </summary>
void PlayScene::Finalize()
{
	//ステージを消す
	//ステージは常に1つにする
	for (auto& child:m_children){
		SAFE_DELETE(child);
	}
	m_children.clear();
}
