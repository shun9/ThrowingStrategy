//************************************************/
//* @file  :ObjectStruct.h
//* @brief :�I�u�W�F�N�g�֘A�̍\���̂܂Ƃ�
//* @date  :2017/11/16
//* @author:S.Katou
//************************************************/
#pragma once
#include <functional>
#include <SL_Math.h>
#include "ObjectConstantNumber.h"

//��ԍۂɕK�v�ȃf�[�^
struct FlyingData
{
	ShunLib::Vec3 start;
	ShunLib::Vec3 end;
	float power;
	THROW_TYPE type;

	//���������Ƃ̕�Ԋ֐���Ԃ�
	std::function<float(float)>Lerp() {
		switch (type)
		{
		//�����^�C�v
		case LINE:
			return ShunLib::Lerp::EaseOut;
		default:
			break;
		}
		return NULL;
	}
};