//************************************************/
//* @file  :Player.h
//* @brief :プレイヤー
//* @date  :2017/10/30
//* @author:S.Katou
//************************************************/
#pragma once
#include "../StateObject.h"
#include "../../Physics/Collision/SL_Collider.h"

class Unit;

class Player : public StateObject<Player>
{
private:
	ShunLib::SphereCollider* m_collider;

public:
	Player():StateObject(this){}
	~Player() {}

	////初期化　更新　終了
	void Initialize()override;
	void Finalize()override;

	ShunLib::SphereCollider* Collider() { return m_collider; }
	
	//持っているユニットの数
	int HavingUnitNum();

	//当たり判定用コールバック
	void CollisionCallBack(ObjectBase* obj);
};