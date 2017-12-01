//************************************************/
//* @file  :ObjectConstantNumber.h
//* @brief :オブジェクト関連の定数
//* @date  :2017/11/16
//* @author:S.Katou
//************************************************/
#pragma once
#include <SL_Lerp.h>

//オブジェクト一覧
enum OBJECT_LIST
{
	ROOT = 0,		//ルートオブジェクト
	PLAYER,			//プレイヤー
	COMMANDER,      //指揮官
	UNIT,           //召喚されるユニット
	BLOCK,          //ブロック
	DEFENSE_TARGET,	//防衛対象
	SUMMONER,		//ユニットを召喚するオブジェクト
	STAGE,			//ステージ

	OBJECT_LIST_END,//オブジェクトの種類数
};

//ユニットの種類
enum UNIT_LIST
{
	NORMAL = 0,

	UNIT_LIST_END,
};

//ステージ一覧
enum STAGE_LIST
{
	GROUND = 0,		//地面のみのステージ

	STAGE_LIST_END,//ステージ種類数
};

//チーム分け
enum TEAM
{
	NONE = -1,    //チーム無し
	RED  = 0,
	BLUE,

	TEAM_END,     //チーム数
};

//投げ方
enum THROW_TYPE
{
	LINE = 0,

	THROW_TYPE_END,
};

