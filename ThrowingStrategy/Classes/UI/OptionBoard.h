//************************************************/
//* @file  :OptionBoard.h
//* @brief :�I�����̃N���X
//* @date  :2018/01/31
//* @author:S.Katou
//************************************************/
#pragma once
#include <vector>
#include <SL_Math.h>
#include "UI.h"
#include "UIResourceHolder.h"
#include "UIConstantNumber.h"

//�I�����̕`��p���
struct OptionData {
	UI_STRING_LIST handle;
	ShunLib::Vec2 pos;
	OptionData() :handle(UI_STRING_NONE) {}
};

class OptionBoard : public UI
{
public:
	using Vec2 = ShunLib::Vec2;

private:
	int m_layer;  //���g�̃��C���[�ԍ�
	int m_width;  //���ɕ��ԑI�����̐�
	int m_height; //�c�ɕ��ԑI�����̐�
	int m_current;//���ݑI�𒆂̔ԍ�

	float m_offsetLeft;//�O�g����̋��� ����
	float m_offsetTop; //�O�g����̋��� �㑤

	//���肪�����ꂽ���ǂ���
	bool m_isDesided;

	//�e�L�X�g�̊g�嗦
	Vec2 m_textScale;

	//�e�L�X�g�̃n���h��
	std::vector<OptionData>m_optionList;

public:
	OptionBoard(int layer,int w,int h);
	~OptionBoard();

	//�X�V�@�`��
	void Update()override;
	void Render()override;

	//�e�L�X�g�̒ǉ�
	void AddText(UI_STRING_LIST text,int optionNum);

	/*--Setter--*/
	void Offset(float left, float top) { m_offsetLeft = left; m_offsetTop = top; }
	void CurrentOption(int op) { m_current = op; }

	/*--Getter--*/
	float BoardWidth  () { return UIConstantNumber::OPTION_BOARD_CONSTANT::TEXTURE_WIDTH * m_scale.m_x; }
	float BoardHeight () { return UIConstantNumber::OPTION_BOARD_CONSTANT::TEXTURE_HEIGHT * m_scale.m_y; }
	float CursorWidth () { return UIConstantNumber::OPTION_BOARD_CONSTANT::CURSOR_SIZE * m_textScale.m_x; }
	float CursorHeirht() { return UIConstantNumber::OPTION_BOARD_CONSTANT::CURSOR_SIZE * m_textScale.m_y; }
	bool IsDesided    () { return m_isDesided; }
	int CurrentOption () { return m_current; }

private:
	//�I�����̕\���ʒu���v�Z
	void CalcOptionPos();
};