//************************************************/
//* @file  :ObjectHolder.h
//* @brief :オブジェクト情報を保管しておくクラス
//* @date  :2018/01/12
//* @author:S.Katou
//************************************************/
#pragma once
#include <vector>
#include <SL_Singleton.h>
#include <SL_ObjectNode.h>

namespace ShunLib {
	class ObjectHolder : public Singleton<ObjectHolder>
	{
		friend Singleton<ObjectHolder>;
	public:
		using ObjectList = std::vector<ObjectNode*>;

	private:
		std::vector<ObjectList> m_objectList;

	public:
		// オブジェクトリストのサイズを設定する
		void ResizeList(int layerNum, int layerSize);

		//オブジェクトを追加
		void AddObject(int layerNum,ObjectNode* obj);

		//オブジェクトを除外
		void RemoveObject(int layerNum, ObjectNode* obj);

		//使用されていないオブジェクトを探す
		ObjectNode* SearchNotEnableObject(int layerNum);

		// ビジターを迎え入れる
		void Accept(int layerNum,Visitor* visitor);

		/*--Getter--*/
		ObjectList& List(int layerNum) { return m_objectList[layerNum]; }

	private:
		ObjectHolder() {}
		~ObjectHolder();
	};
}