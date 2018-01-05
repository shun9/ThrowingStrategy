//************************************************/
//* @file  :MyGame.h
//* @brief :�Q�[���N���X
//* @date  :2018/01/01
//* @author:S.Katou
//************************************************/
#pragma once
#include "SL_Application.h"

#include <SL_ObjectHolder.h>
#include "../Object/ObjectConstantNumber.h"
#include "../../StepTimer.h"

class MyGame :public ShunLib::Application
{
public:
	enum SCENE{
		PLAY,
	};

public:
	MyGame() {
		ShunLib::ObjectHolder::GetInstance()->ResizeList(
			ObjectConstantNumber::OBJECT_LIST_END,
			100
		);
	}
	~MyGame() {}

protected:
	//�������@�X�V�@�`��@�I��
	void Initialize()override;
	void Update()override;
	void Render()override;
	void Finalize()override;
};
