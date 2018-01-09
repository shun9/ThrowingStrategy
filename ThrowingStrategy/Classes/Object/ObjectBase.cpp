//************************************************/
//* @file  :ObjectBase.cpp
//* @brief :�I�u�W�F�N�g
//* @date  :2018/01/05
//* @author:S.Katou
//************************************************/
#include "ObjectBase.h"

#include <SL_Conversion.h>
#include "ObjectModelHolder.h"
#include "../Main/SL_MyStepTimer.h"
#include "../Physics/PhysicsConstantNumber.h"
#include "../Util/SL_Camera.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="type"></param>
ObjectBase::ObjectBase(OBJECT_LIST type):
	ObjectNode(type),
	m_data(type)
{
	m_data.Init();
}

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
	auto pos = m_transform.Pos() + m_transform.Velocity() * timer->GetElapsedSeconds();
	if(m_data.UseGravity())pos.m_y -= GRAVITY;
	m_transform.Pos(pos);

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
/// ������
/// </summary>
void ObjectBase::Initialize()
{
	ObjectNode::Initialize();
	m_data.Init();
}

/// <summary>
/// �X�V
/// </summary>
void ObjectBase::Update()
{
	if (m_data.IsDead()) {
		m_isEnable = false;
	}
}

/// <summary>
/// �`��
/// </summary>
void ObjectBase::Render()
{
	auto model = ObjectModelHolder::GetInstance()->GetModel(this);
	auto camera = ShunLib::MainCamera::GetInstance();

	//�s��̌v�Z
	m_transform.CalcMat();

	//���f���̕`��
	if (model != nullptr)
	{
		//�e�����݂���Ȃ���W���e��������
		auto parent = dynamic_cast<ObjectBase*>(m_parent);
		if (parent != nullptr){
			model->Draw(parent->Transform().TransMat() * m_transform.WorldMat(), camera->ViewMat(), camera->ProjMat());
		}
		else {
			model->Draw(m_transform.WorldMat(), camera->ViewMat(), camera->ProjMat());
		}
	}
}
