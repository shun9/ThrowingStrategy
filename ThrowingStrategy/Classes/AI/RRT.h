//************************************************/
//* @file  :RRT.h
//* @brief :RRTによる経路探索を行うクラス
//* @date  :2018/01/12
//* @author:S.Katou
//************************************************/
#pragma once

#include <vector>
#include <deque>
#include <memory>
#include <SL_Math.h>
#include <SL_Factory.h>
#include "../Object/SL_Shape.h"

class RRT
{
protected:
	//RRT用のノード
	struct Node
	{
		ShunLib::Vec3 point;
		Node* parent;
		std::vector<Node*>children;
		Node() :parent(nullptr) {}
	};

public:
	using Vec3 = ShunLib::Vec3;
	using Route = std::deque<Vec3>;

protected:
	//ノード生成用のファクトリー
	ShunLib::Factory<RRT::Node>m_nodeFactory;

	Node* m_target;//目標地点
	Node* m_start; //スタート地点
	float m_spd;   //1回の移動量

	//ルート
	Route m_route;

	//二次元上で探索をするかどうか
	bool m_is2D;

public:
	RRT(Vec3 start, Vec3 target, float spd);
	~RRT();

	//ルートの生成
	void CreateRoute();

	/*--Setter--*/
	void Is2D(bool is2D) { m_is2D = is2D; }

	/*--Getter--*/
	bool Is2D() { return m_is2D; }
	Route& GetRoute() { return m_route; }

protected:
	//最も近い点を探す
	Node* SearchNearPoint(const Vec3& point);

	//最も近い点を探す (再帰用)
	Node* SearchNearPoint(const Vec3& point, Node* parentPoint, RRT::Node* nearestPoint,float dist);

	//線分が障害物と接しているかどうか
	bool IsHitSegmentAndObstacle(const ShunLib::Segment& segment);

	//ランダムな点を取得
	RRT::Node* GetRandomPoint();

	//目的地に到達したかどうか
	bool IsReachedTarget(Node* node);

	//ルートを設定
	void SetRoute();

	//探索エリアの最大値と最小値
	float AreaMaxX();
	float AreaMaxY();
	float AreaMaxZ();
	float AreaMinX();
	float AreaMinY();
	float AreaMinZ();
};