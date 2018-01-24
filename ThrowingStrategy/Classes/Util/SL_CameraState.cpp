//************************************************/
//* @file  :SL_CameraState.cpp
//* @brief :描画用カメラの状態まとめ
//* @date  :2018/01/17
//* @author:S.Katou
//************************************************/
#include "SL_CameraState.h"

#include <SL_KeyManager.h>
#include <SL_Math.h>
#include "../Object/ObjectBase.h"

using namespace ShunLib;

/*--固定カメラ--*/
void CameraNonMoveState::Enter(MainCamera* camera){}

void CameraNonMoveState::Execute(MainCamera* camera){}

void CameraNonMoveState::Exit(MainCamera* camera){}


/*--追跡カメラ--*/
//追跡ターゲットとの距離と高さ
const float CameraFollowState::FOLLOW_DISTANSE = 20.0f;
const float CameraFollowState::FOLLOW_HEIGHT = 30.0f;

void CameraFollowState::Enter(MainCamera * camera){}

void CameraFollowState::Execute(MainCamera * camera){
	//追跡対象の上方
	Vec3 refPos = camera->FollowTarget()->Transform().Pos() + Vec3::UnitY;

	//追跡対象から視点への差分
	Vec3 cameraV(0.0f, FOLLOW_HEIGHT, FOLLOW_DISTANSE);

	//自機の後ろに回り込むための回転
	Matrix rot = Matrix::CreateRotationY(camera->Angle());
	cameraV = Vec3::Rotation(cameraV, rot);
	Vec3 eyePos = refPos + cameraV;

	auto view = camera->View();
	view.pos = view.pos + (eyePos - view.pos)*0.01f;
	view.target = view.target + (refPos - view.target)*0.2f;
	camera->View(view);
}

void ShunLib::CameraFollowState::Exit(MainCamera * camera){}
