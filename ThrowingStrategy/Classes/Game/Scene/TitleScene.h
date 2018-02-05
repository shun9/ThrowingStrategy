//************************************************/
//* @file  :TitleScene.h
//* @brief :�^�C�g���V�[��
//* @date  :2018/01/24
//* @author:S.Katou
//************************************************/
#pragma once
#include "SL_IScene.h"
#include "../../UI/OptionBoard.h"

class TitleScene :public ShunLib::IScene
{
public:
	//�^�C�g����ʂł̑I����
	enum TITLE_OPTION {
		TITLE_START = 0,
		TITLE_END,
		TITLE_OPTION_END
	};

private:
	//�I����
	OptionBoard m_optionBoard;

public:
	TitleScene();
	~TitleScene();

	//�������@�X�V�@�`��@�I��
	virtual void Initialize();
	virtual void Update();
	virtual void Render();
	virtual void Finalize();
};