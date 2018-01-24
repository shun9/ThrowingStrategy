//************************************************/
//* @file  :PlayScene.cpp
//* @brief :プレイシーン
//* @date  :2017/11/02
//* @author:S.Katou
//************************************************/
#include "PlayScene.h"

#include <SL_Matrix.h>
#include <SL_MacroConstants.h>
#include <SL_ObjectHolder.h>
#include "../../Main/SL_Window.h"
#include "../../Util/SL_Camera.h"

//オブジェクト関連
#include "../../Object/ObjectBase.h"
#include "../../Object/ObjectFactory.h"
#include "../../Object/ObjectConstantNumber.h"
#include "../../Util/Debugger/DebuggerUI.h"

PlayScene::PlayScene()
{
	auto window = ShunLib::Window::GetInstance();

	//カメラ設定
	auto camera = ShunLib::MainCamera::GetInstance();
	ProjData pData;
	pData.aspect = static_cast<float>(window->Width() / window->Height());
	camera->Proj(pData);

	//オブジェクト生成
	auto factory = ObjectFactory::GetInstance();

	auto stage = factory->CreateStage(ObjectConstantNumber::STAGE_LIST::STANDARD);
	this->AddChild(stage);
}

PlayScene::~PlayScene()
{

}

/// <summary>
/// 初期化処理
/// </summary>
void PlayScene::Initialize()
{
}

/// <summary>
/// 更新処理
/// </summary>
void PlayScene::Update()
{
	auto camera = ShunLib::MainCamera::GetInstance();
	camera->Update();
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
}
