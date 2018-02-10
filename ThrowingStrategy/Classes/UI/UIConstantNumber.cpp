//************************************************/
//* @file  :UIConstantNumber.cpp
//* @brief :UI�֘A�̒萔
//* @date  :2018/01/31
//* @author:S.Katou
//************************************************/
#include "UIConstantNumber.h"
using namespace ShunLib;

//HP�Q�[�W
const Vec3  UIConstantNumber::HP_GAUGE_CONSTANT::SCALE = { 3.5f,1.0f,0.5f };

//�\�����e�n�_�̃J�[�\��
const Vec3  UIConstantNumber::THROW_CURSOR_CONSTANT::SCALE = { 1.0f,1.0f,1.0f };

//�I����
const float  UIConstantNumber::OPTION_BOARD_CONSTANT::TEXTURE_WIDTH = 512.0f;
const float  UIConstantNumber::OPTION_BOARD_CONSTANT::TEXTURE_HEIGHT = 256.0f;
const float  UIConstantNumber::OPTION_BOARD_CONSTANT::STRING_TEXTURE_HEIGHT = 32.0f;
const float  UIConstantNumber::OPTION_BOARD_CONSTANT::CURSOR_SIZE = 32.0f;
const float  UIConstantNumber::OPTION_BOARD_CONSTANT::FLAME_SIZE = 16.0f;

//�t�F�[�h�p����
const Vec2  UIConstantNumber::FADE_BLACK::ANCHOR = Vec2(128.0f, 128.0f);
const Vec2  UIConstantNumber::FADE_BLACK::START_POS = Vec2(-1000.0f, 400.0f);
const Vec2  UIConstantNumber::FADE_BLACK::START_SPEED = Vec2(1.2f, -1.0f);
const float  UIConstantNumber::FADE_BLACK::SCALE_MAX = 10.0f;
const float  UIConstantNumber::FADE_BLACK::SCALE_MIN = 0.8f;
const float  UIConstantNumber::FADE_BLACK::GRAVITY = 0.0015f;
