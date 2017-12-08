//************************************************/
//* @file  :PlayScene.cpp
//* @brief :プレイシーン
//* @date  :2017/11/02
//* @author:S.Katou
//************************************************/
#include "PlayScene.h"

#include <SL_Matrix.h>
#include <SL_MacroConstants.h>
#include "../../Main/SL_Window.h"
#include "../../Util/SL_Camera.h"

//オブジェクト関連
#include "../../Object/ObjectBase.h"
#include "../../Object/ObjectFactory.h"
#include "../../Object/ObjectConstantNumber.h"

PlayScene::PlayScene()
{
	auto window = ShunLib::Window::GetInstance();

	//カメラ設定
	auto camera = ShunLib::MainCamera::GetInstance();

	ViewData vData;
	vData.pos = ShunLib::Vec3(0.0f, 10.0f, 15.0f);
	vData.target = ShunLib::Vec3::Zero;

	ProjData pData;
	pData.aspect = static_cast<float>(window->Width() / window->Height());
	camera->View(vData);
	camera->Proj(pData);

	//オブジェクト生成
	auto factory = ObjectFactory::GetInstance();

	auto s = factory->CreateStage(ObjectConstantNumber::STAGE_LIST::GROUND);
}

PlayScene::~PlayScene()
{

}

/// <summary>
/// 初期化処理
/// </summary>
void PlayScene::Initialize()
{
	ObjectBase::ROOT_OBJECT->Initialize();
}

/// <summary>
/// 更新処理
/// </summary>
void PlayScene::Update()
{
	auto camera = ShunLib::MainCamera::GetInstance();
	camera->Update();
	ObjectBase::ROOT_OBJECT->Update();
}

/// <summary>
/// 描画処理
/// </summary>
void PlayScene::Render()
{
	auto camera = ShunLib::MainCamera::GetInstance();
	
	ObjectBase::ROOT_OBJECT->Render(camera->ViewMat(), camera->ProjMat());
}

/// <summary>
/// 終了処理
/// </summary>
void PlayScene::Finalize()
{
	ObjectBase::ROOT_OBJECT->Finalize();
}
