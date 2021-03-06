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

	ShunLib::SphereCollider* m_collider;

public:
	Commander();
	~Commander();

	////初期化　終了
	void Initialize()override;
	void Finalize()override;

	//Getter
	int Capacity() { return m_capacity; }

	//Setter
	void Capacity(int c) { m_capacity = c; }
};