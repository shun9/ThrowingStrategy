//************************************************/
//* @file  :Collider.h
//* @brief :当たり判定オブジェクトのクラス
//* @date  :2017/11/09
//* @author:S.Katou
//************************************************/
#pragma once
#include <functional>
#include <SL_MacroConstants.h>
#include "../../Object/SL_Shape.h"

class ObjectBase;

namespace ShunLib 
{
	
	//当たり判定用クラスの抽象クラス
	class ICollider
	{
	private:
		using Vec3 = ShunLib::Vec3;

	protected:
		//当たり判定を持つオブジェクト
		ObjectBase* m_parent;

		//当たり判定形状
		IShape* m_shape;

		//オブジェクトからの相対座標
		Vec3 m_offset;

		//当たったときに実行する関数
		std::function<void(ObjectBase*)> m_callBack;

	public:
		ICollider();
		virtual ~ICollider();
	
		void Update();
		void DebugRender();

		/*--Getter--*/
		ObjectBase* Parent() { return m_parent; }
		Vec3 Offset() { return m_offset; }

		/*--Setter--*/
		void Offset(const Vec3& offset) { m_offset = offset; }
		void Parent(ObjectBase* parent) { m_parent = parent; }
		void SetCallBack(std::function<void(ObjectBase*)> func) { m_callBack = func; }
	
	//純粋仮想関数
	public:
		//クラスごとに返す形状を変更
		virtual IShape* Shape() = 0;

	public:
		//コールバックを呼ぶ
		void operator()(ObjectBase* obj) { 
			if(m_callBack!=NULL)m_callBack(obj); }
	};


	//球状の当たり判定用クラス
	class SphereCollider : public ICollider
	{
	public:
		SphereCollider() { m_shape  = new Sphere; }
		~SphereCollider() { SAFE_DELETE(m_shape); }
	
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

		Box* Shape() {
			return dynamic_cast<Box*>(m_shape);
		}
	};

}