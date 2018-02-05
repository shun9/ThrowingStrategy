//************************************************/
//* @file  :UIConstantNumber.h
//* @brief :UI�֘A�̒萔
//* @date  :2018/02/05
//* @author:S.Katou
//************************************************/
#pragma once
#include <SL_Math.h>

class UIConstantNumber {
public:
	using Vec2 = ShunLib::Vec2;
	using Vec3 = ShunLib::Vec3;

	//�e�L�X�g�̃��C���[�ꗗ
	enum TEXT_LAYER_LIST {
		TITLE_LAYER,
		TEXT_LAYER_LIST_END
	};

	//HP�Q�[�W
	class HP_GAUGE_CONSTANT {
	public:
		static const Vec3 SCALE;
	};

	//�\�����e�n�_�̃J�[�\��
	class THROW_CURSOR_CONSTANT {
	public:
		static const Vec3 SCALE;
	};

	//�I����
	class OPTION_BOARD_CONSTANT {
	public:
		//�摜�̏c�Ɖ��̃T�C�Y
		static const float TEXTURE_WIDTH;
		static const float TEXTURE_HEIGHT;

		//�����摜�̍����i1�����̃T�C�Y�j
		static const float STRING_TEXTURE_HEIGHT;

		//�J�[�\���̃T�C�Y
		static const float CURSOR_SIZE;

		//�O�g�̕�
		static const float FLAME_SIZE;
	};

	//�t�F�[�h���̍���
	class FADE_BLACK {
	public:
		static const Vec2 ANCHOR;
		static const float SCALE_MAX;
		static const float SCALE_MIN;
	};

};