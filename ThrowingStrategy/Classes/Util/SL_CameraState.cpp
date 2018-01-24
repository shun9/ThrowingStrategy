//************************************************/
//* @file  :SL_CameraState.cpp
//* @brief :�`��p�J�����̏�Ԃ܂Ƃ�
//* @date  :2018/01/17
//* @author:S.Katou
//************************************************/
#include "SL_CameraState.h"

#include <SL_KeyManager.h>
#include <SL_Math.h>
#include "../Object/ObjectBase.h"

using namespace ShunLib;

/*--�Œ�J����--*/
void CameraNonMoveState::Enter(MainCamera* camera){}

void CameraNonMoveState::Execute(MainCamera* camera){}

void CameraNonMoveState::Exit(MainCamera* camera){}


/*--�ǐՃJ����--*/
//�ǐՃ^�[�Q�b�g�Ƃ̋����ƍ���
const float CameraFollowState::FOLLOW_DISTANSE = 20.0f;
const float CameraFollowState::FOLLOW_HEIGHT = 30.0f;

void CameraFollowState::Enter(MainCamera * camera){}

void CameraFollowState::Execute(MainCamera * camera){
	//�ǐՑΏۂ̏��
	Vec3 refPos = camera->FollowTarget()->Transform().Pos() + Vec3::UnitY;

	//�ǐՑΏۂ��王�_�ւ̍���
	Vec3 cameraV(0.0f, FOLLOW_HEIGHT, FOLLOW_DISTANSE);

	//���@�̌��ɉ�荞�ނ��߂̉�]
	Matrix rot = Matrix::CreateRotationY(camera->Angle());
	cameraV = Vec3::Rotation(cameraV, rot);
	Vec3 eyePos = refPos + cameraV;

	auto view = camera->View();
	view.pos = view.pos + (eyePos - view.pos)*0.01f;
	view.target = view.target + (refPos - view.target)*0.2f;
	camera->View(view);
}

void ShunLib::CameraFollowState::Exit(MainCamera * camera){}
