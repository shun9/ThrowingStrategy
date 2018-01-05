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

protected:
	//描画位置
	Vec3 m_pos;

	//回転角度
	Vec3 m_rot;

	//拡大率
	Vec3 m_scale;

	//使用しているかどうか
	bool m_isEnable;

public:
	//コンストラクタ
	UI();

	//デストラクタ
	~UI();

	//更新　描画
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