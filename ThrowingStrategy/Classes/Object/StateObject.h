//************************************************/
//* @file  :StateObject.h
//* @brief :状態を持つオブジェクト
//* @date  :2017/10/30
//* @author:S.Katou
//************************************************/
#pragma once
#include "ObjectBase.h"

#include <memory>
#include <SL_StateMachine.h>
#include <SL_Math.h>

template<class T>
class StateObject : public ObjectBase
{
private:
	std::unique_ptr<ShunLib::StateMachine<T>> m_stateMachine;

public:
	//コンストラクタ　状態を使用するオブジェクトを渡す
	StateObject(T* obj,OBJECT_LIST type):
		ObjectBase(type) {
		m_stateMachine = std::make_unique<ShunLib::StateMachine<T>>(obj);
	}

	virtual ~StateObject() {}

	//更新
	virtual void Update()override {
		//ステートマシンがあれば更新
		if (m_stateMachine){
			m_stateMachine->Update();
		}
		ObjectBase::Update();
	}

	//状態切替
	void ChangeState(ShunLib::State<T>* state) { m_stateMachine->ChangeState(state); }

	//初期化　終了
	virtual void Initialize() {
		ObjectBase::Initialize();
	};
	virtual void Finalize() {
		ObjectBase::Finalize();
	};
};

