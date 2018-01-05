//************************************************/
//* @file  :SL_Shape.h
//* @brief :当たり判定用の形状クラスまとめ
//* @date  :2017/11/09
//* @author:S.Katou
//************************************************/
#pragma once
#include <SL_Math.h>

namespace ShunLib {
	//形状の種類
	enum SHAPE_TYPE
	{
		SPHERE = 0,
		BOX,
		SEGMENT,
		POINT,
		SHAPE_TYPE_END,
	};

	//形状クラスの基底
	class IShape {
	protected:
		Vec3 m_size;
		Vec3 m_scale;

		Vec3 m_centerPoint;//中心点

	public:
		IShape() :m_size(Vec3::One),m_scale(1.0f), m_centerPoint(Vec3::Zero) {}
		virtual ~IShape() {}

		virtual void Render() {};

		/*--Setter--*/
		Vec3 Scale()const { return m_scale; }
		Vec3 Size()const { return m_size; }
		Vec3 CenterPoint()const { return m_centerPoint; }
		virtual SHAPE_TYPE Type()const { return SHAPE_TYPE::SHAPE_TYPE_END; }

		/*--Setter--*/
		void Scale(float s) { m_scale = s; }
		void Scale(const Vec3& s) { m_scale = s; }
		void Size(const Vec3& s) { m_size = s; }
		void CenterPoint(const Vec3& point) { m_centerPoint = point; }
	};

	//球体
	//Scale : xを半径として使用
	//Size  : 使用しない
	class Sphere : public IShape
	{
	public:
		//コンストラクタ　直径を１にする
		Sphere() { this->Scale(0.5f); }
		virtual ~Sphere() {}

		void Render()override;

		virtual SHAPE_TYPE Type()const override { return SHAPE_TYPE::SPHERE; }

		/*--Getter--*/
		float Radius() { return Scale().m_x; }

		/*--Setter--*/
		void Radius(float rad) { Scale(rad); }
	};

	//箱
	//Scale : それぞれの軸の拡大率
	//Size  : それぞれの軸の長さ
	//実際の大きさは Size×Scale
	class Box : public IShape
	{
	public:
		//コンストラクタ　とりあえず１
		Box() {
			Scale(Vec3(1.0f, 1.0f, 1.0f));
			Size(Vec3(1.0f, 1.0f, 1.0f));
		}
		virtual ~Box() {}

		void Render()override;

		virtual SHAPE_TYPE Type()const override { return SHAPE_TYPE::BOX; }

		//それぞれの軸の長さ
		float LengthX()const { return Size().m_x * Scale().m_x; }
		float LengthY()const { return Size().m_y * Scale().m_y; }
		float LengthZ()const { return Size().m_z * Scale().m_z; }

		//それぞれの軸の最大座標
		float MaxX()const { return CenterPoint().m_x + (LengthX() / 2.0f); }
		float MaxY()const { return CenterPoint().m_y + (LengthY() / 2.0f); }
		float MaxZ()const { return CenterPoint().m_z + (LengthZ() / 2.0f); }

		//それぞれの軸の最小座標
		float MinX()const { return CenterPoint().m_x - (LengthX() / 2.0f); }
		float MinY()const { return CenterPoint().m_y - (LengthY() / 2.0f); }
		float MinZ()const { return CenterPoint().m_z - (LengthZ() / 2.0f); }

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

		/*--Getter--*/
		Vec3 StartPoint()const { return m_startPoint; }
		Vec3 EndPoint()const { return m_endPoint; }

		/*--Setter--*/
		void EndPoint(const Vec3& point) { m_endPoint = point; }
		void StartPoint(const Vec3& point) { m_startPoint = point; }

		virtual SHAPE_TYPE Type() const override { return SHAPE_TYPE::SEGMENT; }
	};

	// 点
	class Point : public IShape
	{
	public:
		Point(){}
		virtual ~Point() {}

		virtual SHAPE_TYPE Type() const override { return SHAPE_TYPE::SEGMENT; }
	};

	//最短距離を求める
	float ShortestDistance(const Box& A, const Point& B, Point* buffer = nullptr);
}