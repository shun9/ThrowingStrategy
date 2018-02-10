//************************************************/
//* @file  :FadeExecutor.cpp
//* @brief :シーン遷移時のフェードを行うクラス
//* @date  :2018/02/05
//* @author:S.Katou
//************************************************/
#include "FadeExecutor.h"
#include "../../Main/SL_MyStepTimer.h"
#include "../../UI/UIResourceHolder.h"

using namespace ShunLib;

/// <summary>
/// 更新
/// </summary>
void FadeExecutor::Update()
{
	//経過割合を計算
	m_progressRatio = static_cast<float>(m_frameCnt) / m_endFlame;

	//全体時間の半分でフェードアウト
	if (m_progressRatio <= 0.5f) {
		FadeOut();
	}
	//残りの半分でフェードイン
	else if (m_progressRatio <= 1.0f) {
		//フェードアウトが終わった直後
		if (!m_isEndedFadeOut) {
			m_isEndedFadeOut = true;
			m_vel.m_y *= -1;
		}
		FadeIn();
	}
	else {
		m_isEnded = true;
	}

	//時間をカウント
	m_frameCnt++;
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
	m_frameCnt = 0;
	m_pos = CONSTANT::START_POS;
	m_vel = CONSTANT::START_SPEED;
	m_scale = CONSTANT::SCALE_MIN;
	m_isEndedFadeOut = false;
	m_isEnded = false;
}

/// <summary>
/// フェードアウト中の処理
/// </summary>
void FadeExecutor::FadeOut()
{
	//フェードアウトの進行割合
	float ratio = static_cast<float>(m_frameCnt) / (m_endFlame / 2);

	//移動
	if (ratio < 0.4f){
		m_pos = m_pos + m_vel;
		m_vel.m_y += CONSTANT::GRAVITY;
	}

	//拡大率用割合
	float scaleRatio = Max((ratio - 0.5f) * 2.0f,0.0f);

	//拡大率設定
	float scale = CONSTANT::SCALE_MAX - CONSTANT::SCALE_MIN;
	scale *= scaleRatio;
	m_scale = scale + CONSTANT::SCALE_MIN;
}

/// <summary>
/// フェードイン中の処理
/// </summary>
void FadeExecutor::FadeIn()
{
	//フェードアウトの進行割合
	float ratio = static_cast<float>(m_frameCnt) / (m_endFlame / 2) - 1.0f;

	//移動
	if (ratio >= 0.6f) {
		m_pos = m_pos + m_vel;
		m_vel.m_y += CONSTANT::GRAVITY;
	}

	//拡大率用割合
	float scaleRatio = Min(ratio / 0.5f,1.0f);

	//拡大率設定
	float scale = CONSTANT::SCALE_MAX - CONSTANT::SCALE_MIN;
	scale -= (scale * scaleRatio);
	m_scale = scale + CONSTANT::SCALE_MIN;
}
