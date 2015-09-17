#include "stdafx.h"
#include "Vector3.h"
#include <cmath>
#include "TEMath.h"

namespace TE
{
	Vector3::Vector3(float x, float y, float z)
	{
		m_x = x;
		m_y = y;
		m_z = z;
	}


	Vector3::Vector3(Vector3 const & v)
	{
		Vector3(v.GetX(), v.GetY(), v.GetZ());
	}

	Vector3::~Vector3()
	{}

	inline float Vector3::Lenght() const
	{
		return sqrtf(m_x*m_x + m_y*m_y + m_z*m_z);
	}

	float Vector3::Dot(Vector3 const & v) const
	{
		return m_x*v.GetX() + m_y*v.GetY() + m_z*GetZ();
	}

	Vector3 Vector3::Normalize()
	{
		float length = Lenght();

		m_x /= length;
		m_y /= length;
		m_z /= length;

		return *this;
	}
	//
	//
	//Vector3 Vector3::Rotate(float angle)
	//{
	//	//return nullptr;
	//}

	Vector3 Vector3::Cross(Vector3 v)
	{
		float x = m_y * v.GetZ() - m_z * v.GetY();
		float y = m_z * v.GetZ() - m_x * v.GetZ();
		float z = m_x * v.GetY() - m_y * v.GetX();

		return *(new Vector3(x, y, z));
	}

	Vector3 Vector3::Add(Vector3 v)
	{
		m_x += v.GetX();
		m_y += v.GetY();
		m_z += v.GetZ();

		return *this;
	}

	Vector3 Vector3::Add(float x, float y, float z)
	{
		m_x += x;
		m_y += y;
		m_z += z;

		return *this;
	}

	Vector3 Vector3::Add(float value)
	{
		m_x += value;
		m_y += value;
		m_z += value;

		return *this;
	}

	Vector3 Vector3::Sub(Vector3 v)
	{
		m_x -= v.GetX();
		m_y -= v.GetY();
		m_z -= v.GetZ();

		return *this;
	}

	Vector3 Vector3::Sub(float x, float y, float z)
	{
		m_x -= x;
		m_y -= y;
		m_z -= z;

		return *this;
	}

	Vector3 Vector3::Sub(float value)
	{
		m_x -= value;
		m_y -= value;
		m_z -= value;

		return *this;
	}

	Vector3 Vector3::Mult(Vector3 v)
	{
		m_x *= v.GetX();
		m_y *= v.GetY();
		m_z *= v.GetZ();

		return *this;
	}

	Vector3 Vector3::Mult(float x, float y, float z)
	{
		m_x *= x;
		m_y *= y;
		m_z *= z;

		return *this;
	}

	Vector3 Vector3::Mult(float value)
	{
		m_x *= value;
		m_y *= value;
		m_z *= value;

		return *this;
	}

	Vector3 Vector3::Div(Vector3 v)
	{
		m_x /= v.GetX();
		m_y /= v.GetY();
		m_z /= v.GetZ();

		return *this;
	}

	Vector3 Vector3::Div(float x, float y, float z)
	{
		m_x /= x;
		m_y /= y;
		m_z /= z;

		return *this;
	}

	Vector3 Vector3::Div(float value)
	{
		m_x /= value;
		m_y /= value;
		m_z /= value;

		return *this;
	}

	std::string Vector3::ToString() const
	{
		return "(" + std::to_string(m_x) + ", " + std::to_string(m_y) + ", " + std::to_string(m_z) + ")";
	}
}