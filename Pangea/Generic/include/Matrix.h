/*
 * Matrix.h
 *
 *  Created on: Jan 30, 2011
 *      Author: mmerchan
 */

#include "precision.h"
#include "Vector3.h"
#include <math.h>
#include <stdlib.h>

#ifndef MATRIX_H_
#define MATRIX_H_

class Matrix {

	private:

		real ** mat;
		int cols, rows;

		void allocateMatrix(int rows, int cols) {

			// Allocate
			mat = new real*[rows];
			for (int i = 0; i < rows; i++)
				mat[i] = new real[cols];

			// Initialize
			for (int i = 0; i < rows; i++)
				for (int j = 0; j < cols; j++)
					mat[i][j] = 0;
		}

	public:

		Matrix(int rows, int cols) {
			mat = NULL;
			allocateMatrix(rows, cols);
			this->cols = cols;
			this->rows = rows;
		}

		real * operator[](int pos) {
			return mat[pos];
		}

		// Matrix3 - Vector3 multiplication.
		Vector3 operator*(const Vector3& v) {

			if (rows != 3)
				return Vector3();

			Matrix tmp(3, 1);
			tmp[0][0] = v.getX();
			tmp[1][0] = v.getY();
			tmp[2][0] = v.getZ();

			Matrix out = (*this) * tmp;

			return Vector3(out[0][0], out[1][0], out[2][0]);
		}

		// Matrix - Matrix multiplication.
		// Dimensions must be adecuate (this.rows = other.cols)
		Matrix operator*(const Matrix& other) {

			if (this->cols != other.rows)
				return Matrix(1, 1);

			Matrix out(this->rows, other.cols);

			float p = cols;

			for (int i = 0; i < rows; i++)
				for (int j = 0; j < other.cols; j++)

					for (int k = 0; k < p; k++)
						out[i][j] += mat[i][k] * other.get(k, j);

			return out;
		}

		void set(int row, int col, real value) {
			mat[row][col] = value;
		}

		real get(int row, int col) const {
			return mat[row][col];
		}
/*
		void print() {
			for (int j = 0; j < rows; j++) {
				printf("[ ");
				for (int i = 0; i < cols; i++)
					printf("%.2f ", mat[j][i]);
				printf("]\n");
			}
		}*/

		static Matrix getIdentity(int dim) {
			Matrix out(dim, dim);

			for (int i = 0; i < dim; i++)
				out[i][i] = 1;

			return out;
		}

		static Matrix getRotationMatrix(real xr, real yr, real zr) {

			Matrix xMat = Matrix::getIdentity(3);
			Matrix yMat = Matrix::getIdentity(3);
			Matrix zMat = Matrix::getIdentity(3);

			xMat[1][1] = cos(xr);
			xMat[1][2] = sin(xr);
			xMat[2][1] = -sin(xr);
			xMat[2][2] = cos(xr);

			yMat[0][0] = cos(yr);
			yMat[0][2] = -sin(yr);
			yMat[2][0] = sin(yr);
			yMat[2][2] = cos(yr);

			zMat[0][0] = cos(zr);
			zMat[0][1] = sin(zr);
			zMat[1][0] = -sin(zr);
			zMat[1][1] = cos(zr);

			return xMat * (yMat * zMat);
		}

		// TODO DEALLOCATE EVERYTHING!
		~Matrix() {

		}
};

#endif /* MATRIX_H_ */
