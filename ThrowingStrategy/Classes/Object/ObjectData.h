//************************************************/
//* @file  :ObjectData.h
//* @brief :オブジェクトが使用するデータをまとめたクラス
//* @date  :2017/11/02
//* @author:S.Katou
//************************************************/
#pragma once
#include <SL_Math.h>
#include "ObjectConstantNumber.h"
#include "ObjectParamHolder.h"

class ObjectData
{
private:
	using Vec3 = ShunLib::Vec3;
	using Matrix = ShunLib::Matrix;

protected:
	Vec3 m_pos;        //位置
	Vec3 m_rotation;   //回転角度
	Vec3 m_velocity;   //移動速度
	Vec3 m_scale;      //拡大率
	TEAM m_team;       //チーム分け
	OBJECT_LIST m_type;//このオブジェクトの種類
	bool m_isFriction;//物理の影響を受けるかどうか

public:
	ObjectData() :
		m_pos({ 0.0f,0.0f,0.0f }),
		m_rotation({ 0.0f,0.0f,0.0f }),
		m_velocity({ 0.0f,0.0f,0.0f }),
		m_scale(1.0f),
		m_isFriction(true)
	{}
	virtual ~ObjectData() {}

	//Getter
	Vec3		 Pos     () { return m_pos                  ; }
	Vec3		 Rotation() { return m_rotation             ; }
	Vec3		 Velocity() { return m_velocity             ; }
	Vec3		 Scale   () { return m_scale                ; }
	float		 Spd     () { return OBJ_PARAM(m_type).spd  ; }
	int			 MaxHP   () { return OBJ_PARAM(m_type).maxHP; }
	float		 Power   () { return OBJ_PARAM(m_type).power; }
	TEAM		 Team    () { return m_team                 ; }
	OBJECT_LIST	 Type    () { return m_type                 ; }
	bool	   IsFriction() { return m_isFriction;}

	//Setter
	void Pos         (const Vec3& pos  ) { m_pos        = pos        ; }
	void Rotation    (const Vec3& rot  ) { m_rotation   = rot        ; }
	void Velocity    (const Vec3& vel  ) { m_velocity   = vel        ; }
	void Scale       (const Vec3& scale) { m_scale      = scale      ; }
	void Scale		 (float scale	   ) { m_scale	    = Vec3(scale); }
	void Team        (TEAM t           ) { m_team       = t          ; }
	void Type        (OBJECT_LIST type ) { m_type       = type       ; }
	void IsFriction  (bool fri         ) { m_isFriction = fri        ; }
};
