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
	ShunLib::Vec4 m_color;

public:
	Block();
	~Block();

	//�F�̐ݒ�
	void SetColor(const ShunLib::Vec4& color) { m_color = color; }

protected:
	//������ �X�V �`�� �I��
	void Initialize()override {};
	void Update    ()override {};
	void Render    ()override;
	void Finalize  ()override {};
};
