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

using namespace ShunLib;

/// <summary>
/// コンストラクタ
/// </summary>
PlayScene::PlayScene(){
}

/// <summary>
/// デストラクタ
/// </summary>
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
	//Enterキーで仮リセット処理
	auto key = KeyManager::GetInstance();
	if (key->IsTracker(KeyManager::KEY_CODE::ENTER)) {
		SceneManager::GetInstance()->ChangeScene(MyGame::SCENE::TITLE);
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
