//************************************************/
//* @file  :UnitRoamState.cpp
//* @brief :��������郆�j�b�g�̂�������
//* @date  :2017/11/20
//* @author:S.Katou
//************************************************/
#include "UnitRoamState.h"

#include <cmath>
#include <SL_Conversion.h>
#include <SL_RandomNumber.h>
#include "../../../Main/SL_MyStepTimer.h"

using namespace std;
using namespace ShunLib;

void UnitRoamState::Enter(Unit * obj)
{
	ChangeDirection();
}

void UnitRoamState::Execute(Unit * obj)
{
	auto timer = MyStepTimer::GetInstance();
	m_timeCnt += timer->GetElapsedSeconds();
	
	//��莞�Ԃ��ƂɈړ����ύX
	if (m_timeCnt > m_limit){
		//�i�ޕ�����ς���
		ChangeDirection();

		m_timeCnt = 0.0f;
	}

	//���x�ݒ�
	obj->Velocity(m_direction * obj->Spd());

	obj->Move();
}

void UnitRoamState::Exit(Unit * obj)
{

}

void UnitRoamState::ChangeDirection()
{
	RandomNumber rn;

	//�i�ޕ����������_���ɐݒ�
	float rad = ToRadian(rn(0.0f, 360.0f));

	//���x�ݒ�
	m_direction = Vec3(-sin(rad), 0.0f, cos(rad)).Normalize();
}
