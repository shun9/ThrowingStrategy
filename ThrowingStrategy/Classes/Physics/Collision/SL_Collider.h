//************************************************/
//* @file  :SL_Collider.h
//* @brief :当たり判定オブジェクトのクラス
//* @date  :2018/01/23
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
		using HitObjectList = std::vector<ObjectBase*>;

	protected:
		//当たり判定を持つオブジェクト
		ObjectBase* m_parent;

		//当たり判定形状
		IShape* m_shape;

		//オブジェクトからの相対座標
		Vec3 m_offset;

		//当たっているオブジェクトのリスト
		HitObjectList m_hitList;

		//所属レイヤー
		int m_layer;

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
		ICollider(int layer);
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
		}

		//ビジター受け入れ
		void Accept(ShunLib::Visitor* visitor);

		/*--Getter--*/
		ObjectBase* Parent          () { return m_parent; }
		ObjectBase* HitParent       ();
		Vec3 Offset                 () { return m_offset; }
		const HitObjectList& HitList() { return m_hitList; }
		bool IsEnable               ();
		bool IsStatic               () { return m_isStatic; }
		bool ShouldRejection        () { return m_shouldRejection; }
		SHAPE_TYPE ShapeType        () { return m_shape->Type(); }
		int ColliderType            () { return m_layer; }

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
		SphereCollider(int layer):ICollider(layer) { m_shape  = new Sphere; }
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
		BoxCollider(int layer) :ICollider(layer) { m_shape = new Box; }
		~BoxCollider() { SAFE_DELETE(m_shape); }

		void Update()override;

		Box* Shape() {
			return dynamic_cast<Box*>(m_shape);
		}
	};

}