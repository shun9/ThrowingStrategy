//************************************************/
//* @file  :PowerGauge.h
//* @brief :パワーゲージ
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
	//このオブジェクトのパワーを表示する
	ObjectBase * m_parent;

	//現在のパワー
	float m_power;

	//親からの位置
	Vec3 m_offset;

public:
	PowerGauge();
	~PowerGauge();

	//更新　描画
	void Update()override;
	void Render()override;

	/*--Getter--*/
	ObjectBase* Parent() { return m_parent; }
	Vec3 Offset() { return m_offset; }

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
