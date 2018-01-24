//************************************************/
//* @file  :CollisionManager.cpp
//* @brief :�����蔻����Ǘ�����N���X
//* @date  :2017/12/08
//* @author:S.Katou
//************************************************/
#include "SL_CollisionManager.h"
#include "../../Util/Debugger/DebugMacro.h"
#include "../../Object/ObjectBase.h"

using namespace ShunLib;

/// <summary>
/// ���C���[�̃T�C�Y���ʂɐݒ�
/// </summary>
/// <param name="layerNum">���C���[�ԍ�</param>
/// <param name="layerSize">�T�C�Y</param>
void CollisionManager::ResizeLayer(int layerNum, int layerSize)
{
	m_colliderList[layerNum].reserve(layerSize);
}

//�X�V
void CollisionManager::Update()
{
	//�����蔻��̍X�V
	//�������Ă���I�u�W�F�N�g�ꗗ��������
	for (auto& layer : m_colliderList) {

		for (auto& v : layer) {
			v->Update();
			v->ResetList();
		}
	}

	//�����蔻��
	for (int i = 0; i < COLLIDER_LAYER_END; i++)
	{
		for (int j = i; j < COLLIDER_LAYER_END; j++)
		{
			//�����Ȃ��ғ��m�͔�������Ȃ�
			if (i == STATIC && j == STATIC){
				continue;
			}

			//���C���[�Ԃœ����蔻��
			CollisionLayer(i, j);
		}
	}
}

//�`��
void CollisionManager::Render()
{
	for (auto& layer : m_colliderList)
	{
		for (auto& v : layer)
		{
			Debug v->DebugRender();
		}
	}
}

/// <summary>
/// �����蔻����O��
/// </summary>
void CollisionManager::RemoveCollider(ICollider * col)
{
	std::vector<ICollider*>::iterator tmp;

	for (auto& layer : m_colliderList) {
		//�w�肳�ꂽ�����蔻���T��
		tmp = std::find(layer.begin(), layer.end(), col);

		//����������폜���ďI��
		if (tmp != layer.end()) {
			layer.erase(tmp);
			return;
		}
	}
}

/// <summary>
/// �R���X�g���N�^
/// </summary>
CollisionManager::CollisionManager()
{
	m_colliderList.resize(COLLIDER_LAYER_END);

	m_colliderList[RIGID].reserve(500);
	m_colliderList[STATIC].reserve(100);
	m_colliderList[TRIGGER].reserve(500);
}

/// <summary>
/// ���C���[���Ƃɓ����蔻��
/// </summary>
/// <param name="layer1">1�ڂ̃��C���[�̃C���f�b�N�X</param>
/// <param name="layer2">2�ڂ̃��C���[�̃C���f�b�N�X</param>
void ShunLib::CollisionManager::CollisionLayer(int layer1, int layer2)
{
	//�e���C���[�̑傫��
	int size1 = (int)m_colliderList[layer1].size();
	int size2 = (int)m_colliderList[layer2].size();

	for (int i = 0; i < size1; i++)
	{
		for (int j = 0; j < size2; j++)
		{
			//�e�������ꍇ�́A��������Ȃ�
			if (m_colliderList[layer1][i]->Parent() != nullptr
			&&  m_colliderList[layer1][i]->Parent() == m_colliderList[layer2][j]->Parent()) {
				continue;
			}

			//�ǂ��炩���g�p����Ă��Ȃ���ԂȂ�A��������Ȃ�
			if (!(m_colliderList[layer1][i]->IsEnable()
			&&    m_colliderList[layer2][j]->IsEnable())) {
				continue;
			}

			//�����蔻��
			Collision(m_colliderList[layer1][i],m_colliderList[layer2][j]);
		}
	}
}
