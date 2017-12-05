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
/// ���j�b�g��T���r�W�^�[
/// </summary>
void SearchUnitVisitor::Visit(ShunLib::VisitorNode * node)
{
	Unit* unit = dynamic_cast<Unit*>(node);

	//���j�b�g�Ȃ�J�E���g
	if (unit != nullptr){
		m_unitCnt++;
		m_unitList.push_back(unit);
	}
}

/// <summary>
/// ��Ԃ����I�u�W�F�N�g��T���r�W�^�[
/// </summary>
void SearchStateObjectVisitor::Visit(ShunLib::VisitorNode * node)
{
	ObjectBase* obj = dynamic_cast<ObjectBase*>(node);

	if (obj != nullptr){

		//��Ԃ��������I�u�W�F�N�g�ꗗ
		const std::vector<OBJECT_LIST> STATE_OBJECT{
			PLAYER,
			COMMANDER,
			UNIT,
			SUMMONER,
		};

		//�I�u�W�F�N�g�̎�ނ�T��
		auto result = std::find(STATE_OBJECT.begin(), STATE_OBJECT.end(), obj->Type());
	
		//��Ԃ������Ă���I�u�W�F�N�g�Ȃ�J�E���g
		if (result != STATE_OBJECT.end()){
			m_objectCnt++;
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
		TEAM objTeam = obj->Team();

		//�`�[���ɏ������Ă���
		//�w��`�[���ł͂Ȃ��Ȃ�J�E���g����
		if (objTeam != NONE && objTeam != m_myTeam){
			m_objectCnt++;
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
