#pragma once
#pragma once
#include <string>

namespace TE
{
	class Vector3
	{
	public:
		explicit Vector3(float x = 0, float y = 0, float z = 0);
		Vector3(Vector3 const & v);
		~Vector3();
		float GetX() const { return m_x; }
		float GetY() const { return m_y; }
		float GetZ() const { return m_z; }
		void SetX(float x) { m_x = x; }
		void SetY(float y) { m_y = y; }
		void SetZ(float z) { m_z = z; }

		inline float Lenght() const;
		float Dot(Vector3 const & v) const;
		Vector3 Normalize();
		Vector3 Rotate(float angle);
		Vector3 Cross(Vector3 v);

		Vector3 Add(Vector3 v);
		Vector3 Add(float x, float y, float z);
		Vector3 Add(float value);

		Vector3 Sub(Vector3 v);
		Vector3 Sub(float x, float y, float z);
		Vector3 Sub(float value);

		Vector3 Mult(Vector3 v);
		Vector3 Mult(float x, float y, float z);
		Vector3 Mult(float value);

		Vector3 Div(Vector3 v);
		Vector3 Div(float x, float y, float z);
		Vector3 Div(float value);


		std::string ToString() const;

	private:
		float m_x;
		float m_y;
		float m_z;
	};

}