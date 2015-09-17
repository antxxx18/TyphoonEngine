#include "stdafx.h"
#include "Matrix.h"

namespace TE
{
	Matrix::Matrix()
	{}


	Matrix::~Matrix()
	{}

	Matrix Matrix::InitIdentity()
	{
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				if (i == j)
					m_matrix[i][i] = 1;
				else
					m_matrix[i][i] = 0;
			}
		}

		return *this;
	}

	Matrix Matrix::Transpose(Matrix m)
	{
		for (int i = 0; i < 4; ++i)
			for (int j = 0; j < 4; ++j)
				m_matrix[i][j] = m.m_matrix[i][j];

		return *this;
	}

	Matrix Matrix::Mult(Matrix m)
	{
		Matrix res;

		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{	
				float temp = 0;
				for (int k = 0; k < 4; ++k)
				{
					temp += m_matrix[i][k] * m.Get(k, j);
				}
				res.Set(i, j, temp);
			}
		}

		return res;
	}
}