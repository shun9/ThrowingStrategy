//************************************************/
//* @file  :ObjectStruct.h
//* @brief :オブジェクト関連の構造体まとめ
//* @date  :2017/11/16
//* @author:S.Katou
//************************************************/
#pragma once
#include <functional>
#include <SL_Math.h>
#include "ObjectConstantNumber.h"

//飛ぶ際に必要なデータ
struct FlyingData
{
	ShunLib::Vec3 start;
	ShunLib::Vec3 end;
	float power;
	THROW_TYPE type;

	//投げ方ごとの補間関数を返す
	std::function<float(float)>Lerp() {
		switch (type)
		{
		//直線タイプ
		case LINE:
			return ShunLib::Lerp::EaseOut;
		default:
			break;
		}
		return NULL;
	}
};