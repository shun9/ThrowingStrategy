//************************************************/
//* @file  :SL_Collider.h
//* @brief :当たり判定オブジェクトのクラス
//* @date  :2017/11/16
//* @author:S.Katou
//************************************************/
#pragma once
#include <functional>
#include <vector>
#include <SL_MacroConstants.h>
#include <SL_Visitor.h>
#include "../../Object/SL_Shape.h"

class ObjectBase;

namespace ShunLib
{
	//当たり判定用クラスの抽象クラス
	class ICollider :public VisitorNode
	{
	public:
		using ChildList = std::vector<ICollider*>;
		using HitObjectList = std::vector<ObjectBase*>;
	protected:
		//当たり判定を持つオブジェクト
		ObjectBase* m_parent;

		//子の当たり判定
		//親の当たり判定後に子の当たり判定を行う
		ChildList m_childrenCollider;

		//当たり判定形状
		IShape* m_shape;

		//オブジェクトからの相対座標
		Vec3 m_offset;

		//当たっているオブジェクトのリスト
		HitObjectList m_hitList;

		//親の情報を渡すかどうか
		bool m_shouldPassParentInfo;

		//当たり判定を行うかどうか
		bool m_isEnable;

		//排斥処理を行うかどうか
		bool m_shouldRejection;

		//動くかどうか
		bool m_isStatic;

		//デバッグ描画するかどうか
		bool m_isDebugDraw;
	public:
		ICollider();
		virtual ~ICollider();

		virtual void Update();

		void DebugRender();

		//リストに追加
		//持ち主が同じ場合は追加しない
		void AddHitList(ObjectBase* obj) {
			if (m_parent != obj && obj != nullptr) {
				m_hitList.push_back(obj);
			}
		}

		//リストの初期化
		void ResetList() {
			m_hitList.clear();
			m_hitList.shrink_to_fit();
			for (auto& v:m_childrenCollider){
				v->ResetList();
			}
		}

		//ビジター受け入れ
		void Accept(ShunLib::Visitor* visitor);

		//子の当たり判定を追加
		void AddChildCollider(ICollider* child);

		/*--Getter--*/
		ObjectBase* Parent          () { return m_parent; }
		ObjectBase* HitParent       ();
		ChildList& ChildrenCollider () { return m_childrenCollider; }
		Vec3 Offset                 () { return m_offset; }
		const HitObjectList& HitList() { return m_hitList; }
		bool IsEnable               () { return m_isEnable; }
		bool IsStatic               () { return m_isStatic; }
		bool ShouldRejection        () { return m_shouldRejection; }
		SHAPE_TYPE Type             () { return m_shape->Type(); }

		/*--Setter--*/
		void Offset         (const Vec3& offset) { m_offset = offset; }
		void Parent         (ObjectBase* parent) { m_parent = parent; }
		void IsEnable       (bool enable       ) { m_isEnable = enable; }
		void IsStatic       (bool isStatic     ) { m_isStatic = isStatic; }
		void IsDebugDraw    (bool draw         ) { m_isDebugDraw = draw; }
		void ShouldPassInfo (bool shouldPass   ) { m_shouldPassParentInfo = shouldPass; }
		void ShouldRejection(bool rejection    ) { m_shouldRejection = rejection; }

	//純粋仮想関数
	public:
		//クラスごとに返す形状を変更
		virtual IShape* Shape() = 0;
	};

	//球状の当たり判定用クラス
	class SphereCollider : public ICollider
	{
	public:
		SphereCollider() { m_shape  = new Sphere; }
		~SphereCollider() { SAFE_DELETE(m_shape); }

		void Update()override;

		//キャストしたポインタを返す
		Sphere* Shape() {
			return dynamic_cast<Sphere*>(m_shape);
		}
	};

	//球状の当たり判定用クラス
	class BoxCollider : public ICollider
	{
	public:
		BoxCollider() { m_shape = new Box; }
		~BoxCollider() { SAFE_DELETE(m_shape); }

		void Update()override;

		Box* Shape() {
			return dynamic_cast<Box*>(m_shape);
		}
	};

}