//************************************************/
//* @file  :FadeExecutor.cpp
//* @brief :�V�[���J�ڎ��̃t�F�[�h���s���N���X
//* @date  :2018/02/05
//* @author:S.Katou
//************************************************/
#include "FadeExecutor.h"
#include "../../Main/SL_MyStepTimer.h"
#include "../../UI/UIResourceHolder.h"
#include "../../UI/UIConstantNumber.h"

/// <summary>
/// �X�V
/// </summary>
void FadeExecutor::Update()
{
	//�o�ߊ������v�Z
	m_progressRatio = m_timeCnt / m_endTime;

	//�S�̎��Ԃ̔����Ńt�F�[�h�A�E�g
	if (m_progressRatio <= 0.5f) {
		FadeOut();
	}
	//�c��̔����Ńt�F�[�h�C��
	else if (m_progressRatio <= 1.0f) {
		m_isEndedFadeOut = true;
		FadeIn();
	}
	else {
		m_isEnded = true;
	}

	//���Ԃ��J�E���g
	m_timeCnt += ShunLib::MyStepTimer::GetInstance()->GetElapsedSeconds();
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
	m_timeCnt = 0.0f;
	m_pos = Vec2(300.0f,200.0f);
	m_scale = UIConstantNumber::FADE_BLACK::SCALE_MIN;
	m_isEndedFadeOut = false;
	m_isEnded = false;
}

/// <summary>
/// �t�F�[�h�A�E�g���̏���
/// </summary>
void FadeExecutor::FadeOut()
{
	//�t�F�[�h�A�E�g�̐i�s����
	float ratio = m_timeCnt / (m_endTime / 2.0f);

	//�g�嗦 �ő�@�ŏ�
	const float max = UIConstantNumber::FADE_BLACK::SCALE_MAX;
	const float min = UIConstantNumber::FADE_BLACK::SCALE_MIN;

	//�g�嗦�ݒ�
	float scale = max - min;
	scale *= ratio;
	m_scale = scale + min;
}

/// <summary>
/// �t�F�[�h�C�����̏���
/// </summary>
void FadeExecutor::FadeIn()
{
	//�t�F�[�h�A�E�g�̐i�s����
	float ratio = m_timeCnt / (m_endTime / 2.0f) - 1.0f;

	//�g�嗦 �ő�@�ŏ�
	const float max = UIConstantNumber::FADE_BLACK::SCALE_MAX;
	const float min = UIConstantNumber::FADE_BLACK::SCALE_MIN;

	//�g�嗦�ݒ�
	float scale = max - min;
	scale -= (scale * ratio);
	m_scale = scale;
}
