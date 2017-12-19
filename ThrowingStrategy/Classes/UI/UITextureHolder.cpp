//************************************************/
//* @file  :UITextureHolder.cpp
//* @brief :UI関連の画像をまとめて保持するクラス
//* @date  :2017/12/13
//* @author:S.Katou
//************************************************/
#include "UITextureHolder.h"

/// <summary>
/// コンストラクタ
/// </summary>
UITextureHolder::UITextureHolder()
{
	m_redGauge = std::make_unique<Texture>(L"Resources\\Images\\GaugeRed.png");
	m_greenGauge = std::make_unique<Texture>(L"Resources\\Images\\GaugeGreen.png");
}

/// <summary>
/// デストラクタ
/// </summary>
UITextureHolder::~UITextureHolder()
{

}
