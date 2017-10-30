//************************************************/
//* @file  :ObjectConstantNumber.h
//* @brief :オブジェクト関連の定数
//* @date  :2017/10/30
//* @author:S.Katou
//************************************************/
#pragma once

//オブジェクト一覧
enum OBJECT_LIST
{
	PLAYER = 0,
	num,//オブジェクトの種類数
};

//チーム分け
enum TEAM
{
	RED  = 0,
	BLUE,
	num ,     //チーム数
	NONE = -1,//チーム無し
};