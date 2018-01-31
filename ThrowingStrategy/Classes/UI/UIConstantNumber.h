//************************************************/
//* @file  :UIConstantNumber.h
//* @brief :UI�֘A�̒萔
//* @date  :2018/01/31
//* @author:S.Katou
//************************************************/
#pragma once
#include <SL_Math.h>

class UIConstantNumber {
public:
	using Vec3 = ShunLib::Vec3;

	//HP�Q�[�W
	class HP_GAUGE_CONSTANT {
	public:
		static const Vec3 SCALE;
	};

	//�\�����e�n�_�̃J�[�\��
	class THROW_CURSOR_CONSTANT {
	public:
		static const Vec3 SCALE;
	};
};