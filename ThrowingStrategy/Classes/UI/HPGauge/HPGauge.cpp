//************************************************/
//* @file  :HPGauge.cpp
//* @brief :HPゲージ
//* @date  :2017/12/13
//* @author:S.Katou
//************************************************/
#include "HPGauge.h"
#include <SL_MacroConstants.h>

/// <summary>
/// コンストラクタ
/// </summary>
HPGauge::HPGauge()
{
	m_texture = new ShunLib::Texture(L"");
}

/// <summary>
/// デストラクタ
/// </summary>
HPGauge::~HPGauge()
{
	SAFE_DELETE(m_texture);
}
