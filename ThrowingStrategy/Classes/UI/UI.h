//************************************************/
//* @file  :UI.h
//* @brief :UI�̊��N���X
//* @date  :2017/12/13
//* @author:S.Katou
//************************************************/
#pragma once
#include <SL_Math.h>

class UI
{
public:
	using Vec3 = ShunLib::Vec3;

private:
	//�`��ʒu
	Vec3 m_pos;

	//��]�p�x
	Vec3 m_rot;

	//�g�嗦
	Vec3 m_scale;

public:
	//�R���X�g���N�^
	UI():
	m_pos(Vec3::Zero),
	m_rot(Vec3::Zero),
	m_scale(Vec3::One){}

	//�f�X�g���N�^
	~UI() {}

	//�X�V�@�`��
	virtual void Update() = 0;
	virtual void Render() = 0;

	/*--Getter--*/
	Vec3 Pos(){ return m_pos; }
	Vec3 Rot(){ return m_rot; }

	/*--Setter--*/
	void Pos(const Vec3& pos){ m_pos = pos; }
	void Rot(const Vec3& rot){ m_rot = rot; }
};