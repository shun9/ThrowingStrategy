//************************************************/
//* @file  :ObjectHolder.cpp
//* @brief :�I�u�W�F�N�g����ۊǂ��Ă����N���X
//* @date  :2018/01/01
//* @author:S.Katou
//************************************************/
#include "SL_ObjectHolder.h"
#include <algorithm>
#include <SL_MacroConstants.h>

using namespace ShunLib;

/// <summary>
/// �I�u�W�F�N�g���X�g�̃T�C�Y��ݒ肷��
/// </summary>
/// <param name="layerNum">���C���[�̐�</param>
/// <param name="layerSize">���C���[�̑傫��</param>
void ObjectHolder::ResizeList(int layerNum, int layerSize)
{
	m_objectList.resize(layerNum);
	for (auto& layer:m_objectList)
	{
		layer.reserve(layerSize);
	}
}

/// <summary>
/// �I�u�W�F�N�g�̒ǉ�
/// </summary>
/// <param name="layerNum">���C���[�ԍ�</param>
/// <param name="obj">�I�u�W�F�N�g</param>
void ObjectHolder::AddObject(int layerNum, ObjectNode * obj)
{
	m_objectList[layerNum].push_back(obj);
}

/// <summary>
/// �I�u�W�F�N�g�����O
/// </summary>
/// <param name="layerNum">���C���[�ԍ�</param>
/// <param name="obj">�I�u�W�F�N�g</param>
void ObjectHolder::RemoveObject(int layerNum, ObjectNode * obj)
{
	//�ꗗ�̒�����Y���I�u�W�F�N�g�̃C�e���[�^��T��
	auto itr = std::find(m_objectList[layerNum].begin(), m_objectList[layerNum].end(), obj);

	//���݂����Ȃ珜�O
	if (itr != m_objectList[layerNum].end()) {
		m_objectList[layerNum].erase(itr);
	}
}

/// <summary>
/// �g�p����Ă��Ȃ��I�u�W�F�N�g��T��
/// </summary>
/// <param name="layerNum">���C���[�ԍ�</param>
ObjectNode* ShunLib::ObjectHolder::SearchNotEnableObject(int layerNum)
{
	//���C���[�̔ԍ������݂��Ȃ���ΒT���Ȃ�
	if (layerNum >= (int)m_objectList.size()){
		return nullptr;
	}

	//�g�p����Ă��Ȃ��I�u�W�F�N�g��T��
	for (int i = 0; i < (int)m_objectList[layerNum].size(); i++){
		//�g�p����Ă��Ȃ��I�u�W�F�N�g������������Ԃ�
		if (!m_objectList[layerNum][i]->IsEnable()){
			return m_objectList[layerNum][i];
		}
	}

	//������Ȃ�
	return nullptr;
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ObjectHolder::~ObjectHolder()
{
	//�c���Ă���I�u�W�F�N�g��j��
	for (int i = 0; i < (int)m_objectList.size(); i++){
		for (int j = 0; j < (int)m_objectList[i].size(); j++){
			SAFE_DELETE(m_objectList[i][j]);
		}
	}
}
