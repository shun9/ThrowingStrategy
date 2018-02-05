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
	m_textureList[OPTION_BOARD] = std::make_unique<Texture>(L"Resources\\Images\\OptionBoard.png");
	m_textureList[OPTION_CURSOR] = std::make_unique<Texture>(L"Resources\\Images\\Cursor.png");
	m_textureList[RED_GAUGE] = std::make_unique<Texture>(L"Resources\\Images\\GaugeRed.png");
	m_textureList[GREEN_GAUGE]  = std::make_unique<Texture>(L"Resources\\Images\\GaugeGreen.png");
	m_textureList[ORANGE_GAUGE] = std::make_unique<Texture>(L"Resources\\Images\\GaugeOrange.png");

	//�����e�N�X�`���ǂݍ���
	m_strTexture.resize(UI_STRING_LIST_END);
	m_strTexture[STRING_START] = std::make_unique<Texture>(L"Resources\\Images\\StartString.png");
	m_strTexture[STRING_END] = std::make_unique<Texture>(L"Resources\\Images\\EndString.png");

	//�V�[���e�N�X�`���ǂݍ���
	m_sceneTextureList.resize(SCENE_TEXTURE_LIST_END);
	m_sceneTextureList[BLACK_BALL] = std::make_unique<Texture>(L"Resources\\Images\\BlackBall.png");
	m_sceneTextureList[TITLE_BACK] = std::make_unique<Texture>(L"Resources\\Images\\TitleBack.png");

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
