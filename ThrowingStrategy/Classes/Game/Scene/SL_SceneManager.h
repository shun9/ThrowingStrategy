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

	public:
		//���݂̃V�[���̍X�V�@�`��
		void Update();
		void Render();

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
	};
}