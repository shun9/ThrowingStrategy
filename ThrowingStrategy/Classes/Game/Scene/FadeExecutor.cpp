//************************************************/
//* @file  :FadeExecutor.cpp
//* @brief :シーン遷移時のフェードを行うクラス
//* @date  :2018/02/05
//* @author:S.Katou
//************************************************/
#include "FadeExecutor.h"
#include "../../Main/SL_MyStepTimer.h"
#include "../../UI/UIResourceHolder.h"
#include "../../UI/UIConstantNumber.h"

/// <summary>
/// 更新
/// </summary>
void FadeExecutor::Update()
{
	//経過割合を計算
	m_progressRatio = m_timeCnt / m_endTime;

	//全体時間の半分でフェードアウト
	if (m_progressRatio <= 0.5f) {
		FadeOut();
	}
	//残りの半分でフェードイン
	else if (m_progressRatio <= 1.0f) {
		m_isEndedFadeOut = true;
		FadeIn();
	}
	else {
		m_isEnded = true;
	}

	//時間をカウント
	m_timeCnt += ShunLib::MyStepTimer::GetInstance()->GetElapsedSeconds();
}

/// <summary>
/// 描画
/// </summary>
void FadeExecutor::Render()
{
	auto tex = UIResourceHolder::GetInstance()->GetSceneTexture(SCENE_TEXTURE_LIST::BLACK_BALL);

	tex->Draw(m_pos, Vec2(m_scale, m_scale),nullptr,UIConstantNumber::FADE_BLACK::ANCHOR);
}

/// <summary>
/// 初期化
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
/// フェードアウト中の処理
/// </summary>
void FadeExecutor::FadeOut()
{
	//フェードアウトの進行割合
	float ratio = m_timeCnt / (m_endTime / 2.0f);

	//拡大率 最大　最小
	const float max = UIConstantNumber::FADE_BLACK::SCALE_MAX;
	const float min = UIConstantNumber::FADE_BLACK::SCALE_MIN;

	//拡大率設定
	float scale = max - min;
	scale *= ratio;
	m_scale = scale + min;
}

/// <summary>
/// フェードイン中の処理
/// </summary>
void FadeExecutor::FadeIn()
{
	//フェードアウトの進行割合
	float ratio = m_timeCnt / (m_endTime / 2.0f) - 1.0f;

	//拡大率 最大　最小
	const float max = UIConstantNumber::FADE_BLACK::SCALE_MAX;
	const float min = UIConstantNumber::FADE_BLACK::SCALE_MIN;

	//拡大率設定
	float scale = max - min;
	scale -= (scale * ratio);
	m_scale = scale;
}
