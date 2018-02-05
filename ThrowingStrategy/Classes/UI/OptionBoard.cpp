//************************************************/
//* @file  :OptionBoard.cpp
//* @brief :選択肢のクラス
//* @date  :2018/01/31
//* @author:S.Katou
//************************************************/
#include "OptionBoard.h"

#include <SL_TextManager.h>
#include <SL_KeyManager.h>

using namespace ShunLib;

/// <summary>
/// コンストラクタ
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
/// デストラクタ
/// </summary>
OptionBoard::~OptionBoard()
{

}

/// <summary>
/// 更新
/// </summary>
void OptionBoard::Update(){
	auto key = KeyManager::GetInstance();

	//キー入力によって移動した先の番号
	int next = m_current;

	//上キーが押されたら
	if (key->IsTracker(KeyManager::KEY_CODE::UP        )) { next--; }
	//下キーが押されたら
	else if (key->IsTracker(KeyManager::KEY_CODE::DOWN )) { next++; }
	//右キーが押されたら
	else if (key->IsTracker(KeyManager::KEY_CODE::RIGHT)) { next += m_height; }
	//左キーが押されたら
	else if (key->IsTracker(KeyManager::KEY_CODE::LEFT )) { next -= m_height; }

	//次の値が選択肢内であればカーソル移動
	if (next >= 0 && next < (int)m_optionList.size()) {
		m_current = next;
	}

	//決定したかどうか
	m_isDesided = key->IsTracker(KeyManager::KEY_CODE::SPACE);
}

/// <summary>
/// 描画
/// </summary>
void OptionBoard::Render()
{
	//使用している状態ならば描画する
	if (m_isEnable){
		auto tex = UIResourceHolder::GetInstance();

		//位置を計算
		CalcOptionPos();

		//枠の描画
		tex->GetTexture(UI_TEXTURE_LIST::OPTION_BOARD)->Draw(Vec2(m_pos.m_x, m_pos.m_y), Vec2(m_scale.m_x, m_scale.m_y), nullptr);

		//カーソルの描画
		float cursorX = m_optionList[m_current].pos.m_x - CursorWidth();
		float cursorY = m_optionList[m_current].pos.m_y;
		tex->GetTexture(UI_TEXTURE_LIST::OPTION_CURSOR)->Draw(Vec2(m_pos.m_x + cursorX, m_pos.m_y + cursorY), m_textScale, nullptr);

		//選択肢の描画
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
/// テキストの追加
/// </summary>
/// <param name="text">テキスト</param>
/// <param name="optionNum">何番目の選択肢か</param>
void OptionBoard::AddText(UI_STRING_LIST text, int optionNum)
{
	//枠を超えていたら何もしない
	if (optionNum >= (int)m_optionList.size()) {
		return;
	}

	m_optionList[optionNum].handle = text;
}

/// <summary>
/// 選択肢の表示位置を計算
/// </summary>
void OptionBoard::CalcOptionPos()
{
	using CONSTANT = UIConstantNumber::OPTION_BOARD_CONSTANT;


	//文字列の最大横幅
	//(全体の大きさ-(外枠の大きさ) - 余白 -(カーソルの描画に必要なサイズ)) / 選択肢の数
	float wStrSize
		= (BoardWidth() - (CONSTANT::FLAME_SIZE * 2 * m_scale.m_x) - m_offsetLeft - (CursorWidth() * 2))/m_width;

	//文字列の高さ
	const float hStrSize = CONSTANT::STRING_TEXTURE_HEIGHT*m_textScale.m_y;

	//縦の間隔
	//(全体の大きさ-(外枠の大きさ) - 余白 - (選択肢の描画に必要なサイズ)) / 余白の数
	float hInterval
		= (BoardHeight() - (CONSTANT::FLAME_SIZE * 2 * m_scale.m_y) - m_offsetTop - (hStrSize*m_height)) / (m_height + 1);

	for (int i = 0; i < (int)m_optionList.size(); i++){
		//上から何番目か
		int hIndex = i % m_height;

		//左から何番目か
		int wIndex = i / m_height;

		//縦位置セット
		//(上にある余白の幅) + (上にある選択肢の幅) + (外枠の大きさ)
		m_optionList[i].pos.m_y = (hInterval*(hIndex + 1)) + (hStrSize *hIndex) + (CONSTANT::FLAME_SIZE * m_scale.m_y) + m_offsetTop;

		//横位置セット
		//(左にある選択肢の数)+(カーソル分の余白)+(外枠の大きさ)
		m_optionList[i].pos.m_x = (wStrSize * wIndex)+(CursorWidth()*(wIndex+1))+ (CONSTANT::FLAME_SIZE * m_scale.m_x) + m_offsetLeft;
	}
}
