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
		POINT,
		SHAPE_TYPE_END,
	};

	class IShape {
	protected:
		Vec3 m_size;
		float m_scale;

		Vec3 m_centerPoint;//���S�_

	public:
		IShape() :m_size(Vec3::One),m_scale(1.0f), m_centerPoint(Vec3::Zero) {}
		virtual ~IShape() {}
	
		virtual void Render() {};

		/*--Setter--*/
		float Scale()const { return m_scale; }
		Vec3 Size()const { return m_size; }
		Vec3 CenterPoint()const { return m_centerPoint; }
		virtual SHAPE_TYPE Type()const { return SHAPE_TYPE::SHAPE_TYPE_END; }

		/*--Setter--*/
		void Scale(float s) { m_scale = s; }
		void Size(const Vec3& s) { m_size = s; }
		void CenterPoint(const Vec3& point) { m_centerPoint = point; }
	};

	//����
	//Scale : ���a
	//Size  : �g�p���Ȃ�
	class Sphere : public IShape
	{
	public:
		//�R���X�g���N�^�@���a���P�ɂ���
		Sphere() { this->Scale(0.5f); }
		virtual ~Sphere() {}

		void Render()override;

		virtual SHAPE_TYPE Type()const override { return SHAPE_TYPE::SPHERE; }
	};

	//��
	//Scale : �g�p���Ȃ�
	//Size  : ���ꂼ��̎��̒���
	class Box : public IShape
	{
	public:
		Box() { }
		virtual ~Box() {}

		void Render()override;

		virtual SHAPE_TYPE Type()const override { return SHAPE_TYPE::BOX; }
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

		/*--Getter--*/
		Vec3 StartPoint()const { return m_startPoint; }		
		Vec3 EndPoint()const { return m_endPoint; }
		
		/*--Setter--*/
		void EndPoint(const Vec3& point) { m_endPoint = point; }
		void StartPoint(const Vec3& point) { m_startPoint = point; }

		virtual SHAPE_TYPE Type() const override { return SHAPE_TYPE::SEGMENT; }
	};

	// �_
	class Point : public IShape
	{
	public:
		Point(){}
		virtual ~Point() {}

		virtual SHAPE_TYPE Type() const override { return SHAPE_TYPE::SEGMENT; }
	};

	//�ŒZ���������߂�
	float ShortestDistance(const Box& A, const Point& B);
}