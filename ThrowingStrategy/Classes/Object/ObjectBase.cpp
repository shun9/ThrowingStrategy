#include "ObjectBase.h"

void ObjectBase::Render(const Matrix & view, const Matrix & proj)
{	
	//���f�������݂���Ȃ�Ε`��
	if (m_model)
	{
		Matrix world = Matrix::Identity;

		//�g��@�k��
		world *= Matrix::CreateScale(m_scale);

		//���[�� �s�b�` ���[
		world *= Matrix::CreateRotationZ(m_rotation.m_z);
		world *= Matrix::CreateRotationX(m_rotation.m_x);
		world *= Matrix::CreateRotationY(m_rotation.m_y);

		//�ړ�
		world *= Matrix::CreateTranslation(m_pos);

		//���f���`��
		m_model->Draw(world, view, proj);
	}
}
