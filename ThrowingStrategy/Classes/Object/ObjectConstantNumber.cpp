//************************************************/
//* @file  :ObjectConstantNumber.cpp
//* @brief :オブジェクト関連の定数
//* @date  :2017/12/12
//* @author:S.Katou
//************************************************/
#include "ObjectConstantNumber.h"

using namespace ShunLib;

//状態を持ったオブジェクト一覧
const ObjectConstantNumber::OBJECT_LIST ObjectConstantNumber::STATE_OBJECT[5] = {
	OBJECT_LIST::PLAYER,
	OBJECT_LIST::COMMANDER,
	OBJECT_LIST::UNIT,
	OBJECT_LIST::SUMMONER,
	OBJECT_LIST::DEFENSE_TARGET,
};

//プレイヤー関連
const float ObjectConstantNumber::PLAYER_CONSTANT::COLLIDER_SIZE   = 1.0f;
const Vec3  ObjectConstantNumber::PLAYER_CONSTANT::COLLIDER_OFFSET = { 0.0f,1.0f,0.0f };
const Vec3  ObjectConstantNumber::PLAYER_CONSTANT::HP_GAUGE_OFFSET = { 0.0f,0.0f,4.0f };

//ユニット関連
const Vec3  ObjectConstantNumber::UNIT_CONSTANT::COLLIDER_OFFSET      = { 0.0f, 0.6f, 0.0f };
const Vec3  ObjectConstantNumber::UNIT_CONSTANT::HP_GAUGE_OFFSET      = { 0.0f, 0.0f, 2.0f };
const float ObjectConstantNumber::UNIT_CONSTANT::COLLIDER_BODY_SIZE   = 1.0f;
const float ObjectConstantNumber::UNIT_CONSTANT::COLLIDER_ATTACK_SIZE = 2.0f;
const float ObjectConstantNumber::UNIT_CONSTANT::COLLIDER_CHASE_SIZE  = 14.0f;

//防衛対象関連
const float ObjectConstantNumber::DEFENSE_TARGET_CONSTANT::MODEL_SCALE     = 0.4f;
const Vec3  ObjectConstantNumber::DEFENSE_TARGET_CONSTANT::COLLIDER_OFFSET = { 0.0f,5.0f,0.0f };
const Vec3  ObjectConstantNumber::DEFENSE_TARGET_CONSTANT::COLLIDER_SIZE   = { 4.0f,10.0f,4.0f };
const Vec3  ObjectConstantNumber::DEFENSE_TARGET_CONSTANT::HP_GAUGE_OFFSET = { 0.0f,0.0f,8.0f };

//召喚師関連
const Vec3  ObjectConstantNumber::SUMMONER_CONSTANT::COLLIDER_OFFSET = { 0.0f,0.0f,0.0f };
const Vec3  ObjectConstantNumber::SUMMONER_CONSTANT::COLLIDER_SIZE   = { 3.0f,2.0f,3.0f };
const Vec3  ObjectConstantNumber::SUMMONER_CONSTANT::HP_GAUGE_OFFSET = { 0.0f,0.0f,0.0f };
