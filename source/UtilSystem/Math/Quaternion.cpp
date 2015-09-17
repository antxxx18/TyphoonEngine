#include "stdafx.h"
#include "Quaternion.h"

namespace TE
{
	Quaternion::Quaternion(float x, float y, float z, float w)
	{
		m_x = x;
		m_y = y;
		m_z = z;
		m_w = w;
	}


	Quaternion::~Quaternion()
	{}

	inline float Quaternion::Length() const
	{
		return sqrtf(m_x*m_x + m_y*m_y + m_z*m_z + m_w*m_w);
	}

	Quaternion Quaternion::Normalize()
	{
		float length = Length();

		m_x /= length;
		m_y /= length;
		m_z /= length;
		m_w /= length;

		return *this;
	}

	Quaternion Quaternion::Conjugate() const
	{
		return Quaternion(-m_x, -m_y, -m_z, m_w);
	}

	Quaternion Quaternion::Mult(Quaternion const & q)
	{
		float w = m_w * q.GetW() - m_x * q.GetX() - m_y * q.GetY() - m_z * q.GetZ();
		float x = m_x * q.GetW() + m_w * q.GetX() + m_y * q.GetZ() - m_z * q.GetY();
		float y = m_y * q.GetW() + m_w * q.GetY() + m_z * q.GetX() - m_x * q.GetZ();
		float z = m_z * q.GetW() + m_w * q.GetZ() + m_x * q.GetY() - m_y * q.GetX();
		m_x = x;
		m_y = y;
		m_z = z;
		m_w = w;
		return Quaternion(x, y, z, w);
	}

	Quaternion Quaternion::Mult(Vector3 const & v)
	{
		float w = -m_x * v.GetX() - m_y * v.GetY() - m_z * v.GetZ();
		float x =  m_w * v.GetX() + m_y * v.GetZ() - m_z * v.GetY();
		float y =  m_w * v.GetY() + m_z * v.GetX() - m_x * v.GetZ();
		float z =  m_w * v.GetZ() + m_x * v.GetY() - m_y * v.GetX();
		m_x = x;
		m_y = y;
		m_z = z;
		m_w = w;
		return Quaternion(x, y, z, w);
	}
}