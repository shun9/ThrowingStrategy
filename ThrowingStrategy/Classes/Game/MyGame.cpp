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
#include "../Physics/Collision/SL_CollisionManager.h"
#include "../Util/SL_GamePadManager.h"
#include "Scene\SL_SceneManager.h"
#include "Scene\PlayScene.h"
#include "../Util/Debugger/DebuggerUI.h"
#include "../Object/ObjectBase.h"

using namespace ShunLib;

/// <summary>
/// ����������
/// </summary>
void MyGame::Initialize()
{
	//���[�g�I�u�W�F�N�g�̐ݒ�
	ObjectBase::InitializeRootObject();
	
	//�O���t�B�b�N�֘A
	auto graphics = Graphics::GetInstance();
	Model::SetDevice(graphics->Device(), graphics->DeviceContext());
	Texture::SetDevice(graphics->Device(), graphics->DeviceContext());

	//�V�[���֘A
	auto scene = SceneManager::GetInstance();
	scene->AddScene(SCENE::PLAY, new PlayScene);
	scene->ChangeScene(SCENE::PLAY);

}

/// <summary>
/// �X�V����
/// </summary>
void MyGame::Update()
{
	auto scene = SceneManager::GetInstance();
	auto timer = MyStepTimer::GetInstance();
	
	//�L�[�X�V
	KeyManager::GetInstance()->Update();

	//�Q�[���p�b�h�X�V
	GamePadManager::GetInstance()->Update();

	//�V�[���X�V
	timer->Tick([&]()
	{
		scene->Update();
		CollisionManager::GetInstance()->Update();
	});
}

/// <summary>
/// �`�揈��
/// </summary>
void MyGame::Render()
{
	auto scene = ShunLib::SceneManager::GetInstance();
	scene->Render();
	CollisionManager::GetInstance()->Render();

	DebuggerUI::GetInstance()->Render();
}

/// <summary>
/// �I������
/// </summary>
void MyGame::Finalize()
{
	auto scene = SceneManager::GetInstance();
	scene->DeleteAllScene();
	ObjectBase::FinalizeRootObject();
}
