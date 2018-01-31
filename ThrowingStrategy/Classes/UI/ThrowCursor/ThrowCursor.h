//************************************************/
//* @file  :ThrowCursor.h
//* @brief :���e�n�_�̕\��
//* @date  :2018/01/31
//* @author:S.Katou
//************************************************/
#pragma once

#include "../UI.h"

class ThrowCursor:public UI
{
public:
	using Matrix = ShunLib::Matrix;

private:
	Matrix m_mat;

public:
	ThrowCursor();
	~ThrowCursor() {}

	//�X�V�@�`��
	virtual void Update();
	virtual void Render();
};