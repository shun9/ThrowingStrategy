//************************************************/
//* @file  :UIResourceHolder.h
//* @brief :UI関連の画像,モデルをまとめて保持するクラス
//* @date  :2018/01/31
//* @author:S.Katou
//************************************************/
#pragma once
#include <vector>
#include <memory>
#include <SL_Singleton.h>
#include <SL_Texture.h>
#include <SL_Model.h>

//シーン固有の画像(背景など)一覧
enum SCENE_TEXTURE_LIST {
	BLACK_BALL,//黒い球
	TITLE_BACK,//タイトルの背景
	SCENE_TEXTURE_LIST_END
};

//UIのテクスチャの種類一覧
enum UI_TEXTURE_LIST {

	OPTION_BOARD, //選択肢ボードの枠
	OPTION_CURSOR,//選択肢のカーソル
	RED_GAUGE,    //赤色ゲージ
	GREEN_GAUGE,  //緑色ゲージ
	ORANGE_GAUGE, //オレンジ色ゲージ

	UI_TEXTURE_LIST_END
};

//UIの文字画像の種類一覧
enum UI_STRING_LIST {
	UI_STRING_NONE = -1,
	STRING_START,//はじめる
	STRING_END,  //おわる
	UI_STRING_LIST_END
};

//UIのモデルの種類一覧
enum UI_MODEL_LIST {
	THROW_CURSOR,//投擲の目標地点
	UI_MODEL_LIST_END
};

class UIResourceHolder : public ShunLib::Singleton<UIResourceHolder>
{
	friend ShunLib::Singleton<UIResourceHolder>;
public:
	using Texture = ShunLib::Texture;
	using Model = ShunLib::Model;

private:

	//UI画像
	std::vector<std::unique_ptr<Texture>>m_textureList;

	//文字画像
	std::vector<std::unique_ptr<Texture>>m_strTexture;

	//シーン画像
	std::vector<std::unique_ptr<Texture>>m_sceneTextureList;

	//UIモデル
	std::vector<std::unique_ptr<Model>>m_modelList;

public:
	/*--Getter--*/
	Texture* GetTexture(UI_TEXTURE_LIST tex) { return m_textureList[tex].get(); }
	Texture* GetStrTexture(UI_STRING_LIST tex) { return m_strTexture[tex].get(); }
	Texture* GetSceneTexture(SCENE_TEXTURE_LIST tex) { return m_sceneTextureList[tex].get(); }
	Model* GetModel(UI_MODEL_LIST mod) { return m_modelList[mod].get(); }

private:
	UIResourceHolder();
	~UIResourceHolder();
};