//************************************************/
//* @file  :OptionBoard.h
//* @brief :選択肢のクラス
//* @date  :2018/01/31
//* @author:S.Katou
//************************************************/
#pragma once
#include <vector>
#include <SL_Math.h>
#include "UI.h"
#include "UIResourceHolder.h"
#include "UIConstantNumber.h"

//選択肢の描画用情報
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
	int m_layer;  //自身のレイヤー番号
	int m_width;  //横に並ぶ選択肢の数
	int m_height; //縦に並ぶ選択肢の数
	int m_current;//現在選択中の番号

	float m_offsetLeft;//外枠からの距離 左側
	float m_offsetTop; //外枠からの距離 上側

	//決定が押されたかどうか
	bool m_isDesided;

	//テキストの拡大率
	Vec2 m_textScale;

	//テキストのハンドル
	std::vector<OptionData>m_optionList;

public:
	OptionBoard(int layer,int w,int h);
	~OptionBoard();

	//更新　描画
	void Update()override;
	void Render()override;

	//テキストの追加
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
	//選択肢の表示位置を計算
	void CalcOptionPos();
};