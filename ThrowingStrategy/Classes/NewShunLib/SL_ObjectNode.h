//************************************************/
//* @file  :ObjectNode.h
//* @brief :親子関係を持った3Dオブジェクトのノード
//* @date  :2017/12/19
//* @author:S.Katou
//************************************************/
#pragma once
#include <SL_Node.h>
#include <SL_ObjectTransform.h>

namespace ShunLib {
	class ObjectNode : public Node
	{
	protected:
		//オブジェクトの基本情報
		ObjectTransform m_transform;

		int m_layerNumber;

	public:
		ObjectNode(int layerNumber);
		virtual ~ObjectNode();


		//親設定
		bool SetParent(Node* parent)override;

		//子の追加
		bool AddChild(Node* child)override;

		//子の切り離し
		bool RemoveChild(Node* child)override;

		/*--Getter--*/
		const Vec3 WorldPos()const;
		const Vec3 LocalPos()const { return m_transform.Pos(); }

		/*--Setter--*/
		void LocalPos(const Vec3& pos) { m_transform.Pos(pos); }

		/*--Getter & Setter--*/
		ObjectTransform& Transform() { return m_transform; }

	protected:
		//初期化　更新　描画　終了
		//派生クラスで処理を実装する
		virtual void Initialize()override { Node::Initialize(); };
		virtual void Update    ()override = 0;
		virtual void Render    ()override = 0;
		virtual void Finalize  ()override = 0;
	};
}