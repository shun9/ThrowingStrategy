//************************************************/
//* @file  :ObjectBase.h
//* @brief :�I�u�W�F�N�g
//* @date  :2017/10/30
//* @author:S.Katou
//************************************************/
#pragma once
#include <memory>
#include <SL_Math.h>
#include <SL_Model.h>
#include "ObjectConstantNumber.h"

class ObjectBase
{
private:
	using Vec3 = ShunLib::Vec3;
	using Matrix = ShunLib::Matrix;

protected:
	//�ʒu
	Vec3 m_pos;

	//��]�p�x
	Vec3 m_rotation;

	//�g�嗦
	float m_scale;

	//�`��p���f��
	std::unique_ptr<ShunLib::Model> m_model;

	//�`�[������
	TEAM m_team;

public:
	ObjectBase() :m_pos({ 0.0f,0.0f,0.0f }), m_rotation({ 0.0f,0.0f,0.0f }), m_scale(1.0f) {}
	virtual ~ObjectBase() {}

	//�`��
	void Render(const Matrix& view, const Matrix& proj);

	//���f���̓ǂݍ���
	void LoadModel(const wchar_t* path) { m_model = std::make_unique<ShunLib::Model>(path); }

	//�������@�X�V�@�I��
	virtual void Initialize() = 0;
	virtual void Update()     = 0;
	virtual void Finalize()   = 0;
};