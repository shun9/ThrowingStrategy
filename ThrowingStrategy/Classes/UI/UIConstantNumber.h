//************************************************/
//* @file  :UIConstantNumber.h
//* @brief :UI関連の定数
//* @date  :2018/01/31
//* @author:S.Katou
//************************************************/
#pragma once
#include <SL_Math.h>

class UIConstantNumber {
public:
	using Vec3 = ShunLib::Vec3;

	//HPゲージ
	class HP_GAUGE_CONSTANT {
	public:
		static const Vec3 SCALE;
	};

	//予測着弾地点のカーソル
	class THROW_CURSOR_CONSTANT {
	public:
		static const Vec3 SCALE;
	};
};