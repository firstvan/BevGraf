#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>

template<int N, int M, typename T>
class Matrix{
	T matrix[N][M];

public:

	Matrix() {}






	/*
	Matrix(const T * v)
	{
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < M; j++)
			{
				matrix[i][j] = v[i * N + j];
			}
		}
	}*/


	T getElement(int row, int column){
		if (row >= 0 && row < M && column >= 0 && column < N)
			return matrix[column][row];
		else
			return matrix[0][0];
	}

	void setElement(int row, int column, T value)
	{
		if (row >= 0 && row < M && column >= 0 && column < N)
			matrix[column][row] = value;
		else
			matrix[0][0] = value;
	}

	void kiir()
	{
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < M; j++)
			{
				std::cout << matrix[i][j] << ", ";
			}
			std::cout << std::endl;
		}
		
	}


	Matrix<N, M, T>& operator*=(T skalar)
	{
		for (int i = 0; i < M; i++)
		{
			for  (int j = 0; j < N; j++)
			{
				matrix[j][i] *= skalar;
			}

		}
		return *this;
	}

	template<int NN, int M1, int M2, typename TT>
	friend Matrix<M1, M2, TT> operator*(const Matrix<NN, M2, TT>& m1,
		const Matrix<M1, NN, TT>& m2);

	// 4x4 only
	Matrix<N, M, T> inverse()
	{
		Matrix<N, M, T> inv;
		inv.matrix[0][0] = matrix[1][1] * matrix[2][2] * matrix[3][3] -
			matrix[1][1] * matrix[3][2] * matrix[2][3] -
			matrix[1][2] * matrix[2][1] * matrix[3][3] +
			matrix[1][2] * matrix[3][1] * matrix[2][3] +
			matrix[1][3] * matrix[2][1] * matrix[3][2] -
			matrix[1][3] * matrix[3][1] * matrix[2][2];

		inv.matrix[0][1] = -matrix[0][1] * matrix[2][2] * matrix[3][3] +
			matrix[0][1] * matrix[3][2] * matrix[2][3] +
			matrix[0][2] * matrix[2][1] * matrix[3][3] -
			matrix[0][2] * matrix[3][1] * matrix[2][3] -
			matrix[0][3] * matrix[2][1] * matrix[3][2] +
			matrix[0][3] * matrix[3][1] * matrix[2][2];

		inv.matrix[0][2] = matrix[0][1] * matrix[1][2] * matrix[3][3] -
			matrix[0][1] * matrix[3][2] * matrix[1][3] -
			matrix[0][2] * matrix[1][1] * matrix[3][3] +
			matrix[0][2] * matrix[3][1] * matrix[1][3] +
			matrix[0][3] * matrix[1][1] * matrix[3][2] -
			matrix[0][3] * matrix[3][1] * matrix[1][2];

		inv.matrix[0][3] = -matrix[0][1] * matrix[1][2] * matrix[2][3] +
			matrix[0][1] * matrix[2][2] * matrix[1][3] +
			matrix[0][2] * matrix[1][1] * matrix[2][3] -
			matrix[0][2] * matrix[2][1] * matrix[1][3] -
			matrix[0][3] * matrix[1][1] * matrix[2][2] +
			matrix[0][3] * matrix[2][1] * matrix[1][2];

		inv.matrix[1][0] = -matrix[1][0] * matrix[2][2] * matrix[3][3] +
			matrix[1][0] * matrix[3][2] * matrix[2][3] +
			matrix[1][2] * matrix[2][0] * matrix[3][3] -
			matrix[1][2] * matrix[3][0] * matrix[2][3] -
			matrix[1][3] * matrix[2][0] * matrix[3][2] +
			matrix[1][3] * matrix[3][0] * matrix[2][2];

		inv.matrix[1][1] = matrix[0][0] * matrix[2][2] * matrix[3][3] -
			matrix[0][0] * matrix[3][2] * matrix[2][3] -
			matrix[0][2] * matrix[2][0] * matrix[3][3] +
			matrix[0][2] * matrix[3][0] * matrix[2][3] +
			matrix[0][3] * matrix[2][0] * matrix[3][2] -
			matrix[0][3] * matrix[3][0] * matrix[2][2];

		inv.matrix[1][2] = -matrix[0][0] * matrix[1][2] * matrix[3][3] +
			matrix[0][0] * matrix[3][2] * matrix[1][3] +
			matrix[0][2] * matrix[1][0] * matrix[3][3] -
			matrix[0][2] * matrix[3][0] * matrix[1][3] -
			matrix[0][3] * matrix[1][0] * matrix[3][2] +
			matrix[0][3] * matrix[3][0] * matrix[1][2];

		inv.matrix[1][3] = matrix[0][0] * matrix[1][2] * matrix[2][3] -
			matrix[0][0] * matrix[2][2] * matrix[1][3] -
			matrix[0][2] * matrix[1][0] * matrix[2][3] +
			matrix[0][2] * matrix[2][0] * matrix[1][3] +
			matrix[0][3] * matrix[1][0] * matrix[2][2] -
			matrix[0][3] * matrix[2][0] * matrix[1][2];

		inv.matrix[2][0] = matrix[1][0] * matrix[2][1] * matrix[3][3] -
			matrix[1][0] * matrix[3][1] * matrix[2][3] -
			matrix[1][1] * matrix[2][0] * matrix[3][3] +
			matrix[1][1] * matrix[3][0] * matrix[2][3] +
			matrix[1][3] * matrix[2][0] * matrix[3][1] -
			matrix[1][3] * matrix[3][0] * matrix[2][1];

		inv.matrix[2][1] = -matrix[0][0] * matrix[2][1] * matrix[3][3] +
			matrix[0][0] * matrix[3][1] * matrix[2][3] +
			matrix[0][1] * matrix[2][0] * matrix[3][3] -
			matrix[0][1] * matrix[3][0] * matrix[2][3] -
			matrix[0][3] * matrix[2][0] * matrix[3][1] +
			matrix[0][3] * matrix[3][0] * matrix[2][1];

		inv.matrix[2][2] = matrix[0][0] * matrix[1][1] * matrix[3][3] -
			matrix[0][0] * matrix[3][1] * matrix[1][3] -
			matrix[0][1] * matrix[1][0] * matrix[3][3] +
			matrix[0][1] * matrix[3][0] * matrix[1][3] +
			matrix[0][3] * matrix[1][0] * matrix[3][1] -
			matrix[0][3] * matrix[3][0] * matrix[1][1];

		inv.matrix[2][3] = -matrix[0][0] * matrix[1][1] * matrix[2][3] +
			matrix[0][0] * matrix[2][1] * matrix[1][3] +
			matrix[0][1] * matrix[1][0] * matrix[2][3] -
			matrix[0][1] * matrix[2][0] * matrix[1][3] -
			matrix[0][3] * matrix[1][0] * matrix[2][1] +
			matrix[0][3] * matrix[2][0] * matrix[1][1];

		inv.matrix[3][0] = -matrix[1][0] * matrix[2][1] * matrix[3][2] +
			matrix[1][0] * matrix[3][1] * matrix[2][2] +
			matrix[1][1] * matrix[2][0] * matrix[3][2] -
			matrix[1][1] * matrix[3][0] * matrix[2][2] -
			matrix[1][2] * matrix[2][0] * matrix[3][1] +
			matrix[1][2] * matrix[3][0] * matrix[2][1];

		inv.matrix[3][1] = matrix[0][0] * matrix[2][1] * matrix[3][2] -
			matrix[0][0] * matrix[3][1] * matrix[2][2] -
			matrix[0][1] * matrix[2][0] * matrix[3][2] +
			matrix[0][1] * matrix[3][0] * matrix[2][2] +
			matrix[0][2] * matrix[2][0] * matrix[3][1] -
			matrix[0][2] * matrix[3][0] * matrix[2][1];

		inv.matrix[3][2] = -matrix[0][0] * matrix[1][1] * matrix[3][2] +
			matrix[0][0] * matrix[3][1] * matrix[1][2] +
			matrix[0][1] * matrix[1][0] * matrix[3][2] -
			matrix[0][1] * matrix[3][0] * matrix[1][2] -
			matrix[0][2] * matrix[1][0] * matrix[3][1] +
			matrix[0][2] * matrix[3][0] * matrix[1][1];

		inv.matrix[3][3] = matrix[0][0] * matrix[1][1] * matrix[2][2] -
			matrix[0][0] * matrix[2][1] * matrix[1][2] -
			matrix[0][1] * matrix[1][0] * matrix[2][2] +
			matrix[0][1] * matrix[2][0] * matrix[1][2] +
			matrix[0][2] * matrix[1][0] * matrix[2][1] -
			matrix[0][2] * matrix[2][0] * matrix[1][1];

		T det = matrix[0][0] * inv.matrix[0][0] +
			matrix[1][0] * inv.matrix[0][1] +
			matrix[2][0] * inv.matrix[0][2] +
			matrix[3][0] * inv.matrix[0][3];

		det = 1.0f / det;

		inv *= det;
		return inv;
	}

}; // end class Matrix

template <int N, int M1, int M2, typename T>
Matrix<M1, M2, T> operator*(const Matrix<N, M2, T>& m1,
	const Matrix<M1, N, T>& m2)
{
	Matrix<M1, M2, T> result;

	for (int row = 0; row < M2; ++row)
	{
		for (int col = 0; col < M1; ++col)
		{
			T sum(0.0f);

			for (int j = 0; j < N; ++j)
				sum += m1.matrix[j][row] * m2.matrix[col][j];

			result.matrix[col][row] = sum;
		}
	}

	return result;
}


#endif