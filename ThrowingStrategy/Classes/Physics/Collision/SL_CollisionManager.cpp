//************************************************/
//* @file  :CollisionManager.cpp
//* @brief :�����蔻����Ǘ�����N���X
//* @date  :2017/11/13
//* @author:S.Katou
//************************************************/
#include "SL_CollisionManager.h"
#include "../../Util/Debugger/DebugMacro.h"

//�X�V
void ShunLib::CollisionManager::Update()
{
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
			//�����傪�����Ȃ�Δ�΂�
			if (!(m_colliderList[j]->Parent() != m_colliderList[i]->Parent()
			&&    m_colliderList[j]->PosObj() != m_colliderList[i]->PosObj())){
				continue;
			}

			Collision(m_colliderList[i], m_colliderList[j]);
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