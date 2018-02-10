//************************************************/
//* @file  :FadeExecutor.h
//* @brief :シーン遷移時のフェードを行うクラス
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
	//経過時間
	int m_frameCnt;

	//終了する時間
	int m_endFlame;

	//進行の割合
	float m_progressRatio;

	//フェード用画像の中心位置
	Vec2 m_pos;

	//フェード用画像の移動用
	Vec2 m_vel;

	//フェード用画像の拡大率
	float m_scale;

	//フェードアウトが終了したかどうか
	bool m_isEndedFadeOut;

	//終了したかどうか
	bool m_isEnded;

public:
	FadeExecutor():m_frameCnt(0), m_endFlame(6000) {
		Reset();
	}
	~FadeExecutor() {}

	//更新　描画
	void Update();
	void Render();

	//最初に戻す
	void Reset();

	/*--Getter--*/
	bool IsEnded() { return m_isEnded; }
	bool IsEndedFadeOut() { return m_isEndedFadeOut; }
private:
	//フェードアウト中の処理
	void FadeOut();

	//フェードイン中の処理
	void FadeIn();
};