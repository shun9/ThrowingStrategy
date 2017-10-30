//************************************************/
//* @file  :SL_MyGame.cpp
//* @brief :�Q�[���N���X
//* @date  :2017/10/26
//* @author:S.Katou
//************************************************/
#include "MyGame.h"

#include <SL_Model.h>
#include <SL_Texture.h>
#include "Scene\SL_SceneManager.h"
#include "../Main/SL_Graphics.h"
#include "Scene\PlayScene.h"
#include "../Main/SL_MyStepTimer.h"

/// <summary>
/// ����������
/// </summary>
void MyGame::Initialize()
{
	//�O���t�B�b�N�֘A
	auto graphics = ShunLib::Graphics::GetInstance();
	ShunLib::Model::SetDevice(graphics->Device(), graphics->DeviceContext());
	ShunLib::Texture::SetDevice(graphics->Device(), graphics->DeviceContext());

	//�V�[���֘A
	auto scene = ShunLib::SceneManager::GetInstance();
	scene->AddScene(SCENE::PLAY, new PlayScene);
	scene->ChangeScene(SCENE::PLAY);
}

/// <summary>
/// �X�V����
/// </summary>
void MyGame::Update()
{
	auto scene = ShunLib::SceneManager::GetInstance();
	auto timer = ShunLib::MyStepTimer::GetInstance();

	timer->Tick([&]()
	{
		scene->Update();
	});
}

/// <summary>
/// �`�揈��
/// </summary>
void MyGame::Render()
{
	auto scene = ShunLib::SceneManager::GetInstance();
	scene->Render();
}

/// <summary>
/// �I������
/// </summary>
void MyGame::Finalize()
{
	ShunLib::SceneManager::Destroy();
}
