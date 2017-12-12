//************************************************/
//* @file  :DefenseTarget.h
//* @brief :防衛対象
//* @date  :2017/12/12
//* @author:S.Katou
//************************************************/
#pragma once
#include "../StateObject.h"
#include "../../Physics/Collision/SL_Collider.h"

class DefenseTarget : public StateObject<DefenseTarget>
{
public:
	using DEFENSE_TARGET_CONSTANT = ObjectConstantNumber::DEFENSE_TARGET_CONSTANT;

private:
	//本体の当たり判定
	ShunLib::BoxCollider* m_collider;

public:
	DefenseTarget();
	~DefenseTarget();

	//初期化　終了
	void Initialize()override;
	void Finalize()override;

	//更新
	void Update()override;
};