//************************************************/
//* @file  :TitleScene.h
//* @brief :�^�C�g���V�[��
//* @date  :2018/01/24
//* @author:S.Katou
//************************************************/
#pragma once
#include "SL_IScene.h"

class TitleScene :public ShunLib::IScene
{
public:
	TitleScene();
	~TitleScene();

	//�������@�X�V�@�`��@�I��
	virtual void Initialize();
	virtual void Update();
	virtual void Render();
	virtual void Finalize();
};