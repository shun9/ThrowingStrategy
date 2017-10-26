//************************************************/
//* @file  :SL_SceneManager.cpp
//* @brief :シーンを管理するクラス
//* @date  :2017/10/26
//* @author:S.Katou
//************************************************/
#include "SL_SceneManager.h"
#include <SL_MacroConstants.h>

/// <summary>
/// 現在のシーンを更新
/// </summary>
/// <param name="timer">タイマー</param>
void ShunLib::SceneManager::Update(DX::StepTimer& timer)
{
	//シーンがある場合更新
	if (IsExistsScene(m_currentScene))
	{
		m_sceneList[m_currentScene]->Update(timer);
	}
}

/// <summary>
/// 現在のシーンを描画
/// </summary>
void ShunLib::SceneManager::Render()
{	//シーンがある場合更新
	if (IsExistsScene(m_currentScene))
	{
		m_sceneList[m_currentScene]->Render();
	}
}

/// <summary>
/// シーンの追加
/// </summary>
/// <param name="key">シーンの番号</param>
/// <param name="scene">シーンのポインタ</param>
void ShunLib::SceneManager::AddScene(int key, IScene * scene)
{
	//既にシーンがある場合消す
	if (IsExistsScene(key))
	{
		SAFE_DELETE(m_sceneList[key]);
	}

	m_sceneList[key] = scene;
}

/// <summary>
/// シーンを切り替える
/// </summary>
/// <param name="key">切替後のシーン</param>
void ShunLib::SceneManager::ChangeScene(int key)
{
	//現在のシーンを終了
	if (IsExistsScene(key)){
		m_sceneList[m_currentScene]->Finalize();
	}

	//現在のシーンを変更
	m_currentScene = key;

	//新規のシーンを初期化
	if (IsExistsScene(key)) {
		m_sceneList[m_currentScene]->Initialize();
	}
}

/// <summary>
/// シーンが存在するかどうか
/// </summary>
/// <param name="key">確認するキー</param>
/// <returns>存在したらtrue</returns>
bool ShunLib::SceneManager::IsExistsScene(int key)
{
	//登録されているかどうか
	if (m_sceneList.find(key) == m_sceneList.end())
	{
		return false;
	}

	//存在するかどうか
	if (m_sceneList[key] == nullptr)
	{
		return false;
	}

	return true;
}

/// <summary>
/// 全てのシーンを削除
/// </summary>
void ShunLib::SceneManager::DeleteAllScene()
{
	for (auto& v : m_sceneList)
	{
		//シーンが存在したら削除
		if (IsExistsScene(v.first))
		{
			//終了処理
			v.second->Finalize();
			//削除
			SAFE_DELETE(v.second);
		}
	}
	m_sceneList.clear();
}

/// <summary>
/// コンストラクタ
/// </summary>
ShunLib::SceneManager::SceneManager() :
	m_currentScene(-1)
{
}

/// <summary>
/// デストラクタ
/// </summary>
ShunLib::SceneManager::~SceneManager()
{
	DeleteAllScene();
}
