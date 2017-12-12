//************************************************/
//* @file  :ObjectConstantNumber.cpp
//* @brief :オブジェクト関連の定数
//* @date  :2017/12/11
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
const float ObjectConstantNumber::PLAYER_CONSTANT::COLLIDER_SIZE = 1.0f;
const Vec3  ObjectConstantNumber::PLAYER_CONSTANT::COLLIDER_OFFSET = ShunLib::Vec3::UnitY;

const float ObjectConstantNumber::DEFENSE_TARGET_CONSTANT::MODEL_SCALE = 0.4f;
const Vec3  ObjectConstantNumber::DEFENSE_TARGET_CONSTANT::COLLIDER_OFFSET = { 0.0f,5.0f,0.0f };
const Vec3  ObjectConstantNumber::DEFENSE_TARGET_CONSTANT::COLLIDER_SIZE   = { 4.0f,10.0f,4.0f };
