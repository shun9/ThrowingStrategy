//************************************************/
//* @file  :GroundStage.cpp
//* @brief :�n�ʂ݂̂̃X�e�[�W
//* @date  :2017/12/07
//* @author:S.Katou
//************************************************/
#include "GroundStage.h"
#include "../ObjectFactory.h"
#include "../../Util/SL_Camera.h"
#include "../UnitSummoner/UnitSummoner.h"

void GroundStage::Initialize()
{
	//��Q���̐ݒu
	SettingObstacle();

	//�`�[���̐ݒu
	SettingBlueObject();

	//�ԃ`�[���ݒu
	SettingRedObject();

	//���̏�����
	//�q�̍X�V
	ObjectBase::Initialize();
}

void GroundStage::Finalize()
{
	ObjectBase::Finalize();
}

/// <summary>
/// ��Q���̐ݒu
/// </summary>
void GroundStage::SettingObstacle() {
	auto factory = ObjectFactory::GetInstance();
	ObjectBase* b = factory->CreateObject(OBJECT_LIST::BLOCK);
	b->Pos(ShunLib::Vec3(0.0f, -1.0f, 0.0f));
	b->Scale(ShunLib::Vec3(100.0f, 1.0f, 100.0f));

	this->AddChild(b);
}


/// <summary>
/// �`�[���I�u�W�F�N�g�̐ݒu
/// </summary>
void GroundStage::SettingBlueObject()
{
	//�J�����ݒ�
	auto camera = ShunLib::MainCamera::GetInstance();

	//�I�u�W�F�N�g����
	auto factory = ObjectFactory::GetInstance();

	//�v���C���[�쐬
	//�v���C���[�͐`�[��
	auto p = factory->CreateObject(ObjectConstantNumber::PLAYER);
	camera->FollowTarget(p);
	camera->ChangeMode(FOLLOW_CAMERA);
	p->Pos(ShunLib::Vec3(-25.0f, 0.0f, 0.0f));
	p->Team(ObjectConstantNumber::BLUE);

	//���j�b�g�����I�u�W�F�N�g
	auto summoner = factory->CreateObject(ObjectConstantNumber::SUMMONER);
	summoner->Pos(ShunLib::Vec3(-20.0f, 0.0f, 0.0f));
	summoner->Team(p->Team());
	dynamic_cast<UnitSummoner*>(summoner)->Interval(1000);

	//�h�q�Ώ�
	auto target = factory->CreateObject(ObjectConstantNumber::DEFENSE_TARGET);
	target->Pos(ShunLib::Vec3(-30.0f, 0.0f, 0.0f));
	target->Team(p->Team());
}

/// <summary>
/// �ԃ`�[���I�u�W�F�N�g�̐ݒu
/// </summary>
void GroundStage::SettingRedObject()
{
	//�I�u�W�F�N�g����
	auto factory = ObjectFactory::GetInstance();

	//�����I�u�W�F�N�g
	auto summoner = factory->CreateObject(ObjectConstantNumber::SUMMONER);
	summoner->Pos(ShunLib::Vec3(20.0f, 0.0f, 0.0f));
	summoner->Team(ObjectConstantNumber::TEAM::RED);
	dynamic_cast<UnitSummoner*>(summoner)->Interval(2000);

	//�h�q�Ώ�
	auto target = factory->CreateObject(ObjectConstantNumber::DEFENSE_TARGET);
	target->Pos(ShunLib::Vec3(30.0f, 0.0f, 0.0f));
	target->Team(ObjectConstantNumber::TEAM::RED);
}
