//************************************************/
//* @file  :Node.h
//* @brief :親子関係を持つノード
//* @date  :2017/12/21
//* @author:S.Katou
//************************************************/
#pragma once
#include <vector>
#include <SL_Visitor.h>

namespace ShunLib
{
	class Node : public VisitorNode
	{
	public:
		//ダーティーフラグ一覧
		enum DIRTY_FLAG {
			INITIALIZE_FLAG = 0 ,
			UPDATE_FLAG,
			RENDER_FLAG,
			FINALIZE_FLAG,

			DIRTY_FLAG_END,
		};

	protected:
		//親
		Node* m_parent;

		//子の一覧
		std::vector<Node*> m_children;

		//使用しているかどうか
		bool m_isEnable;

		//ダーティーフラグ
		//処理後にtrue
		bool m_isDirty[DIRTY_FLAG::DIRTY_FLAG_END];

	public:
		Node(int childrenSize = 100);
		virtual ~Node();

		//初期化　更新　描画　終了
		//ダーティーフラグの処理をしたあと
		//派生クラスの処理を呼び出す
		void BaseInitialize();
		void BaseUpdate();
		void BaseRender();
		void BaseFinalize();

		//親設定
		virtual bool SetParent(Node* parent);

		//子の追加
		virtual bool AddChild(Node* child);

		//子の切り離し
		virtual bool RemoveChild(Node* child);

		//ビジターを受け入れる
		virtual void Accept(Visitor* visitor);

		//ダーティーフラグを初期状態に戻す
		//初期化　更新　描画　終了を可能な状態にする
		void ClearDirty();

		//更新　描画を可能な状態にする
		void BaseActiveUpdate();
		void BaseActiveRender();

		/*--Getter--*/
		Node* Parent() { return m_parent; }
		std::vector<Node*>& Children() { return m_children; }
		bool IsEnable() { return m_isEnable; }

	protected:
		//初期化　更新　描画　終了
		//派生クラスで処理を実装する
		virtual void Initialize() { m_isEnable = true; };
		virtual void Update    () = 0;
		virtual void Render    () = 0;
		virtual void Finalize  () = 0;

		//更新　描画を可能な状態にする
		void EnableUpdate() { m_isDirty[DIRTY_FLAG::UPDATE_FLAG] = false; }
		void EnableRender() { m_isDirty[DIRTY_FLAG::RENDER_FLAG] = false; }
	};
}