//************************************************/
//* @file  :Unit.h
//* @brief :��������郆�j�b�g
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

	//�������@�I��
	void Initialize()override;
	void Finalize()override;
};