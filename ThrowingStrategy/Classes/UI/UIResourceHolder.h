//************************************************/
//* @file  :UIResourceHolder.h
//* @brief :UI�֘A�̉摜,���f�����܂Ƃ߂ĕێ�����N���X
//* @date  :2018/01/31
//* @author:S.Katou
//************************************************/
#pragma once
#include <vector>
#include <memory>
#include <SL_Singleton.h>
#include <SL_Texture.h>
#include <SL_Model.h>

//UI�̃e�N�X�`���̎�ވꗗ
enum UI_TEXTURE_LIST {
	OPTION_BOARD,
	OPTION_CURSOR,
	RED_GAUGE,
	GREEN_GAUGE,
	ORANGE_GAUGE,

	UI_TEXTURE_LIST_END
};

//UI�̕����摜�̎�ވꗗ
enum UI_STRING_LIST {
	UI_STRING_NONE = -1,
	STRING_START,//�͂��߂�
	STRING_END,  //�����
	UI_STRING_LIST_END
};

//UI�̃��f���̎�ވꗗ
enum UI_MODEL_LIST {
	THROW_CURSOR,
	UI_MODEL_LIST_END
};

class UIResourceHolder : public ShunLib::Singleton<UIResourceHolder>
{
	friend ShunLib::Singleton<UIResourceHolder>;
public:
	using Texture = ShunLib::Texture;
	using Model = ShunLib::Model;

private:
	//UI�摜
	std::vector<std::unique_ptr<Texture>>m_textureList;

	//�����摜
	std::vector<std::unique_ptr<Texture>>m_strTexture;

	//UI���f��
	std::vector<std::unique_ptr<Model>>m_modelList;

public:
	/*--Getter--*/
	Texture* GetTexture(UI_TEXTURE_LIST tex) { return m_textureList[tex].get(); }
	Texture* GetStrTexture(UI_STRING_LIST tex) { return m_strTexture[tex].get(); }
	Model* GetModel(UI_MODEL_LIST mod) { return m_modelList[mod].get(); }

private:
	UIResourceHolder();
	~UIResourceHolder();
};