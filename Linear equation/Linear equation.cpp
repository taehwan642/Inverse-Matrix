#pragma once

// MADE BY TAE HWAN KIM, SHIN JAE HO
// 김태환, 신재호 제작
// If you see this documents, you can learn & understand Faster.
// 밑에 자료들을 보시면, 더욱 빠르게 배우고 이해하실 수 있으실겁니다.
// https://www.wikihow.com/Find-the-Inverse-of-a-3x3-Matrix
// https://www.wikihow.com/Find-the-Determinant-of-a-3X3-Matrix
// LAST UPDATE 2020 - 03 - 30
// 마지막 업데이트 2020 - 03 - 30
// This is my Github Profile. You can use this source whenever you want. 
// 제 깃허브 페이지입니다. 언제든지 이 소스를 가져다 쓰셔도 됩니다.
// https://github.com/taehwan642 
// Thanks :)
// 감사합니다 :)

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
		//matrixdata의 내부를 num의 사이즈로 재설정하며, 0으로 초기화함
		matrixdata.resize(col, vector<float>(row, 0));
		maxRow = row;
		maxCol = col;
	}
};

void getCofactor(const Matrix& A, Matrix& temp, int p, int q, int n) // 여인수를 구해다주는 함수!
{
	int i = 0, j = 0; // n - 1 X n - 1 행렬에 넣을 x, y좌표

	for (int row = 0; row < n; row++)
	{
		for (int col = 0; col < n; col++)
		{
			if (row != p && col != q) // 하나라도 안되면 안들어감! && 이기때문
			{
				temp.matrixdata[i][j++] = A.matrixdata[row][col]; // j++ <- 후처리로 따로 풀어보면, [i][j] 한 뒤, j++한거와 똑같음

				if (j == n - 1) // 1차원 작게, 3차원이면 2차원 여인수 모음 행렬이 나오니까
				{
					j = 0; // x좌표 초기화
					i++; // y좌표 ++
				}
			}
		}
	}
}

int determinant(Matrix& A, int n)
{
	int D = 0;  // D = 한 행렬의 Determinant값

	if (n == 2) // 계산 압축
		return ((A.matrixdata[0][0] * A.matrixdata[1][1]) - (A.matrixdata[1][0] * A.matrixdata[0][1]));

	Matrix temp(A.maxRow - 1, A.maxCol - 1); // n X n 행렬의 여인수를 담을 임시 행렬

	int sign = 1;  // sign = +, -, +, -.... 형태로 지속되는 결과값에 영향을 주는 정수

	for (int f = 0; f < n; f++)
	{
		getCofactor(A, temp, 0, f, n);  // 0으로 고정시킨 이유는, 수학 공식 상 Determinant (행렬식)은 n개의 열 중 아무거나 잡아도 결과값은 모두 일치하기 때문
		D += sign * A.matrixdata[0][f] * determinant(temp, n - 1); // 재귀 형식으로 돌아간다. f는 n X n 중 정수 n을 향해 간다.

		sign = -sign; // +, -, +, -... 형식으로 되기 때문에 반대로 만들어준다.
	}

	return D; // 마지막엔 n X n 행렬의 Determinant를 리턴해준다.
}

void adjoint(Matrix& A, Matrix& adj) // 딸림행렬, 수반행렬
{
	if (A.matrixdata.size() == 1) // 예외처리
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
			getCofactor(A, temp, i, j, A.matrixdata.size()); // 여인수 구하기, 단 i, j값으로 되기에 temp는 항상 바뀐다.

			sign = ((i + j) % 2 == 0) ? 1 : -1; // +, -, + 형식으로 되는데, 0,0 좌표면 +, 0,1좌표면 -, 이렇게 된다.

			adj.matrixdata[i][j] = (sign) * (determinant(temp, A.matrixdata.size() - 1)); // n - 1 X n - 1 은, 언제나 각 여인수 행렬 은 여인수를 따오는 행렬의 크기 - 1 이기 때문이다.
		}
	}
}

bool inverse(Matrix& A, Matrix& inverse)
{
	int det = determinant(A, A.matrixdata.size()); // Determinant, 역행렬을 시킬 행렬의 행렬식을 구함

	if (det == 0) // 0일때는 예외처리 (역행렬을 구할 수 없기 때문.)
	{
		cout << "Singular matrix, can't find its inverse";
		return false;
	}

	Matrix adj(A.maxRow, A.maxCol); // 딸림행렬 선언

	adjoint(A, adj); // 딸림행렬 초기화

	for (int i = 0; i < A.matrixdata.size(); i++)
		for (int j = 0; j < A.matrixdata.size(); j++)
			inverse.matrixdata[i][j] = adj.matrixdata[i][j] / float(det); // 각 행렬의 원소들을 조합해 값을 도출한다.
	// 역행렬의 공식 -> 역행렬 = 1 / 행렬식 * 딸림행렬
	// 역행렬[i][j]번째 원소 = 딸림행렬[i][j]번째 원소 / 행렬식
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