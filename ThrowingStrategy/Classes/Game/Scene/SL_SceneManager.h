//************************************************/
//* @file  :SL_SceneManager.h
//* @brief :�V�[�����Ǘ�����N���X
//* @date  :2017/10/26
//* @author:S.Katou
//************************************************/
#pragma once
#include <unordered_map>
#include <SL_Singleton.h>
#include "SL_IScene.h"
#include "FadeExecutor.h"
#include "../../../StepTimer.h"

namespace ShunLib
{
	//�V�[�����Ǘ�����N���X
	class SceneManager:public Singleton<SceneManager>
	{
		friend Singleton<SceneManager>;
	private:
		//�V�[���ꗗ
		std::unordered_map<int, IScene*>m_sceneList;

		//���݂̃V�[��
		int m_currentScene;

		//���̃V�[��
		int m_newScene;

		//�t�F�[�h���s�p
		FadeExecutor m_fade;

		//�t�F�[�h�����ǂ���
		bool m_isDuringFade;
	public:
		//���݂̃V�[���̍X�V�@�`��
		void Update();
		void Render();

		//�t�F�[�h�̕`��
		void FadeRender();

		//�V�[���̒ǉ�
		void AddScene(int key, IScene* scene);

		//�V�[����؂�ւ���
		void ChangeScene(int key);

		//�V�[�������݂��邩�ǂ���
		bool IsExistsScene(int key);

		//�S�ẴV�[�����폜
		void DeleteAllScene();

		/*--Getter & Setter--*/
		IScene* CurrentScene();
	private:
		SceneManager();
		~SceneManager();

		//�t�F�[�h���̍X�V�@�`��
		void FadeUpdate();
	};
}