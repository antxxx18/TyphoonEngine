#pragma once

#include "Render.h"
#include "BitmapFont.h"

namespace TE
{
	class Text
	{
	public:
		Text(Render *render, BitmapFont *font);

		bool Init(std::wstring const &text, bool statictext = true, int charsize = 0);
		void Draw(float r, float g, float b, float x, float y);
		void Close();

		bool SetText(std::wstring const &text);

	private:
		bool m_InitBuffers(std::wstring const &text);
		void m_RenderBuffers();
		bool m_updatebuffer(std::wstring const &text);

		Render *m_render;

		BitmapFont *m_font;
		ID3D11Buffer *m_vertexBuffer;
		ID3D11Buffer *m_indexBuffer;
		int m_numindex;
		int m_numdrawindex;
		int m_numvertex;

		bool m_isStatic;
		int m_size;
	};

}
