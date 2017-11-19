//************************************************/
//* @file  :PlayScene.h
//* @brief :�v���C�V�[��
//* @date  :2017/10/26
//* @author:S.Katou
//************************************************/
#pragma once
#include "SL_IScene.h"
#include <vector>

#include "../../Object/Stage/Stage.h"

class ObjectBase;

class PlayScene:public ShunLib::IScene
{
public:
	PlayScene();
	~PlayScene();

	//�������@�X�V�@�`��@�I��
	virtual void Initialize();
	virtual void Update();
	virtual void Render();
	virtual void Finalize();
};