//************************************************/
//* @file  :Player.h
//* @brief :プレイヤー
//* @date  :2017/12/12
//* @author:S.Katou
//************************************************/
#pragma once
#include "../StateObject.h"
#include "../../Physics/Collision/SL_Collider.h"

class Unit;

class Player : public StateObject<Player>
{
public:
	using PLAYER_CONSTANT = ObjectConstantNumber::PLAYER_CONSTANT;

private:
	//本体の当たり判定
	ShunLib::SphereCollider* m_collider;

public:
	Player();
	~Player();

	//初期化　終了
	void Initialize()override;
	void Finalize()override;

	//ユニットを整列する
	void AlignUnits();

	
	//持っているユニットの数
	int HavingUnitNum();

	//持っているユニットの一覧
	std::vector<Unit*>& HavingUnitList();

	/*--Getter--*/
	ShunLib::SphereCollider* Collider() { return m_collider; }
};