//************************************************/
//* @file  :ObjectBase.h
//* @brief :オブジェクト
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
	//位置
	Vec3 m_pos;

	//回転角度
	Vec3 m_rotation;

	//拡大率
	float m_scale;

	//描画用モデル
	std::unique_ptr<ShunLib::Model> m_model;

	//チーム分け
	TEAM m_team;

public:
	ObjectBase() :m_pos({ 0.0f,0.0f,0.0f }), m_rotation({ 0.0f,0.0f,0.0f }), m_scale(1.0f) {}
	virtual ~ObjectBase() {}

	//描画
	void Render(const Matrix& view, const Matrix& proj);

	//モデルの読み込み
	void LoadModel(const wchar_t* path) { m_model = std::make_unique<ShunLib::Model>(path); }

	//初期化　更新　終了
	virtual void Initialize() = 0;
	virtual void Update()     = 0;
	virtual void Finalize()   = 0;
};