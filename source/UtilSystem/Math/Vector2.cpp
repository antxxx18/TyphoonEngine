#include "stdafx.h"
#include "Vector2.h"
#include <cmath>
#include "TEMath.h"

namespace TE
{
	Vector2::Vector2(float x, float y)
	{
		m_x = x;
		m_y = y;
	}


	Vector2::Vector2(Vector2 const & v)
	{
		Vector2(v.GetX(), v.GetY());
	}

	Vector2::~Vector2()
	{}

	inline float Vector2::Lenght() const
	{
		return sqrtf(m_x*m_x + m_y*m_y);
	}

	float Vector2::Dot(Vector2 const & v) const
	{
		return m_x*v.GetX() + m_y*v.GetY();
	}

	Vector2 Vector2::Normalize()
	{
		float length = Lenght();

		m_x /= length;
		m_y /= length;

		return *this;
	}

	Vector2 Vector2::Rotate(float angle)
	{
		float rad = ToRadians(angle);
		float cosa = cosf(rad);
		float sina = sinf(rad);

		float x = m_x;
		float y = m_y;

		m_x = x * cosa - y * sina;
		m_y = x * sina + y * cosa;

		return *this;
	}

	Vector2 Vector2::Add(Vector2 v)
	{
		m_x += v.GetX();
		m_y += v.GetY();

		return *this;
	}

	Vector2 Vector2::Add(float x, float y)
	{
		m_x += x;
		m_y += y;

		return *this;
	}

	Vector2 Vector2::Add(float value)
	{
		m_x += value;
		m_y += value;

		return *this;
	}

	Vector2 Vector2::Sub(Vector2 v)
	{
		m_x -= v.GetX();
		m_y -= v.GetY();

		return *this;
	}

	Vector2 Vector2::Sub(float x, float y)
	{
		m_x -= x;
		m_y -= y;

		return *this;
	}

	Vector2 Vector2::Sub(float value)
	{
		m_x -= value;
		m_y -= value;

		return *this;
	}

	Vector2 Vector2::Mult(Vector2 v)
	{
		m_x *= v.GetX();
		m_y *= v.GetY();

		return *this;
	}

	Vector2 Vector2::Mult(float x, float y)
	{
		m_x *= x;
		m_y *= y;

		return *this;
	}

	Vector2 Vector2::Mult(float value)
	{
		m_x *= value;
		m_y *= value;

		return *this;
	}

	Vector2 Vector2::Div(Vector2 v)
	{
		m_x /= v.GetX();
		m_y /= v.GetY();

		return *this;
	}

	Vector2 Vector2::Div(float x, float y)
	{
		m_x /= x;
		m_y /= y;

		return *this;
	}

	Vector2 Vector2::Div(float value)
	{
		m_x /= value;
		m_y /= value;

		return *this;
	}

	std::string Vector2::ToString() const
	{
		return "(" + std::to_string(m_x) + ", " + std::to_string(m_y) + ")";
	}
}