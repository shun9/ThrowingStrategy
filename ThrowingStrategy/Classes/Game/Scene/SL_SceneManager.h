//************************************************/
//* @file  :SL_SceneManager.h
//* @brief :シーンを管理するクラス
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
	//シーンを管理するクラス
	class SceneManager:public Singleton<SceneManager>
	{
		friend Singleton<SceneManager>;

	private:
		//シーン一覧
		std::unordered_map<int, IScene*>m_sceneList;

		//現在のシーン
		int m_currentScene;

	public:
		//現在のシーンの更新　描画
		void Update();
		void Render();

		//シーンの追加
		void AddScene(int key, IScene* scene);

		//シーンを切り替える
		void ChangeScene(int key);

		//シーンが存在するかどうか
		bool IsExistsScene(int key);

		//全てのシーンを削除
		void DeleteAllScene();

		/*--Getter & Setter--*/
		IScene* CurrentScene();
	private:
		SceneManager();
		~SceneManager();
	};
}