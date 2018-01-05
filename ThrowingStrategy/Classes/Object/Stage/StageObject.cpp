#include "StageObject.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
Block::Block():
	ObjectBase(ObjectConstantNumber::BLOCK)
{
	m_data.Team(ObjectConstantNumber::TEAM::NONE);

	//�����蔻��̐ݒ�
	m_collider = new ShunLib::BoxCollider();
	m_collider->Parent(this);
	m_collider->Offset(ShunLib::Vec3(0.0f, 0.51f, 0.0f));
	m_collider->IsStatic(true);
}

Block::~Block()
{
	SAFE_DELETE(m_collider);
}
