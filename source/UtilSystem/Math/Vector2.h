#pragma once
#include <string>

namespace TE
{
	class Vector2
	{
	public:
		explicit Vector2(float x = 0, float y = 0);
		Vector2(Vector2 const & v);
		~Vector2();
		float GetX() const { return m_x; }
		float GetY() const { return m_y; }
		void SetX(float x) { m_x = x; }
		void SetY(float y) { m_y = y; }

		inline float Lenght() const;
		float Dot(Vector2 const & v) const;
		Vector2 Normalize();
		Vector2 Rotate(float angle);

		Vector2 Add(Vector2 v);
		Vector2 Add(float x, float y);
		Vector2 Add(float value);
		
		Vector2 Sub(Vector2 v);
		Vector2 Sub(float x, float y);
		Vector2 Sub(float value);
		
		Vector2 Mult(Vector2 v);
		Vector2 Mult(float x, float y);
		Vector2 Mult(float value);
		
		Vector2 Div(Vector2 v);
		Vector2 Div(float x, float y);
		Vector2 Div(float value);
		

		std::string ToString() const;

	private:
		float m_x;
		float m_y;
	};

}