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
		ObjectTransform m_transform;

	public:
		ObjectNode() {}
		~ObjectNode() {}

		//親設定
		bool SetParent(Node* parent)override;

		//子の追加
		bool AddChild(Node* child)override;

		//子の切り離し
		bool RemoveChild(Node* child)override;

		/*--Getter--*/
		const Vec3& WorldPos()const { return m_transform.Pos(); }
		const Vec3& LocalPos()const { return m_transform.Pos(); }
		const ObjectTransform& Transform()const { return m_transform; }

		/*--Setter--*/
		void LocalPos(const Vec3& pos) { m_transform.Pos(pos); }

	};
}