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

protected:
	//�`��ʒu
	Vec3 m_pos;

	//��]�p�x
	Vec3 m_rot;

	//�g�嗦
	Vec3 m_scale;

	//�g�p���Ă��邩�ǂ���
	bool m_isEnable;

public:
	//�R���X�g���N�^
	UI();

	//�f�X�g���N�^
	~UI();

	//�X�V�@�`��
	virtual void Update() = 0;
	virtual void Render() = 0;

	/*--Getter--*/
	Vec3 Pos     () { return m_pos; }
	Vec3 Rot     () { return m_rot; }
	Vec3 Scale   () { return m_scale; }
	bool IsEnable() { return m_isEnable; }

	/*--Setter--*/
	void Pos     (const Vec3& pos)   { m_pos = pos; }
	void Rot     (const Vec3& rot)   { m_rot = rot; }
	void Scale   (const Vec3& scale) { m_scale = scale; }
	void IsEnable(bool isEnable)     { m_isEnable = isEnable; }
};