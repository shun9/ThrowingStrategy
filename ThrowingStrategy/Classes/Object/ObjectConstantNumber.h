//************************************************/
//* @file  :ObjectConstantNumber.h
//* @brief :オブジェクト関連の定数
//* @date  :2017/11/02
//* @author:S.Katou
//************************************************/
#pragma once

//オブジェクトのパラメーターを取得する
#define OBJ_PARAM(type) ObjectParamHolder::GetInstance()->GetParam(type)

//オブジェクト一覧
enum OBJECT_LIST
{
	PLAYER = 0,     //プレイヤー
	COMMANDER,      //指揮官
	UNIT,           //召喚されるユニット
	OBJECT_LIST_END,//オブジェクトの種類数
};

//チーム分け
enum TEAM
{
	NONE = -1,    //チーム無し
	RED  = 0,
	BLUE,
	TEAM_END,     //チーム数
};