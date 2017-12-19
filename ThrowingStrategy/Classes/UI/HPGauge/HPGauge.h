//************************************************/
//* @file  :HPGauge.h
//* @brief :HPゲージ
//* @date  :2017/12/13
//* @author:S.Katou
//************************************************/
#pragma once
#include "../UI.h"

#include <SL_Texture.h>
#include "../../Object/ObjectBase.h"

class HPGauge : public UI
{
public:
	using Matrix = ShunLib::Matrix;

private:
	//このオブジェクトのHPを表示する
	ObjectBase * m_parent;

	//親からの位置
	Vec3 m_offset;

public:
	HPGauge();
	~HPGauge();

	//更新　描画
	void Update()override;
	void Render()override;

	/*--Getter--*/
	ObjectBase* Parent() { return m_parent; }
	Vec3 Offset()		 { return m_offset; }

	/*--Setter--*/
	void Offset(const Vec3& off) { m_offset = off; }
	void Parent(ObjectBase* par) { m_parent = par; }

private:
	//行列の計算
	Matrix CalcRedMat();
	Matrix CalcGreenMat();

	//回転を計算
	void CalcRot();
};
