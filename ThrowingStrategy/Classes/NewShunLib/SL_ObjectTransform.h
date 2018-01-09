//************************************************/
//* @file  :ObjectTransform.h
//* @brief :3Dオブジェクトの基本情報
//* @date  :2017/12/19
//* @author:S.Katou
//************************************************/
#pragma once
#include <SL_Math.h>

namespace ShunLib {
	class ObjectTransform
	{
	private:
		using Vec3 = ShunLib::Vec3;
		using Matrix = ShunLib::Matrix;

	private:
		Vec3 m_pos;      //位置
		Vec3 m_rotation;  //回転角度
		Vec3 m_scale;     //拡大率
		Vec3 m_velocity;  //速度
		Matrix m_transMat;//子用  角度とスケールは反映させない
		Matrix m_world;   //描画用

	public:
		ObjectTransform() :
			m_pos({ 0.0f,0.0f,0.0f }),
			m_rotation({ 0.0f,0.0f,0.0f }),
			m_scale(1.0f)
		{}
		~ObjectTransform() {}

		//行列の計算
		const Matrix& CalcMat();

		//Getter
		Vec3		  Pos     ()const { return m_pos; }
		Vec3		  Rotation()const { return m_rotation; }
		Vec3		  Scale   ()const { return m_scale; }
		Vec3		  Velocity()const { return m_velocity; }
		const Matrix& TransMat()const { return m_transMat; }
		const Matrix& WorldMat()const { return m_world; }

		//Setter
		void Pos     (const Vec3& pos  ) { m_pos      = pos; }
		void Rotation(const Vec3& rot  ) { m_rotation = rot; }
		void Scale   (const Vec3& scale) { m_scale    = scale; }
		void Velocity(const Vec3& vel  ) { m_velocity = vel; }
		void Scale   (float scale      ) { m_scale    = Vec3(scale); }
	};
}