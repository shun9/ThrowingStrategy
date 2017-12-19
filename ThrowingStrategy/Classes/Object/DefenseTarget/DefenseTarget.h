//************************************************/
//* @file  :DefenseTarget.h
//* @brief :hqÎÛ
//* @date  :2017/12/12
//* @author:S.Katou
//************************************************/
#pragma once
#include "../StateObject.h"
#include "../../Physics/Collision/SL_Collider.h"

class HPGauge;

class DefenseTarget : public StateObject<DefenseTarget>
{
public:
	using DEFENSE_TARGET_CONSTANT = ObjectConstantNumber::DEFENSE_TARGET_CONSTANT;

private:
	//{ÌÌ½è»è
	ShunLib::BoxCollider* m_collider;
	
	//HPQ[W
	HPGauge* m_hpGauge;

public:
	DefenseTarget();
	~DefenseTarget();

	//ú»@I¹
	void Initialize()override;
	void Finalize()override;

	//XV
	void Update()override;
};