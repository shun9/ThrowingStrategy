//************************************************/
//* @file  :Collider.cpp
//* @brief :�����蔻��I�u�W�F�N�g�̃N���X
//* @date  :2018/01/17
//* @author:S.Katou
//************************************************/
#include "SL_Collider.h"
#include "SL_CollisionManager.h"
#include "../../Object/ObjectBase.h"
#include "../../Util/Debugger/DebugMacro.h"

using namespace ShunLib;

//���R���X�g���N�^
//�����蔻����Ǘ�����N���X�ɓo�^
ICollider::ICollider(int layer) :
	m_layer(layer),
	m_parent(nullptr),
	m_shape(nullptr),
	m_shouldPassParentInfo(true),
	m_isStatic(false),
	m_isEnable(true),
	m_shouldRejection(true),
	m_isDebugDraw(true)
{
	CollisionManager::GetInstance()->AddCollider(layer,this);
}

//���R���X�g���N�^
//�����蔻����Ǘ�����N���X����폜
ICollider::~ICollider()
{
	CollisionManager::GetInstance()->RemoveCollider(this);
}

/// <summary>
/// ���̍X�V
/// </summary>
void ICollider::Update()
{

}

//�f�o�b�O�p�`��
void ICollider::DebugRender()
{
	//�g�p���Ă���Ȃ�`��
	if (IsEnable()){

		if (m_isDebugDraw) {
			m_shape->Render();
		}
	}
}

/// <summary>
/// �r�W�^�[���󂯓����
/// </summary>
void ICollider::Accept(Visitor * visitor)
{
	visitor->Visit(this);
	for (auto& v : m_hitList) {
		visitor->Visit(v);
	}
}

/// <summary>
/// ���������I�u�W�F�N�g��Ԃ�
/// �����蔻�蓯�m�̏��̎󂯓n���Ɏg�p
/// </summary>
ObjectBase * ShunLib::ICollider::HitParent()
{
	if (m_shouldPassParentInfo) {
		return m_parent;
	}
	return nullptr;
}

/// <summary>
/// �g�p���Ă����Ԃ��ǂ���
/// </summary>
bool ICollider::IsEnable()
{
	bool isEnable = m_isEnable;
	if (m_parent != nullptr){
		isEnable = (isEnable && m_parent->IsEnable());
	}
	return isEnable;
}


//����̓����蔻��̍X�V
void SphereCollider::Update()
{
	//���N���X�̍X�V
	ICollider::Update();

	//�ʒu����
	if (m_parent != nullptr){
		Shape()->CenterPoint(m_parent->WorldPos() + this->Offset());
	}
}

//����̓����蔻��̍X�V
void BoxCollider::Update()
{
	//���N���X�̍X�V
	ICollider::Update();

	//�ʒu����
	if (m_parent != nullptr) {
		Shape()->CenterPoint(m_parent->WorldPos() + this->Offset());
		Shape()->Scale(m_parent->Transform().Scale());
	}
}
