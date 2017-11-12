//************************************************/
//* @file  :Commander.h
//* @brief :�w����
//* @date  :2017/11/12
//* @author:S.Katou
//************************************************/
#pragma once
#include "../StateObject.h"
#include "../../Physics/Collision/SL_Collider.h"

class Commander : public StateObject<Commander>
{
private:
	//���Ă鐔
	int m_capacity;

	//������
	float m_throwingPower;

	//������p�x
	float m_throwingAngle;

	ShunLib::BoxCollider* m_collider;

public:
	Commander();
	~Commander();

	////�������@�I��
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