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
	using Vec3 = ShunLib::Vec3;
	using Matrix = ShunLib::Matrix;

protected:
	Vec3 m_pos;        //�ʒu
	Vec3 m_rotation;   //��]�p�x
	Vec3 m_velocity;   //�ړ����x
	float m_scale;     //�g�嗦
	TEAM m_team;       //�`�[������
	OBJECT_LIST m_type;//���̃I�u�W�F�N�g�̎��

public:
	ObjectData() :
		m_pos({ 0.0f,0.0f,0.0f }),
		m_rotation({ 0.0f,0.0f,0.0f }),
		m_velocity({ 0.0f,0.0f,0.0f }),
		m_scale(1.0f)
	{}
	virtual ~ObjectData() {}

	//Getter
	Vec3		 Pos     () { return m_pos                  ; }
	Vec3		 Rotation() { return m_rotation             ; }
	Vec3		 Velocity() { return m_velocity             ; }
	float		 Scale   () { return m_scale                ; }
	float		 Spd     () { return OBJ_PARAM(m_type).spd  ; }
	int			 MaxHP   () { return OBJ_PARAM(m_type).maxHP; }
	int			 Power   () { return OBJ_PARAM(m_type).power; }
	TEAM		 Team    () { return m_team                 ; }
	OBJECT_LIST	 Type    () { return m_type                 ; }

	//Setter
	void Pos     (const Vec3& pos ) { m_pos      = pos  ; }
	void Rotation(const Vec3& rot ) { m_rotation = rot  ; }
	void Velocity(const Vec3& vel ) { m_velocity = vel  ; }
	void Scale   (float scale     ) { m_scale    = scale; }
	void Team    (TEAM t          ) { m_team     = t    ; }
	void Type    (OBJECT_LIST type) { m_type     = type ; }
};
