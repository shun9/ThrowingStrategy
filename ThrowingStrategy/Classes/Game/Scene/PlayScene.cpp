//************************************************/
//* @file  :PlayScene.cpp
//* @brief :�v���C�V�[��
//* @date  :2017/11/02
//* @author:S.Katou
//************************************************/
#include "PlayScene.h"

#include <SL_Matrix.h>
#include <SL_MacroConstants.h>
#include "../../Main/SL_Window.h"
#include "../../Util/SL_Camera.h"

//�I�u�W�F�N�g�֘A
#include "../../Object/ObjectBase.h"
#include "../../Object/ObjectFactory.h"
#include "../../Object/ObjectConstantNumber.h"

PlayScene::PlayScene()
{
	auto window = ShunLib::Window::GetInstance();

	//�J�����ݒ�
	auto camera = ShunLib::MainCamera::GetInstance();

	ViewData vData;
	vData.pos = ShunLib::Vec3(0.0f, 10.0f, 15.0f);
	vData.target = ShunLib::Vec3::Zero;

	ProjData pData;
	pData.aspect = static_cast<float>(window->Width() / window->Height());
	camera->View(vData);
	camera->Proj(pData);

	//�I�u�W�F�N�g����
	auto factory = ObjectFactory::GetInstance();

	auto s = factory->CreateStage(ObjectConstantNumber::STAGE_LIST::GROUND);
}

PlayScene::~PlayScene()
{

}

/// <summary>
/// ����������
/// </summary>
void PlayScene::Initialize()
{

}

/// <summary>
/// �X�V����
/// </summary>
void PlayScene::Update()
{
	auto camera = ShunLib::MainCamera::GetInstance();
	camera->Update();
}

/// <summary>
/// �`�揈��
/// </summary>
void PlayScene::Render()
{
	auto camera = ShunLib::MainCamera::GetInstance();
}

/// <summary>
/// �I������
/// </summary>
void PlayScene::Finalize()
{
}
