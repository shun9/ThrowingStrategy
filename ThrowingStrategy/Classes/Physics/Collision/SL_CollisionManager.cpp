//************************************************/
//* @file  :CollisionManager.cpp
//* @brief :当たり判定を管理するクラス
//* @date  :2017/12/08
//* @author:S.Katou
//************************************************/
#include "SL_CollisionManager.h"
#include "../../Util/Debugger/DebugMacro.h"
#include "../../Object/ObjectBase.h"

//更新
void ShunLib::CollisionManager::Update()
{
	//当たり判定の更新
	//当たっているオブジェクト一覧を初期化
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
			//親が同じ場合は、判定を取らない
			if (m_colliderList[i]->Parent() != nullptr
			&&  m_colliderList[i]->Parent() == m_colliderList[j]->Parent()){
				continue;
			}

			//どちらかが使用されていない状態なら、判定を取らない
			if (!(m_colliderList[i]->IsEnable()
			&&    m_colliderList[j]->IsEnable())) {
				continue;
			}

			//当たり判定
			Collision(
				m_colliderList[i],
				m_colliderList[j],
				(m_colliderList[i]->ShouldRejection()&&m_colliderList[j]->ShouldRejection()));
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