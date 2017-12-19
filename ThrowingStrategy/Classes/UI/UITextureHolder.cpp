//************************************************/
//* @file  :UITextureHolder.cpp
//* @brief :UI�֘A�̉摜���܂Ƃ߂ĕێ�����N���X
//* @date  :2017/12/13
//* @author:S.Katou
//************************************************/
#include "UITextureHolder.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
UITextureHolder::UITextureHolder()
{
	m_redGauge = std::make_unique<Texture>(L"Resources\\Images\\GaugeRed.png");
	m_greenGauge = std::make_unique<Texture>(L"Resources\\Images\\GaugeGreen.png");
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
UITextureHolder::~UITextureHolder()
{

}
