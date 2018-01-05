//************************************************/
//* @file  :ObjectHolder.cpp
//* @brief :オブジェクト情報を保管しておくクラス
//* @date  :2018/01/01
//* @author:S.Katou
//************************************************/
#include "SL_ObjectHolder.h"
#include <algorithm>
#include <SL_MacroConstants.h>

using namespace ShunLib;

/// <summary>
/// オブジェクトリストのサイズを設定する
/// </summary>
/// <param name="layerNum">レイヤーの数</param>
/// <param name="layerSize">レイヤーの大きさ</param>
void ObjectHolder::ResizeList(int layerNum, int layerSize)
{
	m_objectList.resize(layerNum);
	for (auto& layer:m_objectList)
	{
		layer.reserve(layerSize);
	}
}

/// <summary>
/// オブジェクトの追加
/// </summary>
/// <param name="layerNum">レイヤー番号</param>
/// <param name="obj">オブジェクト</param>
void ObjectHolder::AddObject(int layerNum, ObjectNode * obj)
{
	m_objectList[layerNum].push_back(obj);
}

/// <summary>
/// オブジェクトを除外
/// </summary>
/// <param name="layerNum">レイヤー番号</param>
/// <param name="obj">オブジェクト</param>
void ObjectHolder::RemoveObject(int layerNum, ObjectNode * obj)
{
	//一覧の中から該当オブジェクトのイテレータを探す
	auto itr = std::find(m_objectList[layerNum].begin(), m_objectList[layerNum].end(), obj);

	//存在したなら除外
	if (itr != m_objectList[layerNum].end()) {
		m_objectList[layerNum].erase(itr);
	}
}

/// <summary>
/// 使用されていないオブジェクトを探す
/// </summary>
/// <param name="layerNum">レイヤー番号</param>
ObjectNode* ShunLib::ObjectHolder::SearchNotEnableObject(int layerNum)
{
	//レイヤーの番号が存在しなければ探さない
	if (layerNum >= (int)m_objectList.size()){
		return nullptr;
	}

	//使用されていないオブジェクトを探す
	for (int i = 0; i < (int)m_objectList[layerNum].size(); i++){
		//使用されていないオブジェクトが見つかったら返す
		if (!m_objectList[layerNum][i]->IsEnable()){
			return m_objectList[layerNum][i];
		}
	}

	//見つからない
	return nullptr;
}

/// <summary>
/// デストラクタ
/// </summary>
ObjectHolder::~ObjectHolder()
{
	//残っているオブジェクトを破棄
	for (int i = 0; i < (int)m_objectList.size(); i++){
		for (int j = 0; j < (int)m_objectList[i].size(); j++){
			SAFE_DELETE(m_objectList[i][j]);
		}
	}
}
