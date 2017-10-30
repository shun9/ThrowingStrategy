//************************************************/
//* @file  :PlayScene.h
//* @brief :プレイシーン
//* @date  :2017/10/26
//* @author:S.Katou
//************************************************/
#pragma once
#include "SL_IScene.h"
#include <vector>

class ObjectBase;

class PlayScene:public ShunLib::IScene
{
public:
	PlayScene();
	~PlayScene();

	//初期化　更新　描画　終了
	virtual void Initialize();
	virtual void Update();
	virtual void Render();
	virtual void Finalize();

private:
	std::vector<ObjectBase*>m_objList;
};