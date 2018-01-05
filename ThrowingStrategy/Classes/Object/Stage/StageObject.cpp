#include "StageObject.h"

/// <summary>
/// コンストラクタ
/// </summary>
Block::Block():
	ObjectBase(ObjectConstantNumber::BLOCK)
{
	m_data.Team(ObjectConstantNumber::TEAM::NONE);

	//当たり判定の設定
	m_collider = new ShunLib::BoxCollider();
	m_collider->Parent(this);
	m_collider->Offset(ShunLib::Vec3(0.0f, 0.51f, 0.0f));
	m_collider->IsStatic(true);
}

Block::~Block()
{
	SAFE_DELETE(m_collider);
}
