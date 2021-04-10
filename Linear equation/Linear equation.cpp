#pragma once

// MADE BY TAE HWAN KIM, SHIN JAE HO
// ����ȯ, ����ȣ ����
// If you see this documents, you can learn & understand Faster.
// �ؿ� �ڷ���� ���ø�, ���� ������ ���� �����Ͻ� �� �����ǰ̴ϴ�.
// https://www.wikihow.com/Find-the-Inverse-of-a-3x3-Matrix
// https://www.wikihow.com/Find-the-Determinant-of-a-3X3-Matrix
// LAST UPDATE 2020 - 03 - 30
// ������ ������Ʈ 2020 - 03 - 30
// This is my Github Profile. You can use this source whenever you want. 
// �� ����� �������Դϴ�. �������� �� �ҽ��� ������ ���ŵ� �˴ϴ�.
// https://github.com/taehwan642 
// Thanks :)
// �����մϴ� :)

#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

typedef struct Matrix
{
public:
	int maxRow;
	int maxCol;
	vector<vector<float>> matrixdata;
	Matrix(int row, int col)
	{
		//matrixdata�� ���θ� num�� ������� �缳���ϸ�, 0���� �ʱ�ȭ��
		matrixdata.resize(col, vector<float>(row, 0));
		maxRow = row;
		maxCol = col;
	}
};

void getCofactor(const Matrix& A, Matrix& temp, int p, int q, int n) // ���μ��� ���ش��ִ� �Լ�!
{
	int i = 0, j = 0; // n - 1 X n - 1 ��Ŀ� ���� x, y��ǥ

	for (int row = 0; row < n; row++)
	{
		for (int col = 0; col < n; col++)
		{
			if (row != p && col != q) // �ϳ��� �ȵǸ� �ȵ�! && �̱⶧��
			{
				temp.matrixdata[i][j++] = A.matrixdata[row][col]; // j++ <- ��ó���� ���� Ǯ���, [i][j] �� ��, j++�Ѱſ� �Ȱ���

				if (j == n - 1) // 1���� �۰�, 3�����̸� 2���� ���μ� ���� ����� �����ϱ�
				{
					j = 0; // x��ǥ �ʱ�ȭ
					i++; // y��ǥ ++
				}
			}
		}
	}
}

int determinant(Matrix& A, int n)
{
	int D = 0;  // D = �� ����� Determinant��

	if (n == 2) // ��� ����
		return ((A.matrixdata[0][0] * A.matrixdata[1][1]) - (A.matrixdata[1][0] * A.matrixdata[0][1]));

	Matrix temp(A.maxRow - 1, A.maxCol - 1); // n X n ����� ���μ��� ���� �ӽ� ���

	int sign = 1;  // sign = +, -, +, -.... ���·� ���ӵǴ� ������� ������ �ִ� ����

	for (int f = 0; f < n; f++)
	{
		getCofactor(A, temp, 0, f, n);  // 0���� ������Ų ������, ���� ���� �� Determinant (��Ľ�)�� n���� �� �� �ƹ��ų� ��Ƶ� ������� ��� ��ġ�ϱ� ����
		D += sign * A.matrixdata[0][f] * determinant(temp, n - 1); // ��� �������� ���ư���. f�� n X n �� ���� n�� ���� ����.

		sign = -sign; // +, -, +, -... �������� �Ǳ� ������ �ݴ�� ������ش�.
	}

	return D; // �������� n X n ����� Determinant�� �������ش�.
}

void adjoint(Matrix& A, Matrix& adj) // �������, �������
{
	if (A.matrixdata.size() == 1) // ����ó��
	{
		adj.matrixdata[0][0] = 1;
		return;
	}

	int sign = 1;

	Matrix temp(A.maxRow, A.maxCol);

	for (int i = 0; i < A.matrixdata.size(); i++)
	{
		for (int j = 0; j < A.matrixdata.size(); j++)
		{
			getCofactor(A, temp, i, j, A.matrixdata.size()); // ���μ� ���ϱ�, �� i, j������ �Ǳ⿡ temp�� �׻� �ٲ��.

			sign = ((i + j) % 2 == 0) ? 1 : -1; // +, -, + �������� �Ǵµ�, 0,0 ��ǥ�� +, 0,1��ǥ�� -, �̷��� �ȴ�.

			adj.matrixdata[i][j] = (sign) * (determinant(temp, A.matrixdata.size() - 1)); // n - 1 X n - 1 ��, ������ �� ���μ� ��� �� ���μ��� ������ ����� ũ�� - 1 �̱� �����̴�.
		}
	}
}

bool inverse(Matrix& A, Matrix& inverse)
{
	int det = determinant(A, A.matrixdata.size()); // Determinant, ������� ��ų ����� ��Ľ��� ����

	if (det == 0) // 0�϶��� ����ó�� (������� ���� �� ���� ����.)
	{
		cout << "Singular matrix, can't find its inverse";
		return false;
	}

	Matrix adj(A.maxRow, A.maxCol); // ������� ����

	adjoint(A, adj); // ������� �ʱ�ȭ

	for (int i = 0; i < A.matrixdata.size(); i++)
		for (int j = 0; j < A.matrixdata.size(); j++)
			inverse.matrixdata[i][j] = adj.matrixdata[i][j] / float(det); // �� ����� ���ҵ��� ������ ���� �����Ѵ�.
	// ������� ���� -> ����� = 1 / ��Ľ� * �������
	// �����[i][j]��° ���� = �������[i][j]��° ���� / ��Ľ�
	return true;
}

void display(Matrix A)
{
	for (int i = 0; i < A.matrixdata.size(); i++)
	{
		for (int j = 0; j < A.matrixdata.size(); j++)
			cout << A.matrixdata[i][j] << " ";
		cout << endl;
	}
}

int main(void)
{
	Matrix A(3, 3);
	A.matrixdata =
	{
		{1, 0, 5},
		{2, 1, 6},
		{3, 4, 0}
	};

	Matrix adj(3, 3);

	Matrix inv(3, 3);

	if (inverse(A, inv))
		display(inv);
}