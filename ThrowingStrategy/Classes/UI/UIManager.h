//************************************************/
//* @file  :UIManager.h
//* @brief :UI���܂Ƃ߂ĊǗ�����N���X
//* @date  :2017/12/13
//* @author:S.Katou
//************************************************/
#pragma once
#include <SL_Singleton.h>

class UIManager : public ShunLib::Singleton<UIManager>
{
	friend ShunLib::Singleton<UIManager>;

private:
	UIManager() {}
	~UIManager() {}

private:

};
