#pragma once
#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std;
struct Matrix
{
public:
	int maxrow;
	int maxcol;
	vector<vector<double>> matrixdata ;
	Matrix(int row, int col)
	{
		//matrixdata의 내부를 num의 사이즈로 재설정하며, 0으로 초기화함
		matrixdata.resize(col, vector<double>(row, 0));
		maxrow = row;
		maxcol = col;
	}

	void OutputMatrix(int rownum, int colnum)
	{
		if (rownum > maxrow || colnum > maxcol)
			return;
		for (int i = 0; i < maxrow; i++)
		{
			for (int j = 0; j < maxcol; j++)
			{
				if (rownum - 1 == i && colnum - 1 == j)
					cout << matrixdata[i][j];
			}
			cout << "\n";
		}
	}

	void InputMatrix(int rownum, int colnum, int data)
	{
		//rownum이 맥스보다 더 작아질시에도 리턴해야함
		if (rownum > maxrow || colnum > maxcol || rownum <= 0 || colnum <= 0)
		{
			cout << "NO! " << data << endl;
			return;
		}

		matrixdata[colnum - 1][rownum - 1] = data;
	}

	void OuptPutAll()
	{
		for (int i = 0; i < maxrow; i++)
		{
			for (int j = 0; j < maxcol; j++)
			{
				cout << matrixdata[j][i] << " ";
			}
			cout << endl;
			cout << endl;
		}
		cout << endl;
		cout << endl;
		cout << endl;
	}
};
struct Manager
{
	Matrix* MatrixMultiply(Matrix* out, Matrix* a, Matrix* b)
	{
		if (a->maxcol != b->maxrow)
		{
			cout << "NO MATCH!" << endl;
		}

		for (int i = 0; i < a->maxcol; i++)
		{
			for (int j = 0; j < b->maxrow; j++)
			{
				double t = 0;
				for (int k = 0; k < b->maxcol; k++)
				{
					t = t + a->matrixdata[j][k] * b->matrixdata[k][i];
					//cout << i << " " << j << " " << k << " " << t << " " << endl;
				}
				out->matrixdata[j][i] = t;
			}
		}

		return out;
	}

	Matrix* MatrixTranspos(Matrix* out)
	{
		Matrix* tempMatrix = new Matrix(out->maxrow, out->maxcol);
		for (int i = 0; i < tempMatrix->maxrow; i++)
		{
			for (int j = 0; j < tempMatrix->maxcol; j++)
			{
				tempMatrix->matrixdata[i][j] = out->matrixdata[i][j];
			}
		}
		for (int i = 0; i < tempMatrix->maxrow; i++)
		{
			for (int j = 0; j < tempMatrix->maxcol; j++)
			{
				out->matrixdata[j][i] = tempMatrix->matrixdata[i][j];
			}
		}

		return out;
	}

	Matrix* MatrixInverse(Matrix* out)
	{

		return out;
	}
};



int main(void)
{
	//입력값 받아와야함
	Manager MNG;
	Matrix * mat = new Matrix(2,3);
	mat->InputMatrix(1, 1, 1);
	mat->InputMatrix(1, 2, 2);
	mat->InputMatrix(1, 3, 3);
	mat->InputMatrix(2, 1, 4);
	mat->InputMatrix(2, 2, 5);
	mat->InputMatrix(2, 3, 6);
	Matrix* mat2 = new Matrix(3, 2);
	mat2->InputMatrix(1, 1, 1);
	mat2->InputMatrix(1, 2, 2);
	mat2->InputMatrix(2, 1, 3);
	mat2->InputMatrix(2, 2, 4);
	mat2->InputMatrix(3, 1, 5);
	mat2->InputMatrix(3, 2, 6);
	mat->OuptPutAll();
	mat2->OuptPutAll();
	Matrix* result = new Matrix(3, 3);
	result = MNG.MatrixMultiply(result, mat, mat2);
	result->OuptPutAll();
	MNG.MatrixTranspos(result);
	result->OuptPutAll();
	return 0;
}