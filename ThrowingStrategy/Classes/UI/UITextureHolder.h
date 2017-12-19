//************************************************/
//* @file  :UITextureHolder.h
//* @brief :UI�֘A�̉摜���܂Ƃ߂ĕێ�����N���X
//* @date  :2017/12/13
//* @author:S.Katou
//************************************************/
#pragma once
#include <SL_Singleton.h>
#include <SL_Texture.h>

class UITextureHolder : public ShunLib::Singleton<UITextureHolder>
{
	friend ShunLib::Singleton<UITextureHolder>;
public:
	using Texture = ShunLib::Texture;

private:
	std::unique_ptr<Texture>m_redGauge;
	std::unique_ptr<Texture>m_greenGauge;

public:
	/*--Getter--*/
	Texture* RedGauge() { return m_redGauge.get(); }
	Texture* GreenGauge() { return m_greenGauge.get(); }

private:
	UITextureHolder();
	~UITextureHolder();
};