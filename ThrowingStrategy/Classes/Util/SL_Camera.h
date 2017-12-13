//************************************************/
//* @file  :SL_Camera.h
//* @brief :�`��p�J����
//* @date  :2017/11/16
//* @author:S.Katou
//************************************************/
#pragma once

#include <memory>
#include <SL_Singleton.h>
#include <SL_Math.h>
#include <SL_StateMachine.h>

//�ǂ�������Ώ�
class ObjectBase;

//�J�����̏�Ԉꗗ
enum CAMERA_MODE
{
	NON_MOVE_CAMERA = 0,	  //�Œ�
	FOLLOW_CAMERA,            //�ǐ�
	CAMERA_MODE_END,
};

//�r���[�s��ɕK�v�ȃf�[�^
struct ViewData
{
	ShunLib::Vec3 pos;
	ShunLib::Vec3 target;
	ShunLib::Vec3 up;
	ViewData() :
		pos(ShunLib::Vec3(0.0f, 1.0f, 0.0f)),
		target(ShunLib::Vec3(0.0f, 0.0f, 3.0f)),
		up(ShunLib::Vec3::UnitY) {}
};

//�v���W�F�N�V�����s��ɕK�v�ȃf�[�^
struct ProjData
{
	float fov;
	float aspect;
	float nearClip;
	float farClip;
	ProjData() :
		fov(45.0f),
		aspect((800.0f / 600.0f)),
		nearClip(1.0f),
		farClip(200.0f) {}
};

namespace ShunLib {

	class MainCamera  : public Singleton<MainCamera>
	{
		friend Singleton<MainCamera>;
	private:
		using Vec3 = ShunLib::Vec3;
		using Matrix = ShunLib::Matrix;

	private:

		std::unique_ptr<StateMachine<MainCamera>>m_stateMachine;

		//�ǂ�������Ώ�
		ObjectBase* m_followTarget;

		//�p�x
		float m_angle;

		//�r���[�s��@�v���W�F�N�V�����s��
		Matrix m_view;
		Matrix m_proj;

		//�s��쐬�Ɏg�����f�[�^
		ViewData m_viewData;
		ProjData m_projData;

	public:
		void Update();

		//��Ԑؑ�
		void ChangeMode(CAMERA_MODE mode);

		/*--Getter--*/
		const Matrix& ViewMat(){ return m_view; }
		const Matrix& ProjMat(){ return m_proj; }
		ViewData View() { return m_viewData; }
		ProjData Proj() { return m_projData; }
		ObjectBase* FollowTarget() { return m_followTarget; }
		float Angle() { return m_angle; }

		/*--Setter--*/
		void View(const ViewData& data) { m_viewData = data; }
		void Proj(const ProjData& data) { m_projData = data; }
		void FollowTarget(ObjectBase* obj) { m_followTarget = obj; }
		
	
	private:
		MainCamera();
		~MainCamera();

		//�r���[�s��ƃv���W�F�N�V�����s����v�Z����
		void CalcMat() {
			m_view = Matrix::CreateLookAt(m_viewData.pos, m_viewData.target, m_viewData.up);
			m_proj = Matrix::CreateProj(m_projData.fov, m_projData.aspect, m_projData.nearClip, m_projData.farClip);
		}
	};
}