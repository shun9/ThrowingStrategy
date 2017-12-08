//************************************************/
//* @file  :ObjectData.h
//* @brief :�I�u�W�F�N�g���g�p����f�[�^���܂Ƃ߂��N���X
//* @date  :2017/11/02
//* @author:S.Katou
//************************************************/
#pragma once
#include <SL_Math.h>
#include "ObjectConstantNumber.h"
#include "ObjectParamHolder.h"

class ObjectData
{
private:
	using TEAM = ObjectConstantNumber::TEAM;
	using OBJECT_LIST = ObjectConstantNumber::OBJECT_LIST;

protected:
	int m_hp;		   //����HP
	TEAM m_team;       //�`�[������
	OBJECT_LIST m_type;//���̃I�u�W�F�N�g�̎��

public:
	ObjectData():
		m_hp(10) //�K���Ȓl
	{}
	virtual ~ObjectData() {}

	//�_���[�W���󂯂�
	void TakeDamage(int damage) { m_hp -= damage; }

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
