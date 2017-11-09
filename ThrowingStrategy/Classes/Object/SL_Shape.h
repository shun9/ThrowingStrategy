//************************************************/
//* @file  :SL_Shape.h
//* @brief :�����蔻��p�̌`��N���X�܂Ƃ�
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

	public:
		virtual ~IShape() {}
		virtual SHAPE_TYPE Type() { return SHAPE_TYPE::SHAPE_TYPE_END; }
	
		void Render();
	};

	//����
	class Sphere : public IShape
	{
	protected:
		Vec3 m_centerPoint;//���S�_
		float m_radius;    //���a
	
	public:
		Sphere() :m_centerPoint({0.0f,0.0f,0.0f}),m_radius(1.0f) {}
		virtual ~Sphere() {}

		Vec3 CenterPoint() { return m_centerPoint; }
		void CenterPoint(const Vec3& point) { m_centerPoint = point; }

		float Radius() { return m_radius; }
		void Radius(float rad) { m_radius = rad; }
		virtual SHAPE_TYPE Type() { return SHAPE_TYPE::SPHERE; }
	};

	// ����
	class Segment : public IShape
	{
	protected:
		// �n�_���W
		Vec3 m_startPoint;

		// �I�_���W
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


	//�����蔻��p
	bool Collision(IShape* A, IShape* B);
	bool operator*(Sphere& A, Sphere& B);
}