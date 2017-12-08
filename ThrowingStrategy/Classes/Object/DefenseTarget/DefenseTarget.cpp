//************************************************/
//* @file  :DefenseTarget.cpp
//* @brief :–h‰q‘ÎÛ
//* @date  :2017/11/20
//* @author:S.Katou
//************************************************/
#include "DefenseTarget.h"

DefenseTarget::DefenseTarget()
{
	this->Type(ObjectConstantNumber::DEFENSE_TARGET);
	this->Pos(ShunLib::Vec3(0.0f, 3.0f, 0.0f));
	this->Scale(2.0f);
}

DefenseTarget::~DefenseTarget()
{

}
