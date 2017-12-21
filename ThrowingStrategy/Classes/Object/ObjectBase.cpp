//************************************************/
//* @file  :ObjectBase.cpp
//* @brief :�I�u�W�F�N�g
//* @date  :2017/12/21
//* @author:S.Katou
//************************************************/
#include "ObjectBase.h"

#include <SL_Conversion.h>
#include "../Main/SL_MyStepTimer.h"
#include "../Physics/PhysicsConstantNumber.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="type"></param>
ObjectBase::ObjectBase(OBJECT_LIST type):
	m_data(type)
{}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ObjectBase::~ObjectBase(){

}

/// <summary>
/// �ړ�������
/// </summary>
void ObjectBase::Move()
{
	using namespace ShunLib;
	auto timer = MyStepTimer::GetInstance();

	//�ړ����x�𐧌�
	if (m_transform.Velocity().Length() > m_data.Spd()) {
		m_transform.Velocity(m_transform.Velocity().Normalize()*m_data.Spd());
	}

	//�ړ�
	m_transform.Pos(m_transform.Pos() + m_transform.Velocity() * timer->GetElapsedSeconds());

	//�����Ă���������v�Z����
	//�ړ����̂݌v�Z
	//�x�̂݌v�Z�@���グ���茩�������肷�邱�Ƃ͂Ȃ�
	if (m_transform.Velocity().Length() > 1.0f)
	{
		Vec3 rot = m_transform.Rotation();

		rot.m_y = ToAngle(std::atan2(m_transform.Velocity().m_z, m_transform.Velocity().m_x)) - 90.0f;
		m_transform.Rotation(rot);
	}

	//���C��������
	m_transform.Velocity(m_transform.Velocity() * FRICTION);
}

/// <summary>
/// �`��
/// </summary>
void ObjectBase::Render()
{
}
