//************************************************/
//* @file  :DefenseTarget.cpp
//* @brief :防衛対象
//* @date  :2017/12/12
//* @author:S.Katou
//************************************************/
#include "DefenseTarget.h"
#include "../../Util/Debugger/DebuggerUI.h"
#include "../../UI/HPGauge/HPGauge.h"
#include "../../Physics/Collision/SL_CollisionManager.h"

/// <summary>
/// コンストラクタ
/// </summary>
DefenseTarget::DefenseTarget():
	StateObject(this,ObjectConstantNumber::DEFENSE_TARGET)
{
	m_transform.Scale(DEFENSE_TARGET_CONSTANT::MODEL_SCALE);

	//当たり判定の設定
	m_collider = new ShunLib::BoxCollider(ShunLib::COLLIDER_LAYER::STATIC);
	m_collider->Parent(this);
	m_collider->ShouldPassInfo(true);
	m_collider->Offset(DEFENSE_TARGET_CONSTANT::COLLIDER_OFFSET);
	m_collider->Shape()->Size(DEFENSE_TARGET_CONSTANT::COLLIDER_SIZE / DEFENSE_TARGET_CONSTANT::MODEL_SCALE);
	m_collider->IsStatic(true);

	//HPゲージ
	m_hpGauge = new HPGauge;
	m_hpGauge->Parent(this);
	m_hpGauge->Offset(DEFENSE_TARGET_CONSTANT::HP_GAUGE_OFFSET);
}

/// <summary>
/// デストラクタ
/// </summary>
DefenseTarget::~DefenseTarget()
{
	SAFE_DELETE(m_collider);
	SAFE_DELETE(m_hpGauge);
}

/// <summary>
/// 初期化
/// </summary>
void DefenseTarget::Initialize()
{
	//当たり判定を使用する
	m_collider->IsEnable(true);

	//基底の初期化
	StateObject::Initialize();
}

/// <summary>
/// 終了
/// </summary>
void DefenseTarget::Finalize()
{
	//基底の終了
	StateObject::Finalize();

	//当たり判定を使用しない
	m_collider->IsEnable(false);
}

/// <summary>
/// 更新処理
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
