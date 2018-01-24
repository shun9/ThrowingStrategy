//************************************************/
//* @file  :StandardStage.cpp
//* @brief :�M�~�b�N�̖����X�e�[�W
//* @date  :2018/01/24
//* @author:S.Katou
//************************************************/
#include "StandardStage.h"
#include <SL_Colors.h>
#include "StageObject.h"
#include "../ObjectFactory.h"
#include "../UnitSummoner/UnitSummoner.h"
#include "../../Util/SL_Camera.h"

/// <summary>
/// ������
/// </summary>
void StandardStage::Initialize()
{
	//��Q���̐ݒu
	SettingObstacle();

	//�I�u�W�F�N�g�̐ݒu
	SettingBlueObject();
	SettingRedObject();
}

/// <summary>
/// �I��
/// </summary>
void StandardStage::Finalize()
{
}

/// <summary>
/// ��Q���̐ݒu
/// </summary>
void StandardStage::SettingObstacle()
{
	//�X�e�[�W�g�̐ݒu
	SettingFrameOfStage();

	//�ǂ̐ݒu
	SettingWall();
}

/// <summary>
/// �`�[���̐ݒu
/// </summary>
void StandardStage::SettingBlueObject()
{
	//�J�����ݒ�
	auto camera = ShunLib::MainCamera::GetInstance();

	//�I�u�W�F�N�g����
	auto factory = ObjectFactory::GetInstance();

	//�����`�[��
	ObjectConstantNumber::TEAM team = ObjectConstantNumber::BLUE;

	//�v���C���[�쐬
	//�v���C���[�͐`�[��
	auto p = factory->CreateObject(ObjectConstantNumber::PLAYER);
	camera->FollowTarget(p);
	camera->ChangeMode(FOLLOW_CAMERA);
	p->Transform().Pos(ShunLib::Vec3(0.0f, 0.0f, 35.0f));
	p->Data().Team(team);
	p->SetParent(this);

	//���j�b�g�����I�u�W�F�N�g
	auto summoner = factory->CreateObject(ObjectConstantNumber::SUMMONER);
	summoner->Transform().Pos(ShunLib::Vec3(0.0f, 0.0f, 30.0f));
	summoner->Data().Team(team);
	dynamic_cast<UnitSummoner*>(summoner)->Interval(1000);
	summoner->SetParent(this);

	//�h�q�Ώ�
	auto target = factory->CreateObject(ObjectConstantNumber::DEFENSE_TARGET);
	target->Transform().Pos(ShunLib::Vec3(0.0f, 0.0f, 40.0f));
	target->Data().Team(team);
	target->SetParent(this);

}

/// <summary>
/// �ԃ`�[���̐ݒu
/// </summary>
void StandardStage::SettingRedObject()
{
	//�I�u�W�F�N�g����
	auto factory = ObjectFactory::GetInstance();

	//�����`�[��
	ObjectConstantNumber::TEAM team = ObjectConstantNumber::RED;

	//�����I�u�W�F�N�g
	auto summoner = factory->CreateObject(ObjectConstantNumber::SUMMONER);
	summoner->Transform().Pos(ShunLib::Vec3(0.0f, 0.0f, -30.0f));
	summoner->Data().Team(team);
	summoner->SetParent(this);
	dynamic_cast<UnitSummoner*>(summoner)->Interval(2000);

	//�h�q�Ώ�
	auto target = factory->CreateObject(ObjectConstantNumber::DEFENSE_TARGET);
	target->Transform().Pos(ShunLib::Vec3(0.0f, 0.0f, -40.0f));
	target->Data().Team(team);
	target->SetParent(this);
}

/// <summary>
/// �ǂ̐ݒu
/// </summary>
void StandardStage::SettingWall()
{
	auto factory = ObjectFactory::GetInstance();

	//��
	auto obj = factory->CreateObject(OBJECT_LIST::BLOCK);
	obj->Transform().Pos(Vec3(0.0f, 0.0f, 0.0f));
	obj->Transform().Scale(Vec3(10.0f, 4.0f, 1.0f));
	dynamic_cast<Block*>(obj)->SetColor(ShunLib::Colors::BLUE);

	this->AddChild(obj);

	//��
	obj = factory->CreateObject(OBJECT_LIST::BLOCK);
	obj->Transform().Pos(Vec3(20.0f, 0.0f, 0.0f));
	obj->Transform().Scale(Vec3(1.0f, 4.0f, 10.0f));
	dynamic_cast<Block*>(obj)->SetColor(ShunLib::Colors::BLUE);
	this->AddChild(obj);

	//��
	obj = factory->CreateObject(OBJECT_LIST::BLOCK);
	obj->Transform().Pos(Vec3(-20.0f, 0.0f, 0.0f));
	obj->Transform().Scale(Vec3(10.0f, 4.0f, 1.0f));
	dynamic_cast<Block*>(obj)->SetColor(ShunLib::Colors::BLUE);
	this->AddChild(obj);

}

/// <summary>
/// �X�e�[�W�g�̐ݒu
/// </summary>
void StandardStage::SettingFrameOfStage()
{
	//�I�u�W�F�N�g����
	auto factory = ObjectFactory::GetInstance();

	//�n��
	ObjectBase* obj = factory->CreateObject(OBJECT_LIST::BLOCK);
	obj->Transform().Pos(Vec3(0.0f, -1.0f, 0.0f));
	obj->Transform().Scale(Vec3(100.0f, 1.0f, 100.0f));
	this->AddChild(obj);

	//�X�e�[�W�g �E
	obj = factory->CreateObject(OBJECT_LIST::BLOCK);
	obj->Transform().Pos(Vec3(49.0f, 5.0f, 0.0f));
	obj->Transform().Scale(Vec3(1.0f, 10.0f, 100.0f));
	this->AddChild(obj);

	//�X�e�[�W�g ��
	obj = factory->CreateObject(OBJECT_LIST::BLOCK);
	obj->Transform().Pos(Vec3(-49.0f, 5.0f, 0.0f));
	obj->Transform().Scale(Vec3(1.0f, 10.0f, 100.0f));
	this->AddChild(obj);

	//�X�e�[�W�g ��
	obj = factory->CreateObject(OBJECT_LIST::BLOCK);
	obj->Transform().Pos(Vec3(0.0f, 5.0f, 49.0f));
	obj->Transform().Scale(Vec3(100.0f, 10.0f, 1.0f));
	this->AddChild(obj);

	//�X�e�[�W�g ��O
	obj = factory->CreateObject(OBJECT_LIST::BLOCK);
	obj->Transform().Pos(Vec3(0.0f, 5.0f, -49.0f));
	obj->Transform().Scale(Vec3(100.0f, 10.0f, 1.0f));
	this->AddChild(obj);
}
