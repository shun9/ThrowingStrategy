//************************************************/
//* @file  :PlayScene.cpp
//* @brief :�v���C�V�[��
//* @date  :2017/10/26
//* @author:S.Katou
//************************************************/
#include "PlayScene.h"

#include <SL_Matrix.h>
#include <SL_MacroConstants.h>
#include "../../Main/SL_Window.h"
#include "../../Object/Player/Player.h"

PlayScene::PlayScene()
{
	m_objList.push_back(new Player);
}

PlayScene::~PlayScene()
{
	SAFE_DELETE_INSIDE(m_objList);
}

/// <summary>
/// ����������
/// </summary>
void PlayScene::Initialize()
{
	for (auto& v : m_objList)
	{
		v->Initialize();
	}
}

/// <summary>
/// �X�V����
/// </summary>
void PlayScene::Update()
{

}

/// <summary>
/// �`�揈��
/// </summary>
void PlayScene::Render()
{
	using namespace ShunLib;
	auto window = Window::GetInstance();
	Matrix view = Matrix::CreateLookAt(Vec3(0.0f, 10.0f, 15.0f), Vec3::Zero, Vec3::UnitY);
	Matrix proj = Matrix::CreateProj(45.0f, static_cast<float>(window->Width() / window->Height()), 1.0f, 200.0f);

	for (auto v : m_objList)
	{
		v->Render(view,proj);
	}
}

/// <summary>
/// �I������
/// </summary>
void PlayScene::Finalize()
{
	for (auto v : m_objList)
	{
		v->Finalize();
	}
}
