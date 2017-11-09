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
	auto factory = ObjectFactory::GetInstance();

	auto p = factory->Create(PLAYER);
	auto v = factory->Create(COMMANDER);
	auto u = factory->Create(UNIT);
	//p->AddChild(v);
	//p->AddChild(u);
	m_objList.push_back(p);
	m_objList.push_back(v);
	m_objList.push_back(u);

	auto window = ShunLib::Window::GetInstance();
	
	//カメラ設定
	auto camera = ShunLib::MainCamera::GetInstance();
	camera->Pos(ShunLib::Vec3(0.0f, 10.0f, 15.0f));
	camera->Target(ShunLib::Vec3::Zero);
	camera->Aspect(static_cast<float>(window->Width() / window->Height()));

}

PlayScene::~PlayScene()
{
	SAFE_DELETE_INSIDE(m_objList);
}

/// <summary>
/// 初期化処理
/// </summary>
void PlayScene::Initialize()
{
	for (auto& v : m_objList)
	{
		v->Initialize();
	}
}

/// <summary>
/// 更新処理
/// </summary>
void PlayScene::Update()
{
	auto camera = ShunLib::MainCamera::GetInstance();
	camera->Update();

	for (auto v : m_objList)
	{
		v->Update();
	}
}

/// <summary>
/// 描画処理
/// </summary>
void PlayScene::Render()
{
	auto camera = ShunLib::MainCamera::GetInstance();
	
	for (auto v : m_objList)
	{
		v->Render(camera->ViewMat(), camera->ProjMat());
	}
}

/// <summary>
/// 終了処理
/// </summary>
void PlayScene::Finalize()
{
	for (auto v : m_objList)
	{
		v->Finalize();
	}
}
