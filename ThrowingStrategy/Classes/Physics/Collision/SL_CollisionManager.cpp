//************************************************/
//* @file  :CollisionManager.cpp
//* @brief :�����蔻����Ǘ�����N���X
//* @date  :2017/12/08
//* @author:S.Katou
//************************************************/
#include "SL_CollisionManager.h"
#include "../../Util/Debugger/DebugMacro.h"
#include "../../Object/ObjectBase.h"

//�X�V
void ShunLib::CollisionManager::Update()
{
	//�����蔻��̍X�V
	//�������Ă���I�u�W�F�N�g�ꗗ��������
	for (auto& v : m_colliderList)
	{
		v->Update();
		v->ResetList();
	}


	//�����蔻��
	int size = (int)m_colliderList.size();
	for (int i = 0; i < size; i++)
	{
		for (int j = i+1; j < size; j++)
		{
			//�e�������ꍇ�́A��������Ȃ�
			if (m_colliderList[i]->Parent() != nullptr
			&&  m_colliderList[i]->Parent() == m_colliderList[j]->Parent()){
				continue;
			}

			//�ǂ��炩���g�p����Ă��Ȃ���ԂȂ�A��������Ȃ�
			if (!(m_colliderList[i]->IsEnable()
			&&    m_colliderList[j]->IsEnable())) {
				continue;
			}

			//�����蔻��
			Collision(
				m_colliderList[i],
				m_colliderList[j],
				(m_colliderList[i]->ShouldRejection()&&m_colliderList[j]->ShouldRejection()));
		}
	}
}

//�`��
void ShunLib::CollisionManager::Render()
{
	for (auto& v : m_colliderList)
	{
		Debug v->DebugRender();
	}
}