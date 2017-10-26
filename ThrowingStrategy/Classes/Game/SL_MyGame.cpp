//************************************************/
//* @file  :SL_MyGame.cpp
//* @brief :�Q�[���N���X
//* @date  :2017/10/26
//* @author:S.Katou
//************************************************/
#include "SL_MyGame.h"
#include "Scene\SL_SceneManager.h"

/// <summary>
/// ����������
/// </summary>
void ShunLib::MyGame::Initialize()
{
	auto scene = ShunLib::SceneManager::GetInstance();

}

/// <summary>
/// �X�V����
/// </summary>
void ShunLib::MyGame::Update()
{
	auto scene = ShunLib::SceneManager::GetInstance();

	m_timer.Tick([&]()
	{
		scene->Update(m_timer);
	});
}

/// <summary>
/// �`�揈��
/// </summary>
void ShunLib::MyGame::Render()
{
	auto scene = ShunLib::SceneManager::GetInstance();
	scene->Render();

}

/// <summary>
/// �I������
/// </summary>
void ShunLib::MyGame::Finalize()
{
	ShunLib::SceneManager::Destroy();
}
