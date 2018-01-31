//************************************************/
//* @file  :ThrowCursor.h
//* @brief :着弾地点の表示
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

	//更新　描画
	virtual void Update();
	virtual void Render();
};