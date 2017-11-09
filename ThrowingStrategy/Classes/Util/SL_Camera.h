//************************************************/
//* @file  :SL_Camera.h
//* @brief :ï`âÊópÉJÉÅÉâ
//* @date  :2017/11/09
//* @author:S.Katou
//************************************************/
#pragma once

#include <SL_Singleton.h>
#include <SL_Math.h>

namespace ShunLib {
	class MainCamera  : public Singleton<MainCamera>
	{
		friend Singleton<MainCamera>;

	private:
		using Vec3 = ShunLib::Vec3;
		using Matrix = ShunLib::Matrix;

	private:
		Matrix m_view;
		Matrix m_proj;

		Vec3 m_pos;
		Vec3 m_target;
		Vec3 m_up;

		float m_fov;
		float m_aspect;
		float m_near;
		float m_far;

	public:
		void Update();

		const Matrix& ViewMat() { return m_view; }
		const Matrix& ProjMat() { return m_proj; }

		void Pos   (const Vec3& pos) { m_pos = pos; }
		void Target(const Vec3& tar) { m_target = tar; }
		void Up    (const Vec3& up)  { m_up = up; }

		void Fov   (float fov ) { m_fov = fov; }
		void Aspect(float asp ) { m_aspect = asp; }
		void Near  (float nearClip) { m_near = nearClip; }
		void Far   (float farClip ) { m_far = farClip; }

	private:
		MainCamera();
		~MainCamera();
	};
}