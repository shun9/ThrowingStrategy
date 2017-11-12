//************************************************/
//* @file  :Commander.h
//* @brief :指揮官
//* @date  :2017/11/12
//* @author:S.Katou
//************************************************/
#pragma once
#include "../StateObject.h"
#include "../../Physics/Collision/SL_Collider.h"

class Commander : public StateObject<Commander>
{
private:
	//持てる数
	int m_capacity;

	//投擲力
	float m_throwingPower;

	//投げる角度
	float m_throwingAngle;

	ShunLib::BoxCollider* m_collider;

public:
	Commander();
	~Commander();

	////初期化　終了
	void Initialize()override;
	void Finalize()override;

	//Getter
	float ThrowingPower() { return m_throwingPower; }
	float ThrowingAngle() { return m_throwingAngle; }
	int   Capacity     () { return m_capacity     ; }

	//Setter
	void ThrowingPower(float p) { m_throwingPower = p; }
	void ThrowingAngle(float a) { m_throwingAngle = a; }
	void Capacity     (int   c) { m_capacity      = c; }
};