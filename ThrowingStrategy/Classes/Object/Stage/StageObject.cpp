#include "StageObject.h"

Block::Block()
{
	this->Type(BLOCK);
	this->Team(TEAM::NONE);

	//“–‚½‚è”»’è‚ÌÝ’è
	m_collider = new ShunLib::BoxCollider();
	m_collider->Parent(this);
	m_collider->Offset(ShunLib::Vec3(0.0f, 0.55f, 0.0f));
}

Block::~Block()
{
	SAFE_DELETE(m_collider);
}
