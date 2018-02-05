//************************************************/
//* @file  :OptionBoard.cpp
//* @brief :�I�����̃N���X
//* @date  :2018/01/31
//* @author:S.Katou
//************************************************/
#include "OptionBoard.h"

#include <SL_TextManager.h>
#include <SL_KeyManager.h>

using namespace ShunLib;

/// <summary>
/// �R���X�g���N�^
/// </summary>
OptionBoard::OptionBoard(int layer,int w, int h):
	m_layer(layer),
	m_width(w),
	m_height(h),
	m_current(0),
	m_isDesided(false)
{
	m_offsetLeft = 0.0f;
	m_offsetTop = 0.0f;
	m_optionList.resize(w*h);
	m_textScale = Vec2::One;
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
OptionBoard::~OptionBoard()
{

}

/// <summary>
/// �X�V
/// </summary>
void OptionBoard::Update(){
	auto key = KeyManager::GetInstance();

	//�L�[���͂ɂ���Ĉړ�������̔ԍ�
	int next = m_current;

	//��L�[�������ꂽ��
	if (key->IsTracker(KeyManager::KEY_CODE::UP        )) { next--; }
	//���L�[�������ꂽ��
	else if (key->IsTracker(KeyManager::KEY_CODE::DOWN )) { next++; }
	//�E�L�[�������ꂽ��
	else if (key->IsTracker(KeyManager::KEY_CODE::RIGHT)) { next += m_height; }
	//���L�[�������ꂽ��
	else if (key->IsTracker(KeyManager::KEY_CODE::LEFT )) { next -= m_height; }

	//���̒l���I�������ł���΃J�[�\���ړ�
	if (next >= 0 && next < (int)m_optionList.size()) {
		m_current = next;
	}

	//���肵�����ǂ���
	m_isDesided = key->IsTracker(KeyManager::KEY_CODE::SPACE);
}

/// <summary>
/// �`��
/// </summary>
void OptionBoard::Render()
{
	//�g�p���Ă����ԂȂ�Ε`�悷��
	if (m_isEnable){
		auto tex = UIResourceHolder::GetInstance();

		//�ʒu���v�Z
		CalcOptionPos();

		//�g�̕`��
		tex->GetTexture(UI_TEXTURE_LIST::OPTION_BOARD)->Draw(Vec2(m_pos.m_x, m_pos.m_y), Vec2(m_scale.m_x, m_scale.m_y), nullptr);

		//�J�[�\���̕`��
		float cursorX = m_optionList[m_current].pos.m_x - CursorWidth();
		float cursorY = m_optionList[m_current].pos.m_y;
		tex->GetTexture(UI_TEXTURE_LIST::OPTION_CURSOR)->Draw(Vec2(m_pos.m_x + cursorX, m_pos.m_y + cursorY), m_textScale, nullptr);

		//�I�����̕`��
		int index = 0;
		Vec2 p(m_pos.m_x, m_pos.m_y);
		for (int i = 0; i < (int)m_optionList.size(); i++)
		{
			if (m_optionList[i].handle != UI_STRING_LIST::UI_STRING_NONE) {
				tex->GetStrTexture(m_optionList[i].handle)->Draw(m_optionList[i].pos + p, m_textScale);
			}
		}
	}
}

/// <summary>
/// �e�L�X�g�̒ǉ�
/// </summary>
/// <param name="text">�e�L�X�g</param>
/// <param name="optionNum">���Ԗڂ̑I������</param>
void OptionBoard::AddText(UI_STRING_LIST text, int optionNum)
{
	//�g�𒴂��Ă����牽�����Ȃ�
	if (optionNum >= (int)m_optionList.size()) {
		return;
	}

	m_optionList[optionNum].handle = text;
}

/// <summary>
/// �I�����̕\���ʒu���v�Z
/// </summary>
void OptionBoard::CalcOptionPos()
{
	using CONSTANT = UIConstantNumber::OPTION_BOARD_CONSTANT;


	//������̍ő剡��
	//(�S�̂̑傫��-(�O�g�̑傫��) - �]�� -(�J�[�\���̕`��ɕK�v�ȃT�C�Y)) / �I�����̐�
	float wStrSize
		= (BoardWidth() - (CONSTANT::FLAME_SIZE * 2 * m_scale.m_x) - m_offsetLeft - (CursorWidth() * 2))/m_width;

	//������̍���
	const float hStrSize = CONSTANT::STRING_TEXTURE_HEIGHT*m_textScale.m_y;

	//�c�̊Ԋu
	//(�S�̂̑傫��-(�O�g�̑傫��) - �]�� - (�I�����̕`��ɕK�v�ȃT�C�Y)) / �]���̐�
	float hInterval
		= (BoardHeight() - (CONSTANT::FLAME_SIZE * 2 * m_scale.m_y) - m_offsetTop - (hStrSize*m_height)) / (m_height + 1);

	for (int i = 0; i < (int)m_optionList.size(); i++){
		//�ォ�牽�Ԗڂ�
		int hIndex = i % m_height;

		//�����牽�Ԗڂ�
		int wIndex = i / m_height;

		//�c�ʒu�Z�b�g
		//(��ɂ���]���̕�) + (��ɂ���I�����̕�) + (�O�g�̑傫��)
		m_optionList[i].pos.m_y = (hInterval*(hIndex + 1)) + (hStrSize *hIndex) + (CONSTANT::FLAME_SIZE * m_scale.m_y) + m_offsetTop;

		//���ʒu�Z�b�g
		//(���ɂ���I�����̐�)+(�J�[�\�����̗]��)+(�O�g�̑傫��)
		m_optionList[i].pos.m_x = (wStrSize * wIndex)+(CursorWidth()*(wIndex+1))+ (CONSTANT::FLAME_SIZE * m_scale.m_x) + m_offsetLeft;
	}
}
