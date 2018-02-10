//************************************************/
//* @file  :SL_SceneManager.cpp
//* @brief :シーンを管理するクラス
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
/// 現在のシーンを更新
/// </summary>
/// <param name="timer">タイマー</param>
void SceneManager::Update()
{
	//フェード中はシーンの更新はしない
	if (m_isDuringFade){
		//フェード中の更新
		FadeUpdate();
		return;
	}

	if (IsExistsScene(m_currentScene)){
		//キー更新
		KeyManager::GetInstance()->Update();

		//ゲームパッド更新
		GamePadManager::GetInstance()->Update();

		//シーンがある場合更新
		m_sceneList[m_currentScene]->BaseActiveUpdate();
		m_sceneList[m_currentScene]->BaseUpdate();
	}
}

/// <summary>
/// 現在のシーンを描画
/// </summary>
void SceneManager::Render()
{	//シーンがある場合更新
	if (IsExistsScene(m_currentScene))
	{
		m_sceneList[m_currentScene]->BaseActiveRender();
		m_sceneList[m_currentScene]->BaseRender();
	}
}

//フェードの描画
void SceneManager::FadeRender()
{
	//フェード中の描画
	if (m_isDuringFade) {
		m_fade.Render();
	}
}

/// <summary>
/// シーンの追加
/// </summary>
/// <param name="key">シーンの番号</param>
/// <param name="scene">シーンのポインタ</param>
void SceneManager::AddScene(int key, IScene* scene)
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
void SceneManager::ChangeScene(int key)
{
	//現在のシーンを終了
	if (IsExistsScene(m_currentScene)){
		m_sceneList[m_currentScene]->BaseFinalize();

		//フェードする
		m_isDuringFade = true;

		//フェードをリセット
		m_fade.Reset();

		//新しいシーンを更新
		m_newScene = key;
	}
	else{
		m_currentScene = key;
		m_sceneList[m_currentScene]->BaseInitialize();
	}
}

/// <summary>
/// シーンが存在するかどうか
/// </summary>
/// <param name="key">確認するキー</param>
/// <returns>存在したらtrue</returns>
bool SceneManager::IsExistsScene(int key)
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
void SceneManager::DeleteAllScene()
{
	for (auto& v : m_sceneList)
	{
		//シーンが存在したら削除
		if (IsExistsScene(v.first))
		{
			//終了処理
			v.second->BaseFinalize();
			//削除
			SAFE_DELETE(v.second);
		}
	}
	m_sceneList.clear();
}

/// <summary>
/// 現在のシーンを返す
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
/// コンストラクタ
/// </summary>
SceneManager::SceneManager() :
	m_currentScene(-1),
	m_newScene(-1),
	m_isDuringFade(false)
{
}

/// <summary>
/// デストラクタ
/// </summary>
SceneManager::~SceneManager()
{
	DeleteAllScene();
}

/// <summary>
/// フェード中の更新
/// </summary>
void SceneManager::FadeUpdate()
{
	//フェードの更新
	m_fade.Update();

	//フェードアウトが終わったタイミングでシーン切り替え
	if (m_fade.IsEndedFadeOut() && m_currentScene != m_newScene) {
		//新規のシーンを初期化
		if (IsExistsScene(m_newScene)) {
			m_currentScene = m_newScene;
			m_sceneList[m_currentScene]->BaseInitialize();
		}
	}

	//フェードが終了
	if (m_fade.IsEnded()){
		m_isDuringFade = false;
	}
}