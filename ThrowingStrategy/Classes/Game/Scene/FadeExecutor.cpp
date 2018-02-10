//************************************************/
//* @file  :FadeExecutor.cpp
//* @brief :�V�[���J�ڎ��̃t�F�[�h���s���N���X
//* @date  :2018/02/05
//* @author:S.Katou
//************************************************/
#include "FadeExecutor.h"
#include "../../Main/SL_MyStepTimer.h"
#include "../../UI/UIResourceHolder.h"

using namespace ShunLib;

/// <summary>
/// �X�V
/// </summary>
void FadeExecutor::Update()
{
	//�o�ߊ������v�Z
	m_progressRatio = static_cast<float>(m_frameCnt) / m_endFlame;

	//�S�̎��Ԃ̔����Ńt�F�[�h�A�E�g
	if (m_progressRatio <= 0.5f) {
		FadeOut();
	}
	//�c��̔����Ńt�F�[�h�C��
	else if (m_progressRatio <= 1.0f) {
		//�t�F�[�h�A�E�g���I���������
		if (!m_isEndedFadeOut) {
			m_isEndedFadeOut = true;
			m_vel.m_y *= -1;
		}
		FadeIn();
	}
	else {
		m_isEnded = true;
	}

	//���Ԃ��J�E���g
	m_frameCnt++;
}

/// <summary>
/// �`��
/// </summary>
void FadeExecutor::Render()
{
	auto tex = UIResourceHolder::GetInstance()->GetSceneTexture(SCENE_TEXTURE_LIST::BLACK_BALL);

	tex->Draw(m_pos, Vec2(m_scale, m_scale),nullptr,UIConstantNumber::FADE_BLACK::ANCHOR);
}

/// <summary>
/// ������
/// </summary>
void FadeExecutor::Reset()
{
	m_frameCnt = 0;
	m_pos = CONSTANT::START_POS;
	m_vel = CONSTANT::START_SPEED;
	m_scale = CONSTANT::SCALE_MIN;
	m_isEndedFadeOut = false;
	m_isEnded = false;
}

/// <summary>
/// �t�F�[�h�A�E�g���̏���
/// </summary>
void FadeExecutor::FadeOut()
{
	//�t�F�[�h�A�E�g�̐i�s����
	float ratio = static_cast<float>(m_frameCnt) / (m_endFlame / 2);

	//�ړ�
	if (ratio < 0.4f){
		m_pos = m_pos + m_vel;
		m_vel.m_y += CONSTANT::GRAVITY;
	}

	//�g�嗦�p����
	float scaleRatio = Max((ratio - 0.5f) * 2.0f,0.0f);

	//�g�嗦�ݒ�
	float scale = CONSTANT::SCALE_MAX - CONSTANT::SCALE_MIN;
	scale *= scaleRatio;
	m_scale = scale + CONSTANT::SCALE_MIN;
}

/// <summary>
/// �t�F�[�h�C�����̏���
/// </summary>
void FadeExecutor::FadeIn()
{
	//�t�F�[�h�A�E�g�̐i�s����
	float ratio = static_cast<float>(m_frameCnt) / (m_endFlame / 2) - 1.0f;

	//�ړ�
	if (ratio >= 0.6f) {
		m_pos = m_pos + m_vel;
		m_vel.m_y += CONSTANT::GRAVITY;
	}

	//�g�嗦�p����
	float scaleRatio = Min(ratio / 0.5f,1.0f);

	//�g�嗦�ݒ�
	float scale = CONSTANT::SCALE_MAX - CONSTANT::SCALE_MIN;
	scale -= (scale * scaleRatio);
	m_scale = scale + CONSTANT::SCALE_MIN;
}
