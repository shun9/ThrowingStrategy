//************************************************/
//* @file  :FadeExecutor.h
//* @brief :�V�[���J�ڎ��̃t�F�[�h���s���N���X
//* @date  :2018/02/05
//* @author:S.Katou
//************************************************/
#pragma once
#include <SL_Math.h>
#include "../../UI/UIConstantNumber.h"

class FadeExecutor
{
public:
	using Vec2 = ShunLib::Vec2;
	using CONSTANT = UIConstantNumber::FADE_BLACK;

private:
	//�o�ߎ���
	int m_frameCnt;

	//�I�����鎞��
	int m_endFlame;

	//�i�s�̊���
	float m_progressRatio;

	//�t�F�[�h�p�摜�̒��S�ʒu
	Vec2 m_pos;

	//�t�F�[�h�p�摜�̈ړ��p
	Vec2 m_vel;

	//�t�F�[�h�p�摜�̊g�嗦
	float m_scale;

	//�t�F�[�h�A�E�g���I���������ǂ���
	bool m_isEndedFadeOut;

	//�I���������ǂ���
	bool m_isEnded;

public:
	FadeExecutor():m_frameCnt(0), m_endFlame(6000) {
		Reset();
	}
	~FadeExecutor() {}

	//�X�V�@�`��
	void Update();
	void Render();

	//�ŏ��ɖ߂�
	void Reset();

	/*--Getter--*/
	bool IsEnded() { return m_isEnded; }
	bool IsEndedFadeOut() { return m_isEndedFadeOut; }
private:
	//�t�F�[�h�A�E�g���̏���
	void FadeOut();

	//�t�F�[�h�C�����̏���
	void FadeIn();
};