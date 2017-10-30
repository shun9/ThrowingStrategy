#include "ObjectBase.h"

void ObjectBase::Render(const Matrix & view, const Matrix & proj)
{	
	//ƒ‚ƒfƒ‹‚ª‘¶Ý‚·‚é‚È‚ç‚Î•`‰æ
	if (m_model)
	{
		Matrix world = Matrix::Identity;

		//Šg‘å@k¬
		world *= Matrix::CreateScale(m_scale);

		//ƒ[ƒ‹ ƒsƒbƒ` ƒˆ[
		world *= Matrix::CreateRotationZ(m_rotation.m_z);
		world *= Matrix::CreateRotationX(m_rotation.m_x);
		world *= Matrix::CreateRotationY(m_rotation.m_y);

		//ˆÚ“®
		world *= Matrix::CreateTranslation(m_pos);

		//ƒ‚ƒfƒ‹•`‰æ
		m_model->Draw(world, view, proj);
	}
}
