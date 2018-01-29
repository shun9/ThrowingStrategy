//************************************************/
//* @file  :StageObject.cpp
//* @brief :ステージに配置するオブジェクトのまとめ
//* @date  :2018/01/17
//* @author:S.Katou
//************************************************/
#include "StageObject.h"
#include "../../Physics/Collision/SL_CollisionManager.h"
#include "../../Util/SL_Camera.h"
#include "../../Util/BasicShapeModelRenderer.h"

using namespace ShunLib;

/// <summary>
/// コンストラクタ
/// </summary>
Block::Block():
	ObjectBase(ObjectConstantNumber::BLOCK)
{
	m_data.Team(ObjectConstantNumber::TEAM::NONE);

	//当たり判定の設定
	m_collider = new BoxCollider(ShunLib::COLLIDER_LAYER::STATIC);
	m_collider->Parent(this);
	m_collider->IsStatic(true);

	m_color = ShunLib::Colors::WHITE;
}

Block::~Block()
{
	SAFE_DELETE(m_collider);
}

/// <summary>
/// 箱の初期化
/// </summary>
void Block::Initialize()
{
	//当たり判定を使用する
	m_collider->IsEnable(true);

	//基底クラスの初期化
	ObjectBase::Initialize();
}

/// <summary>
/// 箱の描画
/// </summary>
void Block::Render()
{
	auto camera = ShunLib::MainCamera::GetInstance();
	auto renderer = BasicShapeRenderer::GetInstance();

	//行列の計算
	m_transform.CalcMat();

	renderer->DrawCube(m_transform.WorldMat(), camera->ViewMat(), camera->ProjMat(), m_color);
}

/// <summary>
/// 終了処理
/// </summary>
void Block::Finalize()
{
	//当たり判定を使用する
	m_collider->IsEnable(false);
}

