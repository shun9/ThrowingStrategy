//************************************************/
//* @file  :ObjectFactory.cpp
//* @brief :�I�u�W�F�N�g�𐶐�����N���X
//* @date  :2017/10/30
//* @author:S.Katou
//************************************************/
#include "ObjectFactory.h"
#include "Player\Player.h"

/// <summary>
/// �I�u�W�F�N�g�̐���
/// </summary>
/// <param name="num">�I�u�W�F�N�g�̔ԍ�</param>
/// <returns>���������I�u�W�F�N�g</returns>
ObjectBase* ObjectFactory::Create(OBJECT_LIST num)
{
	ObjectBase* obj = nullptr;

	switch (num)
	{
	case PLAYER:
		obj = m_playerFactory.Create();
		break;

	default:
		break;
	}

	return obj;
}
