#include "StageObject.h"

/// <summary>
/// コンストラクタ
/// </summary>
Block::Block()
{
	this->Type(ObjectConstantNumber::BLOCK);
	this->Team(ObjectConstantNumber::TEAM::NONE);

	//当たり判定の設定
	m_collider = new ShunLib::BoxCollider();
	m_collider->Parent(this);
	m_collider->Offset(ShunLib::Vec3(0.0f, 0.51f, 0.0f));
}

Block::~Block()
{
	SAFE_DELETE(m_collider);
}
