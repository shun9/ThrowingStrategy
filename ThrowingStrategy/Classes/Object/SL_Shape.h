//************************************************/
//* @file  :SL_Shape.h
//* @brief :当たり判定用の形状クラスまとめ
//* @date  :2017/11/09
//* @author:S.Katou
//************************************************/
#pragma once
#include <SL_Math.h>

namespace ShunLib {
	enum SHAPE_TYPE
	{
		SPHERE = 0,
		BOX,
		SEGMENT,
		SHAPE_TYPE_END,
	};

	class IShape {
	private:
		using Matrix = ShunLib::Matrix;
		
	protected:
		Vec3 m_size;
		float m_scale;

		Vec3 m_centerPoint;//中心点

	public:
		IShape() :m_size(Vec3::One),m_scale(1.0f), m_centerPoint(Vec3::Zero) {}
		virtual ~IShape() {}
		virtual SHAPE_TYPE Type() { return SHAPE_TYPE::SHAPE_TYPE_END; }
	
		virtual void Render() {};

		/*--Setter--*/
		float Scale() { return m_scale; }
		Vec3 Size() { return m_size; }
		Vec3 CenterPoint() { return m_centerPoint; }

		/*--Setter--*/
		void Scale(float s) { m_scale = s; }
		void Size(const Vec3& s) { m_size = s; }
		void CenterPoint(const Vec3& point) { m_centerPoint = point; }
	};

	//球体
	//Scale : 半径
	//Size  : 使用しない
	class Sphere : public IShape
	{
	private:
		using Matrix = ShunLib::Matrix;
	
	public:
		//コンストラクタ　直径を１にする
		Sphere() { this->Scale(0.5f); }
		virtual ~Sphere() {}

		void Render()override;


		virtual SHAPE_TYPE Type() { return SHAPE_TYPE::SPHERE; }
	};

	//箱
	//Scale : 拡大率
	//Size  : それぞれの軸の長さ
	class Box : public IShape
	{
	private:
		using Matrix = ShunLib::Matrix;

	public:
		Box() { }
		virtual ~Box() {}

		void Render()override;


		virtual SHAPE_TYPE Type() { return SHAPE_TYPE::BOX; }
	};

	// 線分
	class Segment : public IShape
	{
	protected:
		// 始点座標
		Vec3 m_startPoint;

		// 終点座標
		Vec3 m_endPoint;

	public:
		Segment() :m_startPoint({ 0.0f,0.0f,0.0f }), m_endPoint({ 0.0f,0.0f,0.0f }) {}
		virtual ~Segment() {}

		Vec3 StartPoint() { return m_startPoint; }
		void StartPoint(const Vec3& point) { m_startPoint = point; }
		
		Vec3 EndPoint() { return m_endPoint; }
		void EndPoint(const Vec3& point) { m_endPoint = point; }
		
		virtual SHAPE_TYPE Type() { return SHAPE_TYPE::SEGMENT; }
	};


	//当たり判定用
	bool Collision(IShape* A, IShape* B);
	bool operator*(Sphere& A, Sphere& B);
	bool operator*(Sphere& A, Box& B);
	bool operator*(Box& A, Sphere& B);
	bool operator*(Box& A, Box& B);
}