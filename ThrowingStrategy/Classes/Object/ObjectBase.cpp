//************************************************/
//* @file  :ObjectBase.cpp
//* @brief :�I�u�W�F�N�g
//* @date  :2017/11/15
//* @author:S.Katou
//************************************************/
#include "ObjectBase.h"

#include <SL_Conversion.h>
#include "../Main/SL_MyStepTimer.h"
#include "../Physics/PhysicsConstantNumber.h"
#include "ObjectModelHolder.h"

//�S�ẴI�u�W�F�N�g�̐e
//�S�ẴI�u�W�F�N�g�������ɕR�Â���
ObjectBase* ObjectBase::ROOT_OBJECT;

void ObjectBase::InitializeRootObject()
{
	ROOT_OBJECT = new ObjectBase(true);
	ObjectBase::ROOT_OBJECT->Type(ObjectConstantNumber::ROOT);
	ObjectBase::ROOT_OBJECT->LocalPos(ShunLib::Vec3(0.0f, 0.0f, 0.0f));
}

void ObjectBase::FinalizeRootObject()
{
	SAFE_DELETE(ROOT_OBJECT);
}


/// <summary>
/// �e��ݒ肷��
/// </summary>
void ObjectBase::SetParent(ObjectBase * parent)
{
	if (m_parent != nullptr)m_parent->RemoveChild(this);
	m_parent = parent;
	//�e�����݂��A���[�g�ł͂Ȃ��Ƃ��e�f�[�^���e��������
	if (parent != nullptr && parent->Type() != ObjectConstantNumber::ROOT) {
		//���W�𑊑ΓI�Ɍ���
		this->LocalPos(this->LocalPos() - m_parent->WorldPos());
		this->Rotation(ShunLib::Vec3::Zero);
	}
}

/// <summary>
/// �w�肵���q���폜����
/// </summary>
void ObjectBase::RemoveChild(ObjectBase * child)
{
	//�q�����Ȃ���Ή������Ȃ�
	if (m_children.empty())return;

	auto tmpChild = std::find(m_children.begin(), m_children.end(), child);

	if (tmpChild != m_children.end()) {
		//�e�̏����q�ɓn��
		child->LocalPos(child->WorldPos());
		child->Rotation(child->WorldRotation());
		
		//�q��؂藣��
		m_children.erase(tmpChild);
		m_children.shrink_to_fit();
	}
}

/// <summary>
/// �ړ�������
/// </summary>
void ObjectBase::Move()
{
	using namespace ShunLib;
	auto timer = MyStepTimer::GetInstance();

	//�ړ����x�𐧌�
	if (this->Velocity().Length() > this->Spd()) {
		this->Velocity(this->Velocity().Normalize()*this->Spd());
	}

	//�ړ�
	m_pos += this->Velocity() * timer->GetElapsedSeconds();

	//�����Ă���������v�Z����
	if (this->Velocity().Length() > 1.0f)
	{
		float rotY = ShunLib::ToAngle(std::atan2(this->Velocity().m_z, this->Velocity().m_x)) - 90.0f;
		m_rotation.m_y = rotY;
	}

	//���C��������
	m_velocity *= FRICTION;
}


/// /// <summary>
/// �`�� �e�p
/// </summary>
void ObjectBase::Render(const Matrix & view, const Matrix & proj)
{
	//�e������ꍇ�͂����ł͕`�悵�Ȃ�
	if (m_parent != nullptr)return;

	this->RenderChild(view, proj);
}


/// <summary>
/// �`�� �q�p
/// </summary>
void ObjectBase::RenderChild(const Matrix & view, const Matrix & proj)
{
	auto model = ObjectModelHolder::GetInstance()->GetModel(this);

	//�s��X�V
	CalcMat();

	//���f�������݂���Ȃ�Ε`��
	if (model != nullptr) {
		//���f���`��
		model->Draw(m_world, view, proj);
	}

	//�q�̕`��
	for (auto& v : m_children) {
		v->RenderChild(view, proj);
	}
}


/// <summary>
/// ���g�̍s����v�Z����
/// </summary>
void ObjectBase::CalcMat()
{
	m_world = Matrix::Identity;

	//�g��@�k��
	m_world *= Matrix::CreateScale(this->Scale());

	//�q�̉�]
	m_world *= Matrix::CreateRotationZ(this->Rotation().m_z);
	m_world *= Matrix::CreateRotationX(this->Rotation().m_x);
	m_world *= Matrix::CreateRotationY(this->Rotation().m_y);

	//�q�̈ړ�
	m_world *= Matrix::CreateTranslation(this->LocalPos());

	//�e�̍s����e��������
	ObjectBase* parent = this->Parent();
	if (parent != nullptr){
		m_world *= m_parent->World();
	}
}
