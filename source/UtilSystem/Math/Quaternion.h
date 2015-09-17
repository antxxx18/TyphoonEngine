#pragma once

#include "TEMath.h"

namespace TE
{
	class Quaternion
	{
	public:
		Quaternion(float x, float y, float z, float w);
		~Quaternion();

		inline float Length() const;
		Quaternion Normalize();
		Quaternion Conjugate() const;

		Quaternion Mult(Quaternion const & q);
		Quaternion Mult(Vector3 const & v);

		float GetX() const { return m_x; }
		float GetY() const { return m_y; }
		float GetZ() const { return m_z; }
		float GetW() const { return m_w; }

		void SetX(float x) { m_x = x; }
		void SetY(float y) { m_y = y; }
		void SetZ(float z) { m_z = z; }
		void SetW(float w) { m_w = w; }

	private:
		float m_x;
		float m_y;
		float m_z;
		float m_w;
	};
}
