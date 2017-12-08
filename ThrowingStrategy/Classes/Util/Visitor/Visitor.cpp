//************************************************/
//* @file  :Visitor.cpp
//* @brief :�r�W�^�[�܂Ƃ�
//* @date  :2017/11/21
//* @author:S.Katou
//************************************************/
#include "Visitor.h"

#include <algorithm>
#include "../../Object/Unit/Unit.h"

/// <summary>
/// �I�u�W�F�N�g����Ԃ������Ă��邩�ǂ���
/// </summary>
/// <param name="obj"></param>
/// <returns></returns>
bool IsStateObject(ObjectBase* obj)
{
	for (auto& v : ObjectConstantNumber::STATE_OBJECT) {
		if (obj->Type() == v) {
			return true;
		}
	}
	return false;
}

/// <summary>
/// ���j�b�g��T���r�W�^�[
/// </summary>
void SearchUnitVisitor::Visit(ShunLib::VisitorNode * node)
{
	Unit* unit = dynamic_cast<Unit*>(node);

	//���j�b�g�Ȃ�J�E���g
	if (unit != nullptr) {
		m_unitList.push_back(unit);
	}
}

/// <summary>
/// ��Ԃ����I�u�W�F�N�g��T���r�W�^�[
/// </summary>
void SearchStateObjectVisitor::Visit(ShunLib::VisitorNode* node)
{
	ObjectBase* obj = dynamic_cast<ObjectBase*>(node);

	if (obj != nullptr) {

		//��Ԃ������Ă���I�u�W�F�N�g�Ȃ�J�E���g
		if (IsStateObject(obj)) {
			m_objectList.push_back(obj);
		}
	}
}


/// <summary>
/// �Ⴄ�`�[���̃I�u�W�F�N�g��T���r�W�^�[
/// </summary>
void SearchAnotherTeamVisitor::Visit(ShunLib::VisitorNode * node)
{
	ObjectBase* obj = dynamic_cast<ObjectBase*>(node);

	if (obj != nullptr) {
		//�`�[���ɏ������Ă���
		//�w��`�[���ł͂Ȃ��Ȃ�J�E���g����
		if (obj->Team() != ObjectConstantNumber::NONE && obj->Team() != m_myTeam) {
			m_objectList.push_back(obj);
		}
	}
}

/// <summary>
/// ����̃I�u�W�F�N�g��T���r�W�^�[
/// </summary>
void SearchSpecificObjectVisitor::Visit(ShunLib::VisitorNode * node)
{
	//�����Ȃ�J�E���g
	if (node == m_target) {
		ObjectBase* obj = dynamic_cast<ObjectBase*>(node);
		m_object = obj;
	}
}


/// <summary>
/// �ł��߂��ʒu�ɂ���I�u�W�F�N�g��T��
/// </summary>
void SearchNearestObjectVisitor::Visit(ShunLib::VisitorNode * node)
{
	ObjectBase* obj = dynamic_cast<ObjectBase*>(node);

	if (obj != nullptr) {
		//�����w��Ȃ� or ��Ԃ����I�u�W�F�N�g�̏ꍇ
		//�������m�F����
		if (!(m_isOnlyState && !IsStateObject(obj))) {
			ShunLib::Vec3 dist = m_pos - obj->WorldPos();

			if (m_minDist > dist.Length()) {
				//�ŒZ�����̍X�V
				m_minDist = dist.Length();
				m_object = obj;
			}
		}
	}
}

/// <summary>
/// �^�[�Q�b�g�̈ʒu��Ԃ�
/// </summary>
ShunLib::Vec3 SearchNearestObjectVisitor::TargetPos()
{
	ShunLib::Vec3 pos = ShunLib::Vec3::Zero;
	if (IsFound()) {
		pos = m_object->WorldPos();
	}

	return pos;
}
