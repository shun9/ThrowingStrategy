//************************************************/
//* @file  :HPGauge.cpp
//* @brief :HP�Q�[�W
//* @date  :2017/12/13
//* @author:S.Katou
//************************************************/
#include "HPGauge.h"
#include <SL_MacroConstants.h>

/// <summary>
/// �R���X�g���N�^
/// </summary>
HPGauge::HPGauge()
{
	m_texture = new ShunLib::Texture(L"");
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
HPGauge::~HPGauge()
{
	SAFE_DELETE(m_texture);
}
