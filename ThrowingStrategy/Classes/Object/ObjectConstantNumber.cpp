//************************************************/
//* @file  :ObjectConstantNumber.cpp
//* @brief :�I�u�W�F�N�g�֘A�̒萔
//* @date  :2017/12/12
//* @author:S.Katou
//************************************************/
#include "ObjectConstantNumber.h"

using namespace ShunLib;

//��Ԃ��������I�u�W�F�N�g�ꗗ
const ObjectConstantNumber::OBJECT_LIST ObjectConstantNumber::STATE_OBJECT[5] = {
	OBJECT_LIST::PLAYER,
	OBJECT_LIST::COMMANDER,
	OBJECT_LIST::UNIT,
	OBJECT_LIST::SUMMONER,
	OBJECT_LIST::DEFENSE_TARGET,
};

//�v���C���[�֘A
const float ObjectConstantNumber::PLAYER_CONSTANT::COLLIDER_SIZE   = 1.0f;
const Vec3  ObjectConstantNumber::PLAYER_CONSTANT::COLLIDER_OFFSET = { 0.0f,1.0f,0.0f };
const Vec3  ObjectConstantNumber::PLAYER_CONSTANT::HP_GAUGE_OFFSET = { 0.0f,0.0f,4.0f };

//���j�b�g�֘A
const Vec3  ObjectConstantNumber::UNIT_CONSTANT::COLLIDER_OFFSET      = { 0.0f, 0.6f, 0.0f };
const Vec3  ObjectConstantNumber::UNIT_CONSTANT::HP_GAUGE_OFFSET      = { 0.0f, 0.0f, 2.0f };
const float ObjectConstantNumber::UNIT_CONSTANT::COLLIDER_BODY_SIZE   = 1.0f;
const float ObjectConstantNumber::UNIT_CONSTANT::COLLIDER_ATTACK_SIZE = 2.0f;
const float ObjectConstantNumber::UNIT_CONSTANT::COLLIDER_CHASE_SIZE  = 14.0f;

//�h�q�Ώۊ֘A
const float ObjectConstantNumber::DEFENSE_TARGET_CONSTANT::MODEL_SCALE     = 0.4f;
const Vec3  ObjectConstantNumber::DEFENSE_TARGET_CONSTANT::COLLIDER_OFFSET = { 0.0f,5.0f,0.0f };
const Vec3  ObjectConstantNumber::DEFENSE_TARGET_CONSTANT::COLLIDER_SIZE   = { 4.0f,10.0f,4.0f };
const Vec3  ObjectConstantNumber::DEFENSE_TARGET_CONSTANT::HP_GAUGE_OFFSET = { 0.0f,0.0f,8.0f };

//�����t�֘A
const Vec3  ObjectConstantNumber::SUMMONER_CONSTANT::COLLIDER_OFFSET = { 0.0f,0.0f,0.0f };
const Vec3  ObjectConstantNumber::SUMMONER_CONSTANT::COLLIDER_SIZE   = { 3.0f,2.0f,3.0f };
const Vec3  ObjectConstantNumber::SUMMONER_CONSTANT::HP_GAUGE_OFFSET = { 0.0f,0.0f,0.0f };
