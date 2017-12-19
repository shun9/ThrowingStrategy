//************************************************/
//* @file  :ObjectConstantNumber.h
//* @brief :�I�u�W�F�N�g�֘A�̒萔
//* @date  :2017/12/12
//* @author:S.Katou
//************************************************/
#pragma once
#include <SL_Math.h>

class ObjectConstantNumber
{

public:
	//�I�u�W�F�N�g�ꗗ
	enum OBJECT_LIST
	{
		ROOT = 0,		//���[�g�I�u�W�F�N�g
		PLAYER,			//�v���C���[
		COMMANDER,      //�w����
		UNIT,           //��������郆�j�b�g
		BLOCK,          //�u���b�N
		DEFENSE_TARGET,	//�h�q�Ώ�
		SUMMONER,		//���j�b�g����������I�u�W�F�N�g
		STAGE,			//�X�e�[�W

		OBJECT_LIST_END,//�I�u�W�F�N�g�̎�ސ�
	};

	//�X�e�[�W�ꗗ
	enum STAGE_LIST
	{
		GROUND = 0,		//�n�ʂ݂̂̃X�e�[�W

		STAGE_LIST_END,//�X�e�[�W��ސ�
	};

	//�`�[������
	enum TEAM
	{
		NONE = -1,    //�`�[������
		RED = 0,
		BLUE,

		TEAM_END,     //�`�[����
	};

	//������
	enum THROW_TYPE
	{
		LINE = 0,

		THROW_TYPE_END,
	};

public:
	//��Ԃ��������I�u�W�F�N�g�ꗗ
	static const OBJECT_LIST STATE_OBJECT[5];

public:
	//�v���C���[�֘A
	class PLAYER_CONSTANT
	{
	public:
		static const float COLLIDER_SIZE;			//�{�̂̓����蔻��̃T�C�Y
		static const ShunLib::Vec3 COLLIDER_OFFSET;	//�����蔻��̒��S�ʒu
		static const ShunLib::Vec3 HP_GAUGE_OFFSET;	//HP�Q�[�W�̒��S�ʒu

		/// <summary>
		/// �����Ă���I�u�W�F�N�g�̒��S�ʒu
		/// </summary>
		/// <param name="num">���Ԗڂ̃A�C�e����</param>
		static ShunLib::Vec3 HAVING_OFFSET(int num) {
			return ShunLib::Vec3(0.0f, 2.0f * (num + 1) + 2.0f, 0.0f);
		}
	};

	//���j�b�g�֘A
	class UNIT_CONSTANT
	{
	public:
		//���j�b�g�̎��
		enum TYPE_LIST
		{
			NORMAL = 0,

			UNIT_LIST_END,
		};
	public:
		static const ShunLib::Vec3 COLLIDER_OFFSET;	//�����蔻��̒��S�ʒu
		static const ShunLib::Vec3 HP_GAUGE_OFFSET;	//HP�Q�[�W�̒��S�ʒu
		static const float COLLIDER_BODY_SIZE;		//�{�̂̓����蔻��̃T�C�Y
		static const float COLLIDER_ATTACK_SIZE;	//�U���͈͂̓����蔻��̃T�C�Y
		static const float COLLIDER_CHASE_SIZE;		//�ǐՔ͈͂̓����蔻��̃T�C�Y
	};

	//�h�q�Ώۊ֘A
	class DEFENSE_TARGET_CONSTANT
	{
	public:
		static const float MODEL_SCALE;				//���f���̔{��
		static const ShunLib::Vec3 COLLIDER_OFFSET;	//�����蔻��̒��S�ʒu
		static const ShunLib::Vec3 COLLIDER_SIZE;	//�{�̂̓����蔻��̃T�C�Y
		static const ShunLib::Vec3 HP_GAUGE_OFFSET;	//HP�Q�[�W�̒��S�ʒu
	};

	//�����t�֘A
	class SUMMONER_CONSTANT
	{
	public:
		static const ShunLib::Vec3 COLLIDER_OFFSET;	//�����蔻��̒��S�ʒu
		static const ShunLib::Vec3 COLLIDER_SIZE;	//�{�̂̓����蔻��̃T�C�Y
		static const ShunLib::Vec3 HP_GAUGE_OFFSET;	//HP�Q�[�W�̒��S�ʒu
	};

};

