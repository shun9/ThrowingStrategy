//************************************************/
//* @file  :UITextureHolder.h
//* @brief :UI関連の画像をまとめて保持するクラス
//* @date  :2018/01/29
//* @author:S.Katou
//************************************************/
#pragma once
#include <vector>
#include <memory>
#include <SL_Singleton.h>
#include <SL_Texture.h>

//テクスチャの種類一覧
enum TEXTURE_LIST {
	RED_GAUGE,
	GREEN_GAUGE,
	ORANGE_GAUGE,

	TEXTURE_LIST_END
};

class UITextureHolder : public ShunLib::Singleton<UITextureHolder>
{
	friend ShunLib::Singleton<UITextureHolder>;
public:
	using Texture = ShunLib::Texture;

private:
	std::vector<std::unique_ptr<Texture>>m_textureList;

public:
	/*--Getter--*/
	Texture* GetTexture(TEXTURE_LIST tex) { return m_textureList[tex].get(); }

private:
	UITextureHolder();
	~UITextureHolder();
};