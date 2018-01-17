//************************************************/
//* @file  :UnitRRTState.cpp
//* @brief :ユニットをRRTで動かしてみた
//* @date  :2018/01/12
//* @author:S.Katou
//************************************************/
#include "UnitRRTState.h"
#include <SL_ObjectHolder.h>
#include "../../../Util/Visitor/Visitor.h"
#include "../../../Main/SL_MyStepTimer.h"

using namespace ShunLib;

void UnitRRTState::Enter(Unit * unit)
{
	m_timeCnt = 0.0f;
	m_routeUpdateInterval = 10.0f;

	//ルート更新
	UpdateRoute(unit);
}

void UnitRRTState::Execute(Unit * unit)
{
	//時間を計測
	auto timer = MyStepTimer::GetInstance();
	m_timeCnt += timer->GetElapsedSeconds();

	//一定時間ごとにルートを更新
	if (m_timeCnt > m_routeUpdateInterval) {

		//ルート更新
		UpdateRoute(unit);

		m_timeCnt = 0.0f;
	}

	//速度設定 移動
	unit->Transform().Velocity(m_route[m_routeIndex] * unit->Data().Spd());
	unit->Move();
	m_routeIndex++;
}

void UnitRRTState::Exit(Unit * unit)
{

}

/// <summary>
/// ルートの更新
/// </summary>
void UnitRRTState::UpdateRoute(Unit* unit)
{
	auto objHolder = ObjectHolder::GetInstance();

	//敵の防衛対象をターゲットに設定
	SearchTeamVisitor st(unit->Data().Team());
	st.VisitAnotherTeam();
	objHolder->Accept(ObjectConstantNumber::DEFENSE_TARGET, &st);

	//ルート生成
	RRT rrt(unit->Transform().Pos(), st.List()[0]->Transform().Pos(), unit->Data().Spd()*60);
	rrt.Is2D(true);
	rrt.CreateRoute();

	//ルート取得
	m_route = rrt.GetRoute();

	m_routeIndex = 0;
}
