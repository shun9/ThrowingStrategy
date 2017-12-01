//************************************************/
//* @file  :CollisionManager.cpp
//* @brief :当たり判定を管理するクラス
//* @date  :2017/11/13
//* @author:S.Katou
//************************************************/
#include "SL_CollisionManager.h"
#include "../../Util/Debugger/DebugMacro.h"

//更新
void ShunLib::CollisionManager::Update()
{
	for (auto& v : m_colliderList)
	{
		v->Update();
		v->ResetList();
	}

	
	//当たり判定
	int size = (int)m_colliderList.size();
	for (int i = 0; i < size; i++)
	{
		for (int j = i+1; j < size; j++)
		{
			//持ち主が同じならば飛ばす
			if (m_colliderList[j]->Parent() == m_colliderList[i]->Parent()){
				continue;
			}

			if (Collision(m_colliderList[i], m_colliderList[j]))
			{
				//ヒットリストに追加
				m_colliderList[i]->AddHitList(m_colliderList[j]->Parent());
				m_colliderList[j]->AddHitList(m_colliderList[i]->Parent());

				//ヒット処理
				(*m_colliderList[i])(m_colliderList[j]->Parent());
				(*m_colliderList[j])(m_colliderList[i]->Parent());
			}
		}
	}
}

//描画
void ShunLib::CollisionManager::Render()
{
	for (auto& v : m_colliderList)
	{
		Debug v->DebugRender();
	}
}