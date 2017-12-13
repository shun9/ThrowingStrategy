//************************************************/
//* @file  :Commander.h
//* @brief :wŠöŠ¯
//* @date  :2017/11/12
//* @author:S.Katou
//************************************************/
#pragma once
#include "../StateObject.h"
#include "../../Physics/Collision/SL_Collider.h"

class Commander : public StateObject<Commander>
{
private:
	//‚Ä‚é”
	int m_capacity;

	ShunLib::SphereCollider* m_collider;

public:
	Commander();
	~Commander();

	////‰Šú‰»@I—¹
	void Initialize()override;
	void Finalize()override;

	//Getter
	int Capacity() { return m_capacity; }

	//Setter
	void Capacity(int c) { m_capacity = c; }
};