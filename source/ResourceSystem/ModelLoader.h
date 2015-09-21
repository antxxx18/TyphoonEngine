#pragma once

#include "GraphicsSystem/Render.h"
#include "GraphicsSystem/Model.h"

namespace TE
{
	class ModelLoader
	{
	public:
		ModelLoader(Render* pRender);
		bool ObjLoad(Model* pModel, wchar_t* Filename);
		bool MS3DLoad(Model* pModel, wchar_t* Filename);

	//private:
		Render* m_pRender;
	};

}