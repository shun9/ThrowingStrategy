//************************************************/
//* @file  :RRT.h
//* @brief :RRT�ɂ��o�H�T�����s���N���X
//* @date  :2018/01/12
//* @author:S.Katou
//************************************************/
#pragma once

#include <vector>
#include <deque>
#include <memory>
#include <SL_Math.h>
#include <SL_Factory.h>
#include "../Object/SL_Shape.h"

class RRT
{
protected:
	//RRT�p�̃m�[�h
	struct Node
	{
		ShunLib::Vec3 point;
		Node* parent;
		std::vector<Node*>children;
		Node() :parent(nullptr) {}
	};

public:
	using Vec3 = ShunLib::Vec3;
	using Route = std::deque<Vec3>;

protected:
	//�m�[�h�����p�̃t�@�N�g���[
	ShunLib::Factory<RRT::Node>m_nodeFactory;

	Node* m_target;//�ڕW�n�_
	Node* m_start; //�X�^�[�g�n�_
	float m_spd;   //1��̈ړ���

	//���[�g
	Route m_route;

	//�񎟌���ŒT�������邩�ǂ���
	bool m_is2D;

public:
	RRT(Vec3 start, Vec3 target, float spd);
	~RRT();

	//���[�g�̐���
	void CreateRoute();

	/*--Setter--*/
	void Is2D(bool is2D) { m_is2D = is2D; }

	/*--Getter--*/
	bool Is2D() { return m_is2D; }
	Route& GetRoute() { return m_route; }

protected:
	//�ł��߂��_��T��
	Node* SearchNearPoint(const Vec3& point);

	//�ł��߂��_��T�� (�ċA�p)
	Node* SearchNearPoint(const Vec3& point, Node* parentPoint, RRT::Node* nearestPoint,float dist);

	//��������Q���Ɛڂ��Ă��邩�ǂ���
	bool IsHitSegmentAndObstacle(const ShunLib::Segment& segment);

	//�����_���ȓ_���擾
	RRT::Node* GetRandomPoint();

	//�ړI�n�ɓ��B�������ǂ���
	bool IsReachedTarget(Node* node);

	//���[�g��ݒ�
	void SetRoute();

	//�T���G���A�̍ő�l�ƍŏ��l
	float AreaMaxX();
	float AreaMaxY();
	float AreaMaxZ();
	float AreaMinX();
	float AreaMinY();
	float AreaMinZ();
};