//************************************************/
//* @file  :Player.h
//* @brief :�v���C���[
//* @date  :2017/10/30
//* @author:S.Katou
//************************************************/
#pragma once
#include "../StateObject.h"
#include "../../Physics/Collision/SL_Collider.h"

class SphereCollider;

class Player : public StateObject<Player>
{
private:
	ShunLib::SphereCollider* m_collider;

public:
	Player():StateObject(this) {}
	~Player() {}

	////�������@�I��
	void Initialize()override;
	void Finalize()override;

	void CollisionCallBack(ObjectBase* obj);
};