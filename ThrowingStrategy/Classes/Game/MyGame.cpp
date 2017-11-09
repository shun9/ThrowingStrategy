//************************************************/
//* @file  :SL_MyGame.cpp
//* @brief :�Q�[���N���X
//* @date  :2017/11/09
//* @author:S.Katou
//************************************************/
#include "MyGame.h"

#include <SL_Model.h>
#include <SL_Texture.h>
#include <SL_KeyManager.h>

#include "../Main/SL_Graphics.h"
#include "../Main/SL_MyStepTimer.h"
#include "Scene\SL_SceneManager.h"
#include "Scene\PlayScene.h"
#include "../Physics/Collision/SL_CollisionManager.h"

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
	
	//�L�[�X�V
	auto key = ShunLib::KeyManager::GetInstance();
	key->Update();

	//�V�[���X�V
	timer->Tick([&]()
	{
		scene->Update();
		ShunLib::CollisionManager::GetInstance()->Update();
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
	ShunLib::CollisionManager::Destroy();
	ShunLib::SceneManager::Destroy();
}
