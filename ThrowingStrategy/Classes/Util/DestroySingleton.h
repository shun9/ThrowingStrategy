//************************************************/
//* @file  :DestroySingleton.h
//* @brief :シングルトンをまとめて削除する
//* @date  :2017/12/13
//* @author:S.Katou
//************************************************/
#pragma once
#include <SL_KeyManager.h>
#include "SL_Camera.h"
#include "../Physics/Collision/SL_CollisionManager.h"
#include "../Main/SL_MyStepTimer.h"
#include "../Game/Scene/SL_SceneManager.h"
#include "BasicShapeModelRenderer.h"
#include "../Main/SL_Graphics.h"
#include "../Main/SL_Window.h"
#include "../Object/ObjectFactory.h"
#include "../Object/ObjectParamHolder.h"
#include "SL_GamePadManager.h"
#include "Debugger\DebuggerUI.h"
#include "../Object/ObjectModelHolder.h"
#include "../UI/UIManager.h"

class DestroySingleton
{
public:
	static void Destroy(){
		using namespace ShunLib;
		ObjectParamHolder::Destroy();
		ObjectFactory::Destroy();
		ObjectModelHolder::Destroy();
		BasicShapeRenderer::Destroy();
		MainCamera::Destroy();
		CollisionManager::Destroy();
		UIManager::Destroy();
		SceneManager::Destroy();
		MyStepTimer::Destroy();
		GamePadManager::Destroy();
		KeyManager::Destroy();
		DebuggerUI::Destroy();
		Graphics::Destroy();
		Window::Destroy();
	}
};