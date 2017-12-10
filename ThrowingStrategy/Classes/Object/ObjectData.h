//************************************************/
//* @file  :ObjectData.h
//* @brief :オブジェクトが使用するデータをまとめたクラス
//* @date  :2017/11/02
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
	int m_hp;		   //現在HP
	TEAM m_team;       //チーム分け
	OBJECT_LIST m_type;//このオブジェクトの種類

public:
	ObjectData(OBJECT_LIST type){
		m_type = type;
		m_hp = MaxHP();
	}
	virtual ~ObjectData() {}

	//ダメージを受ける
	void TakeDamage(int damage) { m_hp -= damage; }

	//死んでいるかどうか
	bool IsDead() { return m_hp <= 0; }

	//Getter
	float       Spd  () { return OBJ_PARAM(m_type).spd  ; }
	float       Power() { return OBJ_PARAM(m_type).power; }
	int	        MaxHP() { return OBJ_PARAM(m_type).maxHP; }
	int	        HP   () { return m_hp; }
	TEAM		Team () { return m_team                 ; }
	OBJECT_LIST	Type () { return m_type                 ; }

	//Setter
	void HP   (int hp           ) { m_hp = hp; }
	void Team (TEAM t           ) { m_team = t   ; }
	void Type (OBJECT_LIST type ) { m_type = type; }
};
