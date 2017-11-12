//************************************************/
//* @file  :CollisionManager.cpp
//* @brief :当たり判定を管理するクラス
//* @date  :2017/11/12
//* @author:S.Katou
//************************************************/
#include "SL_CollisionManager.h"

void ShunLib::CollisionManager::Update()
{
	for (auto& v : m_colliderList)
	{
		v->Update();
	}

	//当たり判定
	int size = (int)m_colliderList.size();
	for (int i = 0; i < size; i++)
	{
		for (int j = i+1; j < size; j++)
		{
			if (Collision(m_colliderList[i]->Shape(), m_colliderList[j]->Shape()))
			{
				(*m_colliderList[i])(m_colliderList[j]->Parent());
				(*m_colliderList[j])(m_colliderList[i]->Parent());
			}
		}
	}
}

void ShunLib::CollisionManager::Render()
{
	for (auto& v : m_colliderList)
	{
		v->DebugRender();
	}
}
