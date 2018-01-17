//************************************************/
//* @file  :RRT.cpp
//* @brief :RRT�ɂ��o�H�T�����s���N���X
//* @date  :2018/01/12
//* @author:S.Katou
//************************************************/
#include "RRT.h"
#include <functional>
#include <SL_RandomNumber.h>

using namespace ShunLib;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="start">�����ʒu</param>
/// <param name="target">�ڕW�n�_</param>
/// <param name="spd">1��̈ړ���</param>
RRT::RRT(Vec3 start, Vec3 target, float spd):
	m_is2D(false),
	m_spd(spd)
{
	m_start = m_nodeFactory.Create();
	m_target = m_nodeFactory.Create();
	m_start->point = start;
	m_target->point = target;
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
RRT::~RRT()
{
	m_nodeFactory.AllDelete();
}

/// <summary>
/// ���[�g�̐���
/// </summary>
void RRT::CreateRoute()
{
	Node* node = nullptr;

	//�񎟌��Ȃ�΍��������낦��
	if (m_is2D){
		m_target->point.m_y = m_start->point.m_y;
	}

	//�^�[�Q�b�g�ɓ��B����܂Ń��[�v
	while (!(IsReachedTarget(node))){
		//�����_���ȓ_���擾
		node = GetRandomPoint();

		//�ł��߂��_��T��
		Node* parent = SearchNearPoint(node->point);
		node->point = (node->point - parent->point).Normalize() * m_spd;

		//�؍\���ɒǉ�
		parent->children.push_back(node);
		node->parent = parent;
	}

	//�ړI�n�ƂȂ���
	node->children.push_back(m_target);
	m_target->parent = node;

	//���[�g��ݒ�
	SetRoute();
}

/// <summary>
/// �ł��߂��_��T��
/// </summary>
RRT::Node * RRT::SearchNearPoint(const Vec3& point)
{
	Node* nearPoint = m_start;
	float dist = (nearPoint->point - point).Length();

	//�q�̓_���T��
	for (int i = 0; i < (int)m_start->children.size(); i++){
		nearPoint = SearchNearPoint(point, m_start->children[i], nearPoint, dist);
	}

	return nearPoint;
}

/// <summary>
/// �ł��߂��_��T��
/// </summary>
/// <param name="point">�Ώۂ̓_</param>
/// <param name="nearestPoint">���ɒT���_</param>
/// <param name="nearestPoint">����ōł��߂��_</param>
/// <param name="nearestPoint">����ōł��߂�����</param>
RRT::Node* RRT::SearchNearPoint(const Vec3 & point, RRT::Node* nextPoint, RRT::Node* nearestPoint, float distance)
{
	Node* nearPoint = nearestPoint;
	Vec3 vec = (nextPoint->point - point);

	//�ŒZ���������߂���΍X�V
	float dist = vec.Length();
	if (dist < distance){
		nearPoint = nextPoint;
	}

	//�q�̓_���T��
	for (int i = 0; i < (int)nextPoint->children.size(); i++) {
		nearPoint = SearchNearPoint(point, nextPoint->children[i], nearPoint, dist);
	}

	return nearPoint;
}

/// <summary>
/// �����Ə�Q�����ڂ��Ă��邩�ǂ���
/// </summary>
/// <returns></returns>
bool RRT::IsHitSegmentAndObstacle(const ShunLib::Segment& segment)
{
	return false;
}

/// <summary>
/// �����_���ȓ_���擾
/// </summary>
RRT::Node* RRT::GetRandomPoint()
{
	Node* node = m_nodeFactory.Create();
	RandomNumber rn;

	//���W�������_���Ɏ擾
	node->point.m_x = rn(AreaMinX(), AreaMaxX());
	node->point.m_z = rn(AreaMinZ(), AreaMaxZ());

	//�񎟌��̏ꍇ��Y���W�������ʒu�ɍ��킹��
	if (m_is2D){
		node->point.m_y = m_start->point.m_y;
	}
	else{
		node->point.m_y = rn(AreaMinY(), AreaMaxY());
	}

	return node;
}

/// <summary>
/// �ړI�n�ɓ��B�������ǂ���
/// </summary>
bool RRT::IsReachedTarget(Node* node)
{
	if (node == nullptr){
		return false;
	}

	float dist = (m_target->point - node->point).Length();

	//�^�[�Q�b�g�܂ł̋�����1��ňړ��ł���͈͂Ȃ�true
	if (dist < m_spd){
		return true;
	}
	return false;
}

/// <summary>
/// ���[�g��ݒ�
/// </summary>
void RRT::SetRoute()
{
	m_route.push_front(m_target->point);

	//�ċA�p�֐�
	std::function<void(Node*)> SetRoute = [&](Node* node) {
		if (node->parent == nullptr)return;
		m_route.push_front(node->parent->point);
		SetRoute(node->parent);
	};

	//�ċA
	SetRoute(m_target);
}

/// <summary>
/// �T���G���A��X���W�̍ő�l
/// </summary>
float RRT::AreaMaxX()
{
	float max = m_target->point.m_x > m_start->point.m_x ? m_target->point.m_x : m_start->point.m_x;
	return max;
}

/// <summary>
/// �T���G���A��Y���W�̍ő�l
/// </summary>
float RRT::AreaMaxY()
{
	float max = m_target->point.m_y > m_start->point.m_y ? m_target->point.m_y : m_start->point.m_y;
	return max;
}

/// <summary>
/// �T���G���A��Z���W�̍ő�l
/// </summary>
float RRT::AreaMaxZ()
{
	float max = m_target->point.m_z > m_start->point.m_z ? m_target->point.m_z : m_start->point.m_z;
	return max;
}

/// <summary>
/// �T���G���A��X���W�̍ŏ��l
/// </summary>
float RRT::AreaMinX()
{
	float min = m_target->point.m_x < m_start->point.m_x ? m_target->point.m_x : m_start->point.m_x;
	return min;
}

/// <summary>
/// �T���G���A��Y���W�̍ŏ��l
/// </summary>
float RRT::AreaMinY()
{
	float min = m_target->point.m_y < m_start->point.m_y ? m_target->point.m_y : m_start->point.m_y;
	return min;
}

/// <summary>
/// �T���G���A��Z���W�̍ŏ��l
/// </summary>
float RRT::AreaMinZ()
{
	float min = m_target->point.m_z < m_start->point.m_z ? m_target->point.m_z : m_start->point.m_z;
	return min;
}
