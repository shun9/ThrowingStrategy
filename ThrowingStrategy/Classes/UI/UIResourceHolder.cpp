//************************************************/
//* @file  :UIResourceHolder.cpp
//* @brief :UI関連の画像,モデルをまとめて保持するクラス
//* @date  :2018/01/31
//* @author:S.Katou
//************************************************/
#include "UIResourceHolder.h"

/// <summary>
/// コンストラクタ
/// </summary>
UIResourceHolder::UIResourceHolder()
{
	//テクスチャ読み込み
	m_textureList.resize(UI_TEXTURE_LIST_END);
	m_textureList[OPTION_BOARD] = std::make_unique<Texture>(L"Resources\\Images\\OptionBoard.png");
	m_textureList[OPTION_CURSOR] = std::make_unique<Texture>(L"Resources\\Images\\Cursor.png");
	m_textureList[RED_GAUGE] = std::make_unique<Texture>(L"Resources\\Images\\GaugeRed.png");
	m_textureList[GREEN_GAUGE]  = std::make_unique<Texture>(L"Resources\\Images\\GaugeGreen.png");
	m_textureList[ORANGE_GAUGE] = std::make_unique<Texture>(L"Resources\\Images\\GaugeOrange.png");

	//文字テクスチャ読み込み
	m_strTexture.resize(UI_STRING_LIST_END);
	m_strTexture[STRING_START] = std::make_unique<Texture>(L"Resources\\Images\\StartString.png");
	m_strTexture[STRING_END] = std::make_unique<Texture>(L"Resources\\Images\\EndString.png");

	//モデル読み込み
	m_modelList.resize(UI_MODEL_LIST_END);
	m_modelList[THROW_CURSOR] = std::make_unique<Model>(L"CModel\\ThrowPoint.cmo");
}

/// <summary>
/// デストラクタ
/// </summary>
UIResourceHolder::~UIResourceHolder()
{

}
