//************************************************/
//* @file  :SL_Shape.h
//* @brief :“–‚½‚è”»’è—p‚ÌŒ`óƒNƒ‰ƒX‚Ü‚Æ‚ß
//* @date  :2017/11/12
//* @author:S.Katou
//************************************************/
#include "SL_Shape.h"
#include "../Util/SL_Camera.h"
#include "../Util/BasicShapeModelRenderer.h"

//“–‚½‚è”»’è
bool ShunLib::Collision(IShape* A, IShape* B)
{
	//“¯‚¶‚à‚Ì“¯Žm
	if (A->Type() == B->Type())
	{
		//‹…‚Æ‹…
		if (A->Type() == SHAPE_TYPE::SPHERE)
		{
			Sphere* a = dynamic_cast<Sphere*>(A);
			Sphere* b = dynamic_cast<Sphere*>(B);
			return (*a) * (*b);
		}

		//” ‚Æ” 
		if (A->Type() == SHAPE_TYPE::BOX)
		{
			Box* a = dynamic_cast<Box*>(A);
			Box* b = dynamic_cast<Box*>(B);
			return (*a) * (*b);
		}
	}

	//•Ð•û‚ª‹…
	if (A->Type() == SHAPE_TYPE::SPHERE)
	{
		//‹…‚Æ” 
		if (B->Type() == SHAPE_TYPE::BOX)
		{
			Sphere* a = dynamic_cast<Sphere*>(A);
			Box* b = dynamic_cast<Box*>(B);
			return (*a) * (*b);
		}
	}

	//•Ð•û‚ª” 
	if (A->Type() == SHAPE_TYPE::BOX)
	{
		//” ‚Æ‹…
		if (B->Type() == SHAPE_TYPE::SPHERE)
		{
			Box* a = dynamic_cast<Box*>(A);
			Sphere* b = dynamic_cast<Sphere*>(B);
			return (*a) * (*b);
		}
	}

	return false;
}

/*--“–‚½‚è”»’è—p--*/
//‹…‚Æ‹…
bool ShunLib::operator*(Sphere & A, Sphere & B)
{
	// ’†SÀ•WŠÔ‚Ì‹——£‚ðŒvŽZ
	Vec3 distV = B.CenterPoint() - A.CenterPoint();

	float dist = distV.Length();

	// ”¼Œa‚Ì˜a
	float rad = A.Scale() + B.Scale();
	rad *= rad;

	// ‹——£‚ª”¼Œa‚Ì˜a‚æ‚è‘å‚«‚¯‚ê‚ÎA“–‚½‚Á‚Ä‚¢‚È‚¢
	if (dist > rad)
	{
		return false;
	}

	return true;
}

//‹…‚Æ” 
bool ShunLib::operator*(Sphere & A, Box & B)
{
	return false;
}

//” ‚Æ‹…
bool ShunLib::operator*(Box & A, Sphere & B)
{
	return false;
}

//” ‚Æ” 
bool ShunLib::operator*(Box & A, Box & B)
{
	return false;
}


//‹…‚Ì•`‰æ
void ShunLib::Sphere::Render()
{
	auto camera = ShunLib::MainCamera::GetInstance();
	auto shape = BasicShapeRenderer::GetInstance();

	Matrix world = Matrix::CreateScale(Scale()*2.0f);
	world *= Matrix::CreateTranslation(m_centerPoint);
	shape->DrawSphere(world,camera->ViewMat(),camera->ProjMat());
}

//” ‚Ì•`‰æ
void ShunLib::Box::Render()
{
	auto camera = ShunLib::MainCamera::GetInstance();
	auto shape = BasicShapeRenderer::GetInstance();

	Matrix world;
	world = Matrix::CreateScale(this->Size());
	world *= Matrix::CreateScale(Scale());
	world *= Matrix::CreateTranslation(m_centerPoint);
	shape->DrawCube(world, camera->ViewMat(), camera->ProjMat());
}
