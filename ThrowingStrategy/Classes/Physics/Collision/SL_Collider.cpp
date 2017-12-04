//************************************************/
//* @file  :Collider.cpp
//* @brief :�����蔻��I�u�W�F�N�g�̃N���X
//* @date  :2017/11/12
//* @author:S.Katou
//************************************************/
#include "SL_Collider.h"
#include "SL_CollisionManager.h"
#include "../../Object/ObjectBase.h"
#include "../../Util/Debugger/DebugMacro.h"

using namespace ShunLib;

//���R���X�g���N�^
//�����蔻����Ǘ�����N���X�ɓo�^
ICollider::ICollider() :
	m_parent(nullptr),
	m_shape(nullptr),
	m_callBack(NULL),
	m_isEntity(true),
	m_isDebugDraw(true)
{
	CollisionManager::GetInstance()->AddCollider(this);
}

//���R���X�g���N�^
//�����蔻����Ǘ�����N���X����폜
ICollider::~ICollider()
{
	CollisionManager::GetInstance()->RemoveCollider(this);
}

//�f�o�b�O�p�`��
void ICollider::DebugRender()
{
	if (m_isDebugDraw){
		m_shape->Render();
	}
}

void ShunLib::ICollider::Accept(ShunLib::Visitor * visitor)
{
	visitor->Visit(this);
	for (auto& v : m_hitList) {
		visitor->Visit(v);
	}
}

void ShunLib::ICollider::AddChildCollider(ICollider * child)
{
	m_childrenCollider.push_back(child);
	CollisionManager::GetInstance()->RemoveCollider(child);
}


//����̓����蔻��̍X�V
void SphereCollider::Update()
{
	if (m_parent != nullptr){
		Vec3 pos = m_parent->WorldPos();

		Shape()->CenterPoint(m_parent->WorldPos() + this->Offset());
	}
}

//����̓����蔻��̍X�V
void BoxCollider::Update()
{
	if (m_parent != nullptr)
	{
		Shape()->CenterPoint(m_parent->WorldPos() + this->Offset());
		Shape()->Size(m_parent->Scale());
	}
}
