//************************************************/
//* @file  :Collider.cpp
//* @brief :�����蔻��I�u�W�F�N�g�̃N���X
//* @date  :2017/11/12
//* @author:S.Katou
//************************************************/
#include "SL_Collider.h"
#include "SL_CollisionManager.h"
#include "../../Object/ObjectBase.h"

//����̓����蔻��̍X�V
void ShunLib::ICollider::Update()
{
	if (m_parent != nullptr)
	{	
		Shape()->CenterPoint(m_parent->Pos() + this->Offset());
	}
}

//���R���X�g���N�^
//�����蔻����Ǘ�����N���X�ɓo�^
ShunLib::ICollider::ICollider() :
	m_parent(nullptr),
	m_shape(nullptr),
	m_callBack(NULL)
{
	CollisionManager::GetInstance()->AddCollider(this);
}

//���R���X�g���N�^
//�����蔻����Ǘ�����N���X����폜
ShunLib::ICollider::~ICollider()
{
	CollisionManager::GetInstance()->RemoveCollider(this);
}

//�f�o�b�O�p�`��
void ShunLib::ICollider::DebugRender()
{
	m_shape->Render();
}
