//************************************************/
//* @file  :UIConstantNumber.cpp
//* @brief :UI関連の定数
//* @date  :2018/01/31
//* @author:S.Katou
//************************************************/
#include "UIConstantNumber.h"
using namespace ShunLib;

//HPゲージ
const Vec3  UIConstantNumber::HP_GAUGE_CONSTANT::SCALE = { 3.5f,1.0f,0.5f };

//予測着弾地点のカーソル
const Vec3  UIConstantNumber::THROW_CURSOR_CONSTANT::SCALE = { 1.0f,1.0f,1.0f };

//選択肢
const float  UIConstantNumber::OPTION_BOARD_CONSTANT::TEXTURE_WIDTH = 512.0f;
const float  UIConstantNumber::OPTION_BOARD_CONSTANT::TEXTURE_HEIGHT = 256.0f;
const float  UIConstantNumber::OPTION_BOARD_CONSTANT::STRING_TEXTURE_HEIGHT = 32.0f;
const float  UIConstantNumber::OPTION_BOARD_CONSTANT::CURSOR_SIZE = 32.0f;
const float  UIConstantNumber::OPTION_BOARD_CONSTANT::FLAME_SIZE = 16.0f;

//フェード用黒玉
const Vec2  UIConstantNumber::FADE_BLACK::ANCHOR = Vec2(128.0f, 128.0f);
const float  UIConstantNumber::FADE_BLACK::SCALE_MAX = 10.0f;
const float  UIConstantNumber::FADE_BLACK::SCALE_MIN = 0.8f;
