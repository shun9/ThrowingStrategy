//************************************************/
//* @file  :Unit.h
//* @brief :召喚されるユニット
//* @date  :2017/11/13
//* @author:S.Katou
//************************************************/
#pragma once
#include "../StateObject.h"
#include "../../Physics/Collision/SL_Collider.h"

struct FlyingData;
class Unit :public StateObject<Unit>
{
private:
	int m_type;
	ShunLib::SphereCollider* m_collider;

public:
	Unit():StateObject(this) {}
	~Unit() {}

	//初期化　終了
	void Initialize()override;
	void Finalize()override;

	//他ユニットに持ち上げられる
	void ToBeLifted();

	//他ユニットに投げられる
	void ToBeThrow(const FlyingData& data);
};