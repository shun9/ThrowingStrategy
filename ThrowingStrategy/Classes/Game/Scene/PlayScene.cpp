//************************************************/
//* @file  :PlayScene.cpp
//* @brief :�v���C�V�[��
//* @date  :2017/11/02
//* @author:S.Katou
//************************************************/
#include "PlayScene.h"
#include <SL_KeyManager.h>
#include "SL_SceneManager.h"
#include "../MyGame.h"
#include "../../Main/SL_Window.h"
#include "../../Util/SL_Camera.h"
#include "../../Object/Stage/Stage.h"
#include "../../Object/ObjectFactory.h"
#include "../../Object/ObjectConstantNumber.h"

using namespace ShunLib;

/// <summary>
/// �R���X�g���N�^
/// </summary>
PlayScene::PlayScene(){
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlayScene::~PlayScene()
{

}

/// <summary>
/// ����������
/// </summary>
void PlayScene::Initialize()
{
	//�I�u�W�F�N�g����
	auto factory = ObjectFactory::GetInstance();

	auto stage = factory->CreateStage(ObjectConstantNumber::STAGE_LIST::STANDARD);
	this->AddChild(stage);
}

/// <summary>
/// �X�V����
/// </summary>
void PlayScene::Update()
{
	//Enter�L�[�ŉ����Z�b�g����
	auto key = KeyManager::GetInstance();
	if (key->IsTracker(KeyManager::KEY_CODE::ENTER)) {
		SceneManager::GetInstance()->ChangeScene(MyGame::SCENE::TITLE);
	}
}

/// <summary>
/// �`�揈��
/// </summary>
void PlayScene::Render()
{
}

/// <summary>
/// �I������
/// </summary>
void PlayScene::Finalize()
{
	//�X�e�[�W������
	//�X�e�[�W�͏��1�ɂ���
	for (auto& child:m_children){
		SAFE_DELETE(child);
	}
	m_children.clear();
}
