//************************************************/
//* @file  :SL_MyStepTimer.h
//* @brief :StepTimer�̃��b�v�N���X
//* @date  :2017/10/28
//* @author:S.Katou
//************************************************/
#pragma once
#include <SL_Singleton.h>
#include "../../StepTimer.h"

namespace ShunLib
{
	class MyStepTimer :public Singleton<MyStepTimer>
	{
		friend Singleton<MyStepTimer>;
	private:
		DX::StepTimer m_timer;

	public:
		//�^�C�}�[�X�V
		template<typename TUpdate>
		void Tick(const TUpdate& update) {};
		
		//�^�C�}�[���Z�b�g
		void ResetElapsedTime() { m_timer.ResetElapsedTime(); }
	
		uint64_t GetElapsedTicks() const { return m_timer.GetElapsedTicks(); }
		double GetElapsedSeconds() const { return m_timer.GetElapsedSeconds(); }

		uint64_t GetTotalTicks() const { return m_timer.GetTotalTicks(); }
		double GetTotalSeconds() const { return m_timer.GetTotalSeconds(); }

		uint32_t GetFrameCount() const { return m_timer.GetFrameCount(); }

		uint32_t GetFramesPerSecond() const { return m_timer.GetFramesPerSecond(); }

		void SetFixedTimeStep(bool isFixedTimestep) { m_timer.SetFixedTimeStep(isFixedTimestep); }

		void SetTargetElapsedTicks(uint64_t targetElapsed) { m_timer.SetTargetElapsedTicks(targetElapsed); }
		void SetTargetElapsedSeconds(double targetElapsed) { m_timer.SetTargetElapsedSeconds(targetElapsed); }

	private:
		MyStepTimer() {}
		~MyStepTimer() {}

	};

}