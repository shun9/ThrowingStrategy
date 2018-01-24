//************************************************/
//* @file  :CollisionManager.cpp
//* @brief :当たり判定を管理するクラス
//* @date  :2017/12/08
//* @author:S.Katou
//************************************************/
#include "SL_CollisionManager.h"
#include "../../Util/Debugger/DebugMacro.h"
#include "../../Object/ObjectBase.h"

using namespace ShunLib;

/// <summary>
/// レイヤーのサイズを個別に設定
/// </summary>
/// <param name="layerNum">レイヤー番号</param>
/// <param name="layerSize">サイズ</param>
void CollisionManager::ResizeLayer(int layerNum, int layerSize)
{
	m_colliderList[layerNum].reserve(layerSize);
}

//更新
void CollisionManager::Update()
{
	//当たり判定の更新
	//当たっているオブジェクト一覧を初期化
	for (auto& layer : m_colliderList) {

		for (auto& v : layer) {
			v->Update();
			v->ResetList();
		}
	}

	//当たり判定
	for (int i = 0; i < COLLIDER_LAYER_END; i++)
	{
		for (int j = i; j < COLLIDER_LAYER_END; j++)
		{
			//動かない者同士は判定を取らない
			if (i == STATIC && j == STATIC){
				continue;
			}

			//レイヤー間で当たり判定
			CollisionLayer(i, j);
		}
	}
}

//描画
void CollisionManager::Render()
{
	for (auto& layer : m_colliderList)
	{
		for (auto& v : layer)
		{
			Debug v->DebugRender();
		}
	}
}

/// <summary>
/// 当たり判定を外す
/// </summary>
void CollisionManager::RemoveCollider(ICollider * col)
{
	std::vector<ICollider*>::iterator tmp;

	for (auto& layer : m_colliderList) {
		//指定された当たり判定を探す
		tmp = std::find(layer.begin(), layer.end(), col);

		//見つかったら削除して終了
		if (tmp != layer.end()) {
			layer.erase(tmp);
			return;
		}
	}
}

/// <summary>
/// コンストラクタ
/// </summary>
CollisionManager::CollisionManager()
{
	m_colliderList.resize(COLLIDER_LAYER_END);

	m_colliderList[RIGID].reserve(500);
	m_colliderList[STATIC].reserve(100);
	m_colliderList[TRIGGER].reserve(500);
}

/// <summary>
/// レイヤーごとに当たり判定
/// </summary>
/// <param name="layer1">1つ目のレイヤーのインデックス</param>
/// <param name="layer2">2つ目のレイヤーのインデックス</param>
void ShunLib::CollisionManager::CollisionLayer(int layer1, int layer2)
{
	//各レイヤーの大きさ
	int size1 = (int)m_colliderList[layer1].size();
	int size2 = (int)m_colliderList[layer2].size();

	for (int i = 0; i < size1; i++)
	{
		for (int j = 0; j < size2; j++)
		{
			//親が同じ場合は、判定を取らない
			if (m_colliderList[layer1][i]->Parent() != nullptr
			&&  m_colliderList[layer1][i]->Parent() == m_colliderList[layer2][j]->Parent()) {
				continue;
			}

			//どちらかが使用されていない状態なら、判定を取らない
			if (!(m_colliderList[layer1][i]->IsEnable()
			&&    m_colliderList[layer2][j]->IsEnable())) {
				continue;
			}

			//当たり判定
			Collision(m_colliderList[layer1][i],m_colliderList[layer2][j]);
		}
	}
}
