//************************************************/
//* @file  :UITextureHolder.cpp
//* @brief :UI�֘A�̉摜���܂Ƃ߂ĕێ�����N���X
//* @date  :2018/01/29
//* @author:S.Katou
//************************************************/
#include "UITextureHolder.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
UITextureHolder::UITextureHolder()
{
	m_textureList.resize(TEXTURE_LIST_END);
	m_textureList[RED_GAUGE]    = std::make_unique<Texture>(L"Resources\\Images\\GaugeRed.png");
	m_textureList[GREEN_GAUGE]  = std::make_unique<Texture>(L"Resources\\Images\\GaugeGreen.png");
	m_textureList[ORANGE_GAUGE] = std::make_unique<Texture>(L"Resources\\Images\\GaugeOrange.png");
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
UITextureHolder::~UITextureHolder()
{

}
