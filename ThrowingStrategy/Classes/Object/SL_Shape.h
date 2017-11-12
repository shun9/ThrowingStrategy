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
		using Matrix = ShunLib::Matrix;
		
	protected:
		Vec3 m_size;
		float m_scale;

		Vec3 m_centerPoint;//���S�_

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

	//����
	//Scale : ���a
	//Size  : �g�p���Ȃ�
	class Sphere : public IShape
	{
	private:
		using Matrix = ShunLib::Matrix;
	
	public:
		//�R���X�g���N�^�@���a���P�ɂ���
		Sphere() { this->Scale(0.5f); }
		virtual ~Sphere() {}

		void Render()override;


		virtual SHAPE_TYPE Type() { return SHAPE_TYPE::SPHERE; }
	};

	//��
	//Scale : �g�嗦
	//Size  : ���ꂼ��̎��̒���
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
	bool operator*(Sphere& A, Box& B);
	bool operator*(Box& A, Sphere& B);
	bool operator*(Box& A, Box& B);
}