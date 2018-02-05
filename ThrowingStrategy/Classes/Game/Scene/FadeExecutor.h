//************************************************/
//* @file  :FadeExecutor.h
//* @brief :シーン遷移時のフェードを行うクラス
//* @date  :2018/02/05
//* @author:S.Katou
//************************************************/
#pragma once
#include <SL_Math.h>

class FadeExecutor
{
public:
	using Vec2 = ShunLib::Vec2;

private:
	//経過時間
	float m_timeCnt;

	//終了する時間
	float m_endTime;

	//進行の割合
	float m_progressRatio;

	//フェード用画像の中心位置
	Vec2 m_pos;

	//フェード用画像の拡大率
	float m_scale;

	//フェードアウトが終了したかどうか
	bool m_isEndedFadeOut;

	//終了したかどうか
	bool m_isEnded;

public:
	FadeExecutor():m_timeCnt(0.0f),m_endTime(5.0f) {
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