//************************************************/
//* @file  :TitleScene.cpp
//* @brief :�^�C�g���V�[��
//* @date  :2018/01/24
//* @author:S.Katou
//************************************************/
#include "TitleScene.h"
#include <SL_KeyManager.h>
#include "SL_SceneManager.h"
#include "../MyGame.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
TitleScene::TitleScene()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
TitleScene::~TitleScene()
{
}

/// <summary>
/// ������
/// </summary>
void TitleScene::Initialize()
{

}

/// <summary>
/// �X�V
/// </summary>
void TitleScene::Update()
{
	//���݂͉��������v���C�V�[���ֈڍs
	ShunLib::SceneManager::GetInstance()->ChangeScene(MyGame::SCENE::PLAY);
}

/// <summary>
/// �`��
/// </summary>
void TitleScene::Render()
{
}

/// <summary>
/// �I��
/// </summary>
void TitleScene::Finalize()
{
}
