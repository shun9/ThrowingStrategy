//************************************************/
//* @file  :ObjectData.h
//* @brief :オブジェクトが使用するデータをまとめたクラス
//* @date  :2018/01/05
//* @author:S.Katou
//************************************************/
#pragma once
#include <SL_Math.h>
#include "ObjectConstantNumber.h"
#include "ObjectParamHolder.h"

class ObjectData
{
public:
	using TEAM = ObjectConstantNumber::TEAM;
	using OBJECT_LIST = ObjectConstantNumber::OBJECT_LIST;

protected:
	int m_hp;		           //現在HP
	bool m_useGravity;         //重力の影響を受けるかどうか
	bool m_shouldLimitVelocity;//速度に制限をかけるかどうか
	bool m_shouldChangeDir;    //向いている方向を変えるかどうか
	TEAM m_team;               //チーム分け
	OBJECT_LIST m_type;        //このオブジェクトの種類

public:
	ObjectData(OBJECT_LIST type){
		m_type = type;
		Init();
	}
	virtual ~ObjectData() {}

	//初期化
	void Init() {
		m_hp = MaxHP();
		m_useGravity = true;
		m_shouldLimitVelocity = true;
		m_shouldChangeDir = true;
	};

	//ダメージを受ける
	void TakeDamage(int damage) { m_hp = ShunLib::Max(0, m_hp - damage); }

	//死んでいるかどうか
	bool IsDead() { return m_hp <= 0; }

	//Getter
	float       Spd    () { return OBJ_PARAM(m_type).spd  ; }
	float       Power  () { return OBJ_PARAM(m_type).power; }
	int	        MaxHP  () { return OBJ_PARAM(m_type).maxHP; }
	int	        HP     () { return m_hp                   ; }
	TEAM		Team   () { return m_team                 ; }
	OBJECT_LIST	Type   () { return m_type                 ; }
	bool UseGravity    () { return m_useGravity; }
	bool ShouldLimitVel() { return m_shouldLimitVelocity; }
	bool ShouldChangeDir() { return m_shouldChangeDir; }

	//Setter
	void HP   (int hp              ) { m_hp = hp    ; }
	void Team (TEAM t              ) { m_team = t   ; }
	void Type (OBJECT_LIST type    ) { m_type = type; }
	void UseGravity(bool use       ) { m_useGravity = use; }
	void ShouldLimitVel(bool should) { m_shouldLimitVelocity = should; }
	void ShouldChangeDir(bool should) { m_shouldChangeDir = should; }
};
