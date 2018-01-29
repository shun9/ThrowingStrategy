//************************************************/
//* @file  :PowerGauge.h
//* @brief :�p���[�Q�[�W
//* @date  :2018/01/29
//* @author:S.Katou
//************************************************/
#pragma once
#include "../UI.h"

#include <SL_Texture.h>
#include "../../Object/ObjectBase.h"

class PowerGauge : public UI
{
public:
	using Matrix = ShunLib::Matrix;

private:
	//���̃I�u�W�F�N�g�̃p���[��\������
	ObjectBase * m_parent;

	//���݂̃p���[
	float m_power;

	//�e����̈ʒu
	Vec3 m_offset;

public:
	PowerGauge();
	~PowerGauge();

	//�X�V�@�`��
	void Update()override;
	void Render()override;

	/*--Getter--*/
	ObjectBase* Parent() { return m_parent; }
	Vec3 Offset() { return m_offset; }

	/*--Setter--*/
	void Offset(const Vec3& off) { m_offset = off; }
	void Parent(ObjectBase* par) { m_parent = par; }

private:
	//�s��̌v�Z
	Matrix CalcRedMat();
	Matrix CalcGreenMat();

	//��]���v�Z
	void CalcRot();
};
