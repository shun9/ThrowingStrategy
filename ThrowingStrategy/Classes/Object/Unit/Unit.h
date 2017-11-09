//************************************************/
//* @file  :Unit.h
//* @brief :召喚されるユニット
//* @date  :2017/11/01
//* @author:S.Katou
//************************************************/
#pragma once
#include "../StateObject.h"

class Unit :public StateObject<Unit>
{
private:
	int m_type;

public:
	Unit():StateObject(this) {}
	~Unit() {}

	//初期化　終了
	void Initialize()override;
	void Finalize()override;
};