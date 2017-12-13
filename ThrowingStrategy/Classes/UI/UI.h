//************************************************/
//* @file  :UI.h
//* @brief :UIの基底クラス
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
	//描画位置
	Vec3 m_pos;

	//回転角度
	Vec3 m_rot;

	//拡大率
	Vec3 m_scale;

public:
	//コンストラクタ
	UI():
	m_pos(Vec3::Zero),
	m_rot(Vec3::Zero),
	m_scale(Vec3::One){}

	//デストラクタ
	~UI() {}

	//更新　描画
	virtual void Update() = 0;
	virtual void Render() = 0;

	/*--Getter--*/
	Vec3 Pos(){ return m_pos; }
	Vec3 Rot(){ return m_rot; }

	/*--Setter--*/
	void Pos(const Vec3& pos){ m_pos = pos; }
	void Rot(const Vec3& rot){ m_rot = rot; }
};