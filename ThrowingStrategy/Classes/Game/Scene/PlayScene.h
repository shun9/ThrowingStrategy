//************************************************/
//* @file  :PlayScene.h
//* @brief :�v���C�V�[��
//* @date  :2017/10/26
//* @author:S.Katou
//************************************************/
#pragma once

#include "SL_IScene.h"

class PlayScene:public ShunLib::IScene
{
public:
	PlayScene() {}
	~PlayScene() {}

	//�������@�X�V�@�`��@�I��
	virtual void Initialize();
	virtual void Update(DX::StepTimer& timer);
	virtual void Render();
	virtual void Finalize();

private:

};