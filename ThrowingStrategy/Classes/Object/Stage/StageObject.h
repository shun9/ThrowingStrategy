//************************************************/
//* @file  :StageObject.h
//* @brief :�X�e�[�W�ɔz�u����I�u�W�F�N�g�̂܂Ƃ�
//* @date  :2017/11/16
//* @author:S.Katou
//************************************************/
#pragma once
#include "../ObjectBase.h"
#include "../../Physics/Collision/SL_Collider.h"

//��
class Block : public ObjectBase
{
private:
	ShunLib::BoxCollider* m_collider;

public:
	Block();
	~Block();
};
