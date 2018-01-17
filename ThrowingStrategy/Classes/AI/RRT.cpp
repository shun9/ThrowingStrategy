//************************************************/
//* @file  :RRT.cpp
//* @brief :RRTによる経路探索を行うクラス
//* @date  :2018/01/12
//* @author:S.Katou
//************************************************/
#include "RRT.h"
#include <functional>
#include <SL_RandomNumber.h>

using namespace ShunLib;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="start">初期位置</param>
/// <param name="target">目標地点</param>
/// <param name="spd">1回の移動量</param>
RRT::RRT(Vec3 start, Vec3 target, float spd):
	m_is2D(false),
	m_spd(spd)
{
	m_start = m_nodeFactory.Create();
	m_target = m_nodeFactory.Create();
	m_start->point = start;
	m_target->point = target;
}

/// <summary>
/// デストラクタ
/// </summary>
RRT::~RRT()
{
	m_nodeFactory.AllDelete();
}

/// <summary>
/// ルートの生成
/// </summary>
void RRT::CreateRoute()
{
	Node* node = nullptr;

	//二次元ならば高さをそろえる
	if (m_is2D){
		m_target->point.m_y = m_start->point.m_y;
	}

	//ターゲットに到達するまでループ
	while (!(IsReachedTarget(node))){
		//ランダムな点を取得
		node = GetRandomPoint();

		//最も近い点を探す
		Node* parent = SearchNearPoint(node->point);
		node->point = (node->point - parent->point).Normalize() * m_spd;

		//木構造に追加
		parent->children.push_back(node);
		node->parent = parent;
	}

	//目的地とつなげる
	node->children.push_back(m_target);
	m_target->parent = node;

	//ルートを設定
	SetRoute();
}

/// <summary>
/// 最も近い点を探す
/// </summary>
RRT::Node * RRT::SearchNearPoint(const Vec3& point)
{
	Node* nearPoint = m_start;
	float dist = (nearPoint->point - point).Length();

	//子の点も探す
	for (int i = 0; i < (int)m_start->children.size(); i++){
		nearPoint = SearchNearPoint(point, m_start->children[i], nearPoint, dist);
	}

	return nearPoint;
}

/// <summary>
/// 最も近い点を探す
/// </summary>
/// <param name="point">対象の点</param>
/// <param name="nearestPoint">次に探す点</param>
/// <param name="nearestPoint">現状で最も近い点</param>
/// <param name="nearestPoint">現状で最も近い距離</param>
RRT::Node* RRT::SearchNearPoint(const Vec3 & point, RRT::Node* nextPoint, RRT::Node* nearestPoint, float distance)
{
	Node* nearPoint = nearestPoint;
	Vec3 vec = (nextPoint->point - point);

	//最短距離よりも近ければ更新
	float dist = vec.Length();
	if (dist < distance){
		nearPoint = nextPoint;
	}

	//子の点も探す
	for (int i = 0; i < (int)nextPoint->children.size(); i++) {
		nearPoint = SearchNearPoint(point, nextPoint->children[i], nearPoint, dist);
	}

	return nearPoint;
}

/// <summary>
/// 線分と障害物が接しているかどうか
/// </summary>
/// <returns></returns>
bool RRT::IsHitSegmentAndObstacle(const ShunLib::Segment& segment)
{
	return false;
}

/// <summary>
/// ランダムな点を取得
/// </summary>
RRT::Node* RRT::GetRandomPoint()
{
	Node* node = m_nodeFactory.Create();
	RandomNumber rn;

	//座標をランダムに取得
	node->point.m_x = rn(AreaMinX(), AreaMaxX());
	node->point.m_z = rn(AreaMinZ(), AreaMaxZ());

	//二次元の場合はY座標を初期位置に合わせる
	if (m_is2D){
		node->point.m_y = m_start->point.m_y;
	}
	else{
		node->point.m_y = rn(AreaMinY(), AreaMaxY());
	}

	return node;
}

/// <summary>
/// 目的地に到達したかどうか
/// </summary>
bool RRT::IsReachedTarget(Node* node)
{
	if (node == nullptr){
		return false;
	}

	float dist = (m_target->point - node->point).Length();

	//ターゲットまでの距離が1回で移動できる範囲ならtrue
	if (dist < m_spd){
		return true;
	}
	return false;
}

/// <summary>
/// ルートを設定
/// </summary>
void RRT::SetRoute()
{
	m_route.push_front(m_target->point);

	//再帰用関数
	std::function<void(Node*)> SetRoute = [&](Node* node) {
		if (node->parent == nullptr)return;
		m_route.push_front(node->parent->point);
		SetRoute(node->parent);
	};

	//再帰
	SetRoute(m_target);
}

/// <summary>
/// 探索エリアのX座標の最大値
/// </summary>
float RRT::AreaMaxX()
{
	float max = m_target->point.m_x > m_start->point.m_x ? m_target->point.m_x : m_start->point.m_x;
	return max;
}

/// <summary>
/// 探索エリアのY座標の最大値
/// </summary>
float RRT::AreaMaxY()
{
	float max = m_target->point.m_y > m_start->point.m_y ? m_target->point.m_y : m_start->point.m_y;
	return max;
}

/// <summary>
/// 探索エリアのZ座標の最大値
/// </summary>
float RRT::AreaMaxZ()
{
	float max = m_target->point.m_z > m_start->point.m_z ? m_target->point.m_z : m_start->point.m_z;
	return max;
}

/// <summary>
/// 探索エリアのX座標の最小値
/// </summary>
float RRT::AreaMinX()
{
	float min = m_target->point.m_x < m_start->point.m_x ? m_target->point.m_x : m_start->point.m_x;
	return min;
}

/// <summary>
/// 探索エリアのY座標の最小値
/// </summary>
float RRT::AreaMinY()
{
	float min = m_target->point.m_y < m_start->point.m_y ? m_target->point.m_y : m_start->point.m_y;
	return min;
}

/// <summary>
/// 探索エリアのZ座標の最小値
/// </summary>
float RRT::AreaMinZ()
{
	float min = m_target->point.m_z < m_start->point.m_z ? m_target->point.m_z : m_start->point.m_z;
	return min;
}
