#pragma once
#include <GamePad.h>
#include <SL_Singleton.h>
namespace ShunLib
{
	class GamePadManager:public Singleton<GamePadManager>
	{
		friend Singleton<GamePadManager>;
	public:
		enum BUTTON_LIST
		{
			A,
			B,
			X,
			Y,
			L,
			R,
		};

		enum BUTTON_STATE
		{
			UP       = DirectX::GamePad::ButtonStateTracker::ButtonState::UP,
			HELD     = DirectX::GamePad::ButtonStateTracker::ButtonState::HELD,
			RELEASED = DirectX::GamePad::ButtonStateTracker::ButtonState::RELEASED,
			PRESSED  = DirectX::GamePad::ButtonStateTracker::ButtonState::PRESSED,
		};

	private:
		std::unique_ptr<DirectX::GamePad>m_pad;
		DirectX::GamePad::State m_state;
		DirectX::GamePad::ButtonStateTracker m_tracker;

	public:
		void Update(){
			m_state = m_pad->GetState(0);
			m_tracker.Update(m_state);
		}

		//押してる間 true
		bool IsPushed(BUTTON_LIST button){
			bool push = false;

			switch (button)
			{
			case BUTTON_LIST::A:push = m_state.IsAPressed(); break;
			case BUTTON_LIST::B:push = m_state.IsBPressed();break;
			case BUTTON_LIST::X:push = m_state.IsXPressed();break;
			case BUTTON_LIST::Y:push = m_state.IsYPressed();break;
			case BUTTON_LIST::L:push = m_state.IsRightTriggerPressed();break;
			case BUTTON_LIST::R:push = m_state.IsLeftTriggerPressed();break;
			default:break;
			}

			return push;
		}

		//指定した状態なら true
		//デフォルトは押したフレームのみ true
		bool IsTrigger(BUTTON_LIST button, BUTTON_STATE state = PRESSED) {
			auto push = m_tracker.a;

			switch (button)
			{
			case BUTTON_LIST::A:push = m_tracker.a; break;
			case BUTTON_LIST::B:push = m_tracker.b; break;
			case BUTTON_LIST::X:push = m_tracker.x; break;
			case BUTTON_LIST::Y:push = m_tracker.y; break;
			case BUTTON_LIST::L:push = m_tracker.rightTrigger; break;
			case BUTTON_LIST::R:push = m_tracker.leftTrigger; break;
			default:return false;
			}

			return(push == state);
		}

	private:
		GamePadManager() {
			m_pad = std::make_unique<DirectX::GamePad>();
		}
		~GamePadManager() {}
	};
}