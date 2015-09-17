#pragma once

namespace TE
{
	class Matrix
	{
	public:
		Matrix();
		~Matrix();
		float Get(int x, int y) const { return m_matrix[x][y]; }
		void Set(int x, int y, float value) { m_matrix[x][y] = value; }
		Matrix InitIdentity();
		Matrix Transpose(Matrix m);
		Matrix Mult(Matrix m);


	private:
		float m_matrix[4][4];
	};
}