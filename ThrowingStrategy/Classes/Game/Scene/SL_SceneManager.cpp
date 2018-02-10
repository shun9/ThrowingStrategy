//************************************************/
//* @file  :SL_SceneManager.cpp
//* @brief :�V�[�����Ǘ�����N���X
//* @date  :2017/10/26
//* @author:S.Katou
//************************************************/
#include "SL_SceneManager.h"
#include <SL_KeyManager.h>
#include <SL_MacroConstants.h>
#include "../../UI/UIManager.h"
#include "../../Util/SL_GamePadManager.h"

using namespace ShunLib;

/// <summary>
/// ���݂̃V�[�����X�V
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void SceneManager::Update()
{
	//�t�F�[�h���̓V�[���̍X�V�͂��Ȃ�
	if (m_isDuringFade){
		//�t�F�[�h���̍X�V
		FadeUpdate();
		return;
	}

	if (IsExistsScene(m_currentScene)){
		//�L�[�X�V
		KeyManager::GetInstance()->Update();

		//�Q�[���p�b�h�X�V
		GamePadManager::GetInstance()->Update();

		//�V�[��������ꍇ�X�V
		m_sceneList[m_currentScene]->BaseActiveUpdate();
		m_sceneList[m_currentScene]->BaseUpdate();
	}
}

/// <summary>
/// ���݂̃V�[����`��
/// </summary>
void SceneManager::Render()
{	//�V�[��������ꍇ�X�V
	if (IsExistsScene(m_currentScene))
	{
		m_sceneList[m_currentScene]->BaseActiveRender();
		m_sceneList[m_currentScene]->BaseRender();
	}
}

//�t�F�[�h�̕`��
void SceneManager::FadeRender()
{
	//�t�F�[�h���̕`��
	if (m_isDuringFade) {
		m_fade.Render();
	}
}

/// <summary>
/// �V�[���̒ǉ�
/// </summary>
/// <param name="key">�V�[���̔ԍ�</param>
/// <param name="scene">�V�[���̃|�C���^</param>
void SceneManager::AddScene(int key, IScene* scene)
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
void SceneManager::ChangeScene(int key)
{
	//���݂̃V�[�����I��
	if (IsExistsScene(m_currentScene)){
		m_sceneList[m_currentScene]->BaseFinalize();

		//�t�F�[�h����
		m_isDuringFade = true;

		//�t�F�[�h�����Z�b�g
		m_fade.Reset();

		//�V�����V�[�����X�V
		m_newScene = key;
	}
	else{
		m_currentScene = key;
		m_sceneList[m_currentScene]->BaseInitialize();
	}
}

/// <summary>
/// �V�[�������݂��邩�ǂ���
/// </summary>
/// <param name="key">�m�F����L�[</param>
/// <returns>���݂�����true</returns>
bool SceneManager::IsExistsScene(int key)
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
void SceneManager::DeleteAllScene()
{
	for (auto& v : m_sceneList)
	{
		//�V�[�������݂�����폜
		if (IsExistsScene(v.first))
		{
			//�I������
			v.second->BaseFinalize();
			//�폜
			SAFE_DELETE(v.second);
		}
	}
	m_sceneList.clear();
}

/// <summary>
/// ���݂̃V�[����Ԃ�
/// </summary>
/// <returns></returns>
IScene* SceneManager::CurrentScene()
{
	if (IsExistsScene(m_currentScene))
	{
		return m_sceneList[m_currentScene];
	}
	return nullptr;
}

/// <summary>
/// �R���X�g���N�^
/// </summary>
SceneManager::SceneManager() :
	m_currentScene(-1),
	m_newScene(-1),
	m_isDuringFade(false)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
SceneManager::~SceneManager()
{
	DeleteAllScene();
}

/// <summary>
/// �t�F�[�h���̍X�V
/// </summary>
void SceneManager::FadeUpdate()
{
	//�t�F�[�h�̍X�V
	m_fade.Update();

	//�t�F�[�h�A�E�g���I������^�C�~���O�ŃV�[���؂�ւ�
	if (m_fade.IsEndedFadeOut() && m_currentScene != m_newScene) {
		//�V�K�̃V�[����������
		if (IsExistsScene(m_newScene)) {
			m_currentScene = m_newScene;
			m_sceneList[m_currentScene]->BaseInitialize();
		}
	}

	//�t�F�[�h���I��
	if (m_fade.IsEnded()){
		m_isDuringFade = false;
	}
}