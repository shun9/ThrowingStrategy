//************************************************/
//* @file  :ObjectConstantNumber.h
//* @brief :オブジェクト関連の定数
//* @date  :2017/12/12
//* @author:S.Katou
//************************************************/
#pragma once
#include <SL_Math.h>

class ObjectConstantNumber
{

public:
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
		RED = 0,
		BLUE,

		TEAM_END,     //チーム数
	};

	//投げ方
	enum THROW_TYPE
	{
		LINE = 0,

		THROW_TYPE_END,
	};

public:
	//状態を持ったオブジェクト一覧
	static const OBJECT_LIST STATE_OBJECT[5];

public:
	//プレイヤー関連
	class PLAYER_CONSTANT
	{
	public:
		static const float COLLIDER_SIZE;			//本体の当たり判定のサイズ
		static const ShunLib::Vec3 COLLIDER_OFFSET;	//当たり判定の中心位置
		static const ShunLib::Vec3 HP_GAUGE_OFFSET;	//HPゲージの中心位置

		/// <summary>
		/// 持っているオブジェクトの中心位置
		/// </summary>
		/// <param name="num">何番目のアイテムか</param>
		static ShunLib::Vec3 HAVING_OFFSET(int num) {
			return ShunLib::Vec3(0.0f, 2.0f * (num + 1) + 2.0f, 0.0f);
		}
	};

	//ユニット関連
	class UNIT_CONSTANT
	{
	public:
		//ユニットの種類
		enum TYPE_LIST
		{
			NORMAL = 0,

			UNIT_LIST_END,
		};
	public:
		static const ShunLib::Vec3 COLLIDER_OFFSET;	//当たり判定の中心位置
		static const ShunLib::Vec3 HP_GAUGE_OFFSET;	//HPゲージの中心位置
		static const float COLLIDER_BODY_SIZE;		//本体の当たり判定のサイズ
		static const float COLLIDER_ATTACK_SIZE;	//攻撃範囲の当たり判定のサイズ
		static const float COLLIDER_CHASE_SIZE;		//追跡範囲の当たり判定のサイズ
	};

	//防衛対象関連
	class DEFENSE_TARGET_CONSTANT
	{
	public:
		static const float MODEL_SCALE;				//モデルの倍率
		static const ShunLib::Vec3 COLLIDER_OFFSET;	//当たり判定の中心位置
		static const ShunLib::Vec3 COLLIDER_SIZE;	//本体の当たり判定のサイズ
		static const ShunLib::Vec3 HP_GAUGE_OFFSET;	//HPゲージの中心位置
	};

	//召喚師関連
	class SUMMONER_CONSTANT
	{
	public:
		static const ShunLib::Vec3 COLLIDER_OFFSET;	//当たり判定の中心位置
		static const ShunLib::Vec3 COLLIDER_SIZE;	//本体の当たり判定のサイズ
		static const ShunLib::Vec3 HP_GAUGE_OFFSET;	//HPゲージの中心位置
	};

};

