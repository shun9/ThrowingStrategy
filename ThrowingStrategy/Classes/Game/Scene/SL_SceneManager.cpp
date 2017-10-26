//************************************************/
//* @file  :SL_SceneManager.cpp
//* @brief :�V�[�����Ǘ�����N���X
//* @date  :2017/10/26
//* @author:S.Katou
//************************************************/
#include "SL_SceneManager.h"
#include <SL_MacroConstants.h>

/// <summary>
/// ���݂̃V�[�����X�V
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void ShunLib::SceneManager::Update(DX::StepTimer& timer)
{
	//�V�[��������ꍇ�X�V
	if (IsExistsScene(m_currentScene))
	{
		m_sceneList[m_currentScene]->Update(timer);
	}
}

/// <summary>
/// ���݂̃V�[����`��
/// </summary>
void ShunLib::SceneManager::Render()
{	//�V�[��������ꍇ�X�V
	if (IsExistsScene(m_currentScene))
	{
		m_sceneList[m_currentScene]->Render();
	}
}

/// <summary>
/// �V�[���̒ǉ�
/// </summary>
/// <param name="key">�V�[���̔ԍ�</param>
/// <param name="scene">�V�[���̃|�C���^</param>
void ShunLib::SceneManager::AddScene(int key, IScene * scene)
{
	//���ɃV�[��������ꍇ����
	if (IsExistsScene(key))
	{
		SAFE_DELETE(m_sceneList[key]);
	}

	m_sceneList[key] = scene;
}

/// <summary>
/// �V�[����؂�ւ���
/// </summary>
/// <param name="key">�ؑ֌�̃V�[��</param>
void ShunLib::SceneManager::ChangeScene(int key)
{
	//���݂̃V�[�����I��
	if (IsExistsScene(key)){
		m_sceneList[m_currentScene]->Finalize();
	}

	//���݂̃V�[����ύX
	m_currentScene = key;

	//�V�K�̃V�[����������
	if (IsExistsScene(key)) {
		m_sceneList[m_currentScene]->Initialize();
	}
}

/// <summary>
/// �V�[�������݂��邩�ǂ���
/// </summary>
/// <param name="key">�m�F����L�[</param>
/// <returns>���݂�����true</returns>
bool ShunLib::SceneManager::IsExistsScene(int key)
{
	//�o�^����Ă��邩�ǂ���
	if (m_sceneList.find(key) == m_sceneList.end())
	{
		return false;
	}

	//���݂��邩�ǂ���
	if (m_sceneList[key] == nullptr)
	{
		return false;
	}

	return true;
}

/// <summary>
/// �S�ẴV�[�����폜
/// </summary>
void ShunLib::SceneManager::DeleteAllScene()
{
	for (auto& v : m_sceneList)
	{
		//�V�[�������݂�����폜
		if (IsExistsScene(v.first))
		{
			//�I������
			v.second->Finalize();
			//�폜
			SAFE_DELETE(v.second);
		}
	}
	m_sceneList.clear();
}

/// <summary>
/// �R���X�g���N�^
/// </summary>
ShunLib::SceneManager::SceneManager() :
	m_currentScene(-1)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ShunLib::SceneManager::~SceneManager()
{
	DeleteAllScene();
}
