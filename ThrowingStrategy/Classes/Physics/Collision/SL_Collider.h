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
	
		virtual void Update() = 0;
		void DebugRender();

		void Parent(ObjectBase* parent) { m_parent = parent; }
		ObjectBase* Parent() { return m_parent; }

		Vec3 Offset() { return m_offset; }
		void Offset(const Vec3& offset) { m_offset = offset; }
	
		IShape* Shape() { return m_shape; }

		void SetCallBack(std::function<void(ObjectBase*)> func) { m_callBack = func; }
	
	protected:
		void Shape(IShape* shape) { m_shape = shape; }

	public:
		void operator()(ObjectBase* obj) { 
			if(m_callBack!=NULL)m_callBack(obj); }
	};


	//球状の当たり判定
	class SphereCollider : public ICollider
	{
	public:
		SphereCollider() { m_shape  = new Sphere; }
		~SphereCollider() { SAFE_DELETE(m_shape); }

		void Update()override;
	
	private:
		//キャストしたポインタを返す
		Sphere* CastShape() {
			return dynamic_cast<Sphere*>(m_shape);
		}
	};
}