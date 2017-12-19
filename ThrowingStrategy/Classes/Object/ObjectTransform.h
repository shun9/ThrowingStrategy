//************************************************/
//* @file  :ObjectData.h
//* @brief :オブジェクトが使用するデータをまとめたクラス
//* @date  :2017/11/02
//* @author:S.Katou
//************************************************/
#pragma once
#include <SL_Math.h>

class ObjectTransform
{
private:
	using Vec3 = ShunLib::Vec3;
	using Matrix = ShunLib::Matrix;

protected:
	Vec3 m_pos;        //位置
	Vec3 m_rotation;   //回転角度
	Vec3 m_velocity;   //移動速度
	Vec3 m_scale;      //拡大率
	Matrix m_world;    //描画用

public:
	ObjectTransform() :
		m_pos({ 0.0f,0.0f,0.0f }),
		m_rotation({ 0.0f,0.0f,0.0f }),
		m_velocity({ 0.0f,0.0f,0.0f }),
		m_scale(1.0f)
	{}
	~ObjectTransform() {}

	//Getter
	Vec3		  Pos     ()const { return m_pos; }
	Vec3		  Rotation()const { return m_rotation; }
	Vec3		  Velocity()const { return m_velocity; }
	Vec3		  Scale   ()const { return m_scale; }
	const Matrix& World   ()const { return m_world; }

	//Setter
	void Pos     (const Vec3& pos  ) { m_pos = pos; }
	void Rotation(const Vec3& rot  ) { m_rotation = rot; }
	void Velocity(const Vec3& vel  ) { m_velocity = vel; }
	void Scale   (const Vec3& scale) { m_scale = scale; }
	void Scale   (float scale      ) { m_scale = Vec3(scale); }
};
