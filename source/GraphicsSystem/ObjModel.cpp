#include "stdafx.h"
#include "ObjModel.h"


namespace TE
{
	ObjModel::ObjModel(Render * pRender)
	{

	}

	bool ObjModel::Init()
	{
		return false;
	}

	void ObjModel::Draw(CXMMATRIX view)
	{
	}

	bool ObjModel::Close()
	{
		return false;
	}

	void ObjModel::Translate(float x, float y, float z)
	{
	}

	void ObjModel::Rotate(float angle, float x, float y, float z)
	{
	}

	void ObjModel::Scale(float x, float y, float z)
	{
	}

	void ObjModel::Identity()
	{
	}

	bool ObjModel::LoadObjFile(wchar_t const * Filename)
	{
		return false;
	}

	void ObjModel::RenderBuffers()
	{
	}

	void ObjModel::SetShaderParameters(CXMMATRIX viewmatrix)
	{
	}

	void ObjModel::RenderShader()
	{
	}



}
