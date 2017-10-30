#include "ObjectBase.h"

void ObjectBase::Render(const Matrix & view, const Matrix & proj)
{	
	//モデルが存在するならば描画
	if (m_model)
	{
		Matrix world = Matrix::Identity;

		//拡大　縮小
		world *= Matrix::CreateScale(m_scale);

		//ロール ピッチ ヨー
		world *= Matrix::CreateRotationZ(m_rotation.m_z);
		world *= Matrix::CreateRotationX(m_rotation.m_x);
		world *= Matrix::CreateRotationY(m_rotation.m_y);

		//移動
		world *= Matrix::CreateTranslation(m_pos);

		//モデル描画
		m_model->Draw(world, view, proj);
	}
}
