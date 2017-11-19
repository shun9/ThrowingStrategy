//************************************************/
//* @file  :SL_Camera.cpp
//* @brief :描画用カメラ
//* @date  :2017/11/09
//* @author:S.Katou
//************************************************/
#include "SL_Camera.h"
#include "SL_CameraState.h"

ShunLib::MainCamera::MainCamera() :
	m_angle(0.0f)
{
	m_stateMachine = std::make_unique<StateMachine<MainCamera>>(this);
	m_stateMachine->ChangeState(new CameraNonMoveState);

	CalcMat();
}

ShunLib::MainCamera::~MainCamera()
{

}

void ShunLib::MainCamera::Update()
{
	m_stateMachine->Update();
	CalcMat();
}

/// <summary>
/// カメラの状態を変更
/// </summary>
void ShunLib::MainCamera::ChangeMode(CAMERA_MODE mode)
{
	switch (mode)
	{
	case NON_MOVE_CAMERA:m_stateMachine->ChangeState(new CameraNonMoveState);	break;
	case FOLLOW_CAMERA:	m_stateMachine->ChangeState(new CameraFollowState); break;
	default:
		break;
	}
}

