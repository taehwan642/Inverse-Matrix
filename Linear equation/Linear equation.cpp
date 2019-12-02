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
	vector<vector<double>> matrixdata;
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
		if (rownum > maxrow || colnum > maxcol || rownum < 0 || colnum < 0)
		{
			cout << "NO! " << data << endl;
			return;
		}

		matrixdata[colnum][rownum] = data;
	}

	void InputMatrix2(int rownum, int colnum, int data)
	{
		//rownum이 맥스보다 더 작아질시에도 리턴해야함
		if (rownum > maxrow || colnum > maxcol || rownum <= 0 || colnum <= 0)
		{
			cout << "NO! " << data << endl;
			return;
		}

		matrixdata[colnum-1][rownum-1] = data;
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
	Manager MNG;
	//입력값 받아와야함
	cout << "★행렬의 곱셈 프로그램★" << endl << endl;

	cout << "★행렬이 자동으로 2개 만들어질거라구~!★" << endl << endl;
	cout << "★2번째 행렬의 행의 크기를 입력하라구~!★" << endl;

	int hang = 0, yull = 0;

	cin >> hang;
	cout << "★1번째 행렬의 열의 크기를 입력하라구~!★" << endl;

	cin >> yull;
	
	Matrix* matrix1 = new Matrix(yull, hang);

	cout << "★행렬의 원소를 1,1 부터 1,2 순서대로 너가 입력한 크기만큼까지 입력할거라구~!★" << endl;
	int inputdata = 0;
	
	for (int i = 0; i < yull ; i++)
	{
		for (int j = 0; j < hang; j++)
		{
			cin >> inputdata;
			matrix1->InputMatrix(i, j, inputdata);
			cout << endl;
			matrix1->OuptPutAll();
		}
	}
	cout << "★다 했니? 이제 2번째 행렬의 행을 넣으라구~★" << endl;

	int hang2 = 0, yull2 = 0;
	cin >> hang2;
	cout << "★이제 2번째 행렬의 열을 넣으라구~★" << endl;
	cin >> yull2;
	Matrix* matrix2 = new Matrix(yull2, hang2);

	cout << "★행렬의 원소를 1,1 부터 1,2 순서대로 너가 입력한 크기만큼까지 입력할거라구~!★" << endl;


	int inputdata2 = 0;
	for (int i = 0; i < yull2; i++)
	{
		for (int j = 0; j < hang2; j++)
		{
			cin >> inputdata2;
			matrix2->InputMatrix(i, j, inputdata2);
			cout << endl;
			matrix2->OuptPutAll();
		}
	}

	cout << endl << endl;

	cout << "★두 행렬의 곱한 값은!★" << endl << endl;

	Matrix* result = new Matrix(yull2 , hang);

	result = MNG.MatrixMultiply(result, matrix1, matrix2);

	result->OuptPutAll();

	/*Matrix* mat = new Matrix(2, 3);
	mat->InputMatrix2(1, 1, 1);
	mat->InputMatrix2(1, 2, 2);
	mat->InputMatrix2(1, 3, 3);
	mat->InputMatrix2(2, 1, 4);
	mat->InputMatrix2(2, 2, 5);
	mat->InputMatrix2(2, 3, 6);
	Matrix* mat2 = new Matrix(3, 2);
	mat2->InputMatrix2(1, 1, 1);
	mat2->InputMatrix2(1, 2, 2);
	mat2->InputMatrix2(2, 1, 3);
	mat2->InputMatrix2(2, 2, 4);
	mat2->InputMatrix2(3, 1, 5);
	mat2->InputMatrix2(3, 2, 6);
	mat->OuptPutAll();
	mat2->OuptPutAll();
	Matrix* result = new Matrix(3, 3);
	result = MNG.MatrixMultiply(result, mat, mat2);
	result->OuptPutAll();
	MNG.MatrixTranspos(result);
	result->OuptPutAll();*/
	return 0;
}