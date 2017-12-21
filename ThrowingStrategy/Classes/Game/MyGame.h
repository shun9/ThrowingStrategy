//************************************************/
//* @file  :SL_MyGame.h
//* @brief :�Q�[���N���X
//* @date  :2017/10/26
//* @author:S.Katou
//************************************************/
#pragma once
#include "SL_Application.h"
#include "../../StepTimer.h"

class MyGame :public ShunLib::Application
{
public:
	enum SCENE{
		PLAY,
	};

public:
	MyGame() {}
	~MyGame() {}

protected:
	//�������@�X�V�@�`��@�I��
	void Initialize()override;
	void Update()override;
	void Render()override;
	void Finalize()override;
};
