//************************************************/
//* @file  :ObjectTransform.h
//* @brief :3D�I�u�W�F�N�g�̊�{���
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
		Vec3 m_pos;        //�ʒu
		Vec3 m_rotation;   //��]�p�x
		Vec3 m_scale;      //�g�嗦
		Matrix m_world;    //�`��p

	public:
		ObjectTransform() :
			m_pos({ 0.0f,0.0f,0.0f }),
			m_rotation({ 0.0f,0.0f,0.0f }),
			m_scale(1.0f)
		{}
		~ObjectTransform() {}

		//�s��̌v�Z
		const Matrix& CalcMat();

		//Getter
		Vec3		  Pos     ()const { return m_pos; }
		Vec3		  Rotation()const { return m_rotation; }
		Vec3		  Scale   ()const { return m_scale; }
		const Matrix& WorldMat()const { return m_world; }

		//Setter
		void Pos     (const Vec3& pos  ) { m_pos      = pos; }
		void Rotation(const Vec3& rot  ) { m_rotation = rot; }
		void Scale   (const Vec3& scale) { m_scale    = scale; }
		void Scale   (float scale      ) { m_scale    = Vec3(scale); }
	};
}