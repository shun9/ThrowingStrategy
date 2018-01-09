//************************************************/
//* @file  :ObjectData.h
//* @brief :�I�u�W�F�N�g���g�p����f�[�^���܂Ƃ߂��N���X
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
	int m_hp;		   //����HP
	bool m_useGravity; //�d�͂̉e�����󂯂邩�ǂ���
	TEAM m_team;       //�`�[������
	OBJECT_LIST m_type;//���̃I�u�W�F�N�g�̎��

public:
	ObjectData(OBJECT_LIST type){
		m_type = type;
		Init();
	}
	virtual ~ObjectData() {}

	//������
	void Init() {
		m_hp = MaxHP();
		m_useGravity = true;
	};

	//�_���[�W���󂯂�
	void TakeDamage(int damage) { m_hp = ShunLib::Max(0, m_hp - damage); }

	//����ł��邩�ǂ���
	bool IsDead() { return m_hp <= 0; }

	//Getter
	float       Spd  () { return OBJ_PARAM(m_type).spd  ; }
	float       Power() { return OBJ_PARAM(m_type).power; }
	int	        MaxHP() { return OBJ_PARAM(m_type).maxHP; }
	int	        HP   () { return m_hp                   ; }
	TEAM		Team () { return m_team                 ; }
	OBJECT_LIST	Type () { return m_type                 ; }
	bool UseGravity  () { return m_useGravity; }

	//Setter
	void HP   (int hp           ) { m_hp = hp    ; }
	void Team (TEAM t           ) { m_team = t   ; }
	void Type (OBJECT_LIST type ) { m_type = type; }
	void UseGravity(bool useGra ) { m_useGravity = useGra; }
};
