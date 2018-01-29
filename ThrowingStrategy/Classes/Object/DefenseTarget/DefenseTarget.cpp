//************************************************/
//* @file  :DefenseTarget.cpp
//* @brief :�h�q�Ώ�
//* @date  :2017/12/12
//* @author:S.Katou
//************************************************/
#include "DefenseTarget.h"
#include "../../Util/Debugger/DebuggerUI.h"
#include "../../UI/HPGauge/HPGauge.h"
#include "../../Physics/Collision/SL_CollisionManager.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
DefenseTarget::DefenseTarget():
	StateObject(this,ObjectConstantNumber::DEFENSE_TARGET)
{
	m_transform.Scale(DEFENSE_TARGET_CONSTANT::MODEL_SCALE);

	//�����蔻��̐ݒ�
	m_collider = new ShunLib::BoxCollider(ShunLib::COLLIDER_LAYER::STATIC);
	m_collider->Parent(this);
	m_collider->ShouldPassInfo(true);
	m_collider->Offset(DEFENSE_TARGET_CONSTANT::COLLIDER_OFFSET);
	m_collider->Shape()->Size(DEFENSE_TARGET_CONSTANT::COLLIDER_SIZE / DEFENSE_TARGET_CONSTANT::MODEL_SCALE);
	m_collider->IsStatic(true);

	//HP�Q�[�W
	m_hpGauge = new HPGauge;
	m_hpGauge->Parent(this);
	m_hpGauge->Offset(DEFENSE_TARGET_CONSTANT::HP_GAUGE_OFFSET);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
DefenseTarget::~DefenseTarget()
{
	SAFE_DELETE(m_collider);
	SAFE_DELETE(m_hpGauge);
}

/// <summary>
/// ������
/// </summary>
void DefenseTarget::Initialize()
{
	//�����蔻����g�p����
	m_collider->IsEnable(true);

	//���̏�����
	StateObject::Initialize();
}

/// <summary>
/// �I��
/// </summary>
void DefenseTarget::Finalize()
{
	//���̏I��
	StateObject::Finalize();

	//�����蔻����g�p���Ȃ�
	m_collider->IsEnable(false);
}

/// <summary>
/// �X�V����
/// </summary>
void DefenseTarget::Update()
{
	if (m_data.Team() == ObjectConstantNumber::BLUE){
		DebuggerUI::GetInstance()->DrawDebugText("DefenseTarget BLUE : %d", m_data.HP());
	}
	else {
		DebuggerUI::GetInstance()->DrawDebugText("DefenseTarget RED  : %d", m_data.HP());
	}

	StateObject::Update();
}
