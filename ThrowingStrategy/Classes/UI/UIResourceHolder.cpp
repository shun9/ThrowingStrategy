//************************************************/
//* @file  :UIResourceHolder.cpp
//* @brief :UI�֘A�̉摜,���f�����܂Ƃ߂ĕێ�����N���X
//* @date  :2018/01/31
//* @author:S.Katou
//************************************************/
#include "UIResourceHolder.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
UIResourceHolder::UIResourceHolder()
{
	//�e�N�X�`���ǂݍ���
	m_textureList.resize(UI_TEXTURE_LIST_END);
	m_textureList[RED_GAUGE]    = std::make_unique<Texture>(L"Resources\\Images\\GaugeRed.png");
	m_textureList[GREEN_GAUGE]  = std::make_unique<Texture>(L"Resources\\Images\\GaugeGreen.png");
	m_textureList[ORANGE_GAUGE] = std::make_unique<Texture>(L"Resources\\Images\\GaugeOrange.png");

	//���f���ǂݍ���
	m_modelList.resize(UI_MODEL_LIST_END);
	m_modelList[THROW_CURSOR] = std::make_unique<Model>(L"CModel\\ThrowPoint.cmo");
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
UIResourceHolder::~UIResourceHolder()
{

}
