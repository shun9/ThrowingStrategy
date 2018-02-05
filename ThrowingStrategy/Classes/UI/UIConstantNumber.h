//************************************************/
//* @file  :UIConstantNumber.h
//* @brief :UI関連の定数
//* @date  :2018/01/31
//* @author:S.Katou
//************************************************/
#pragma once
#include <SL_Math.h>

class UIConstantNumber {
public:
	using Vec3 = ShunLib::Vec3;

	//テキストのレイヤー一覧
	enum TEXT_LAYER_LIST {
		TITLE_LAYER,
		TEXT_LAYER_LIST_END
	};

	//HPゲージ
	class HP_GAUGE_CONSTANT {
	public:
		static const Vec3 SCALE;
	};

	//予測着弾地点のカーソル
	class THROW_CURSOR_CONSTANT {
	public:
		static const Vec3 SCALE;
	};

	//選択肢
	class OPTION_BOARD_CONSTANT {
	public:
		//画像の縦と横のサイズ
		static const float TEXTURE_WIDTH;
		static const float TEXTURE_HEIGHT;

		//文字画像の高さ（1文字のサイズ）
		static const float STRING_TEXTURE_HEIGHT;

		//カーソルのサイズ
		static const float CURSOR_SIZE;

		//外枠の幅
		static const float FLAME_SIZE;
	};
};