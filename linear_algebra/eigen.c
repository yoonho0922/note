#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define MAX 5

//선형방정식의 행렬 배열 구조체 선언 
typedef struct matrix {
	double a[MAX][MAX];
}matrix;

//고유값과 고유값 수를 저장하는 구조체 선언
typedef struct eigenvalue {
	int cnt;	//고유값의 개수
	int e[MAX];	//고유값을 저장할 배열
}eigenvalue;

int error;

eigenvalue eigen(matrix a, int n);	//고유값 계산 함수
matrix eigensub(matrix a, int n, int e);	//고유값을 받아서 행렬에서 고유값을 뺀 행렬을 반환하는 함수
void printout(matrix a, int n);	//연산 결과 출력 함수
void gauss(matrix a, int n);		//가우스 소거법 계산 함수
void backsub(matrix a, int n);	//역대입법 계산함수

//고유값 계산
eigenvalue eigen(matrix a, int n) {
	int i = -50;
	int det = 0;
	eigenvalue e;
	e.cnt = 0;

	//2*2행렬의 고유값 구하기
	if (n == 2) {

		while (i < 50 && e.cnt < 2) {
			det = (a.a[0][0] - i) * (a.a[1][1] - i) - a.a[0][1] * a.a[1][0];
			//printf(" %d, %d, %d |", i, det, e.cnt);
			if (det == 0) {
				e.e[e.cnt] = i;
				e.cnt++;
			}
			i++;
		}
	}//3*3행렬의 고유값 구하기
	else if (n == 3) {

		while (i < 50 && e.cnt < 3) {
			det = (a.a[0][0] - i) * ((a.a[1][1] - i) * (a.a[2][2] - i) - a.a[1][2] * a.a[2][1])
				- (a.a[0][1]) * (a.a[1][0] * (a.a[2][2] - i) - a.a[1][2] * a.a[2][0])
				+ (a.a[0][2]) * (a.a[1][0] * a.a[2][1] - (a.a[1][1] - i) * a.a[2][0]);
			if (det == 0) {
				e.e[e.cnt] = i;
				e.cnt++;
			}
			i++;
		}
	}
	if (e.cnt == 0) {
		printf("고유값이 존재하지 않습니다!!\n\n");
		return e;
	}
	printf(" 고유값 : ");
	for (int j = 0; j < e.cnt; j++)
		printf("%d%s ", e.e[j], j + 1 == e.cnt ? "" : ",");
	printf("\n\n");
	return e;
}

//고유값을 뺀 행렬 반환
matrix eigensub(matrix a, int n, int e) {
	matrix b;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i == j)
				b.a[i][j] = a.a[i][j] - e;
			else
				b.a[i][j] = a.a[i][j];
		}
	}
	return b;
}



//이 밑은 가우스-조단 소거법의 응용

//연산결과를 출력
void printout(matrix a, int n) {
	int i = 0, j = 0;

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {

			printf(" %.3lf\t", a.a[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

// 입력받은 선형 방정식을 가우스 소거법으로 계산
void gauss(matrix a, int n) {
	int i = 0, j = 0, k = 0, l = 0;
	double multi = 0, temp = 0;

	error = 0;
	k = 0;

	while (k < n && error != 1) {
		l = k;
		for (j = k + 1; j < n; j++) {

			if (fabs(a.a[j][k]) > fabs(a.a[l][k]))
				l = j;

			//j차항의 절대값이 더 큰걸 위로 올림
			for (j = k; j < n; j++) {	//swap (a.a[k][j], a.a[l][j]) 
				temp = a.a[k][j];
				a.a[k][j] = a.a[l][j];
				a.a[l][j] = temp;
			}

			if (a.a[k][k] != 0) {

				for (j = k + 1; j < n; j++) {
					multi = -1 * (a.a[j][k]) / a.a[k][k];	//소거를 위한 multi 계산
					//몇 배를 곱할건지 결정

					for (i = k; i < n; i++) {

						if (multi != 0)
							a.a[j][i] = a.a[j][i] + multi * a.a[k][i];
					}
					//printout(a, n);
				}
			}
			else {
				error = 1;
			}
		}
		k = k + 1;
	}

	if (error == 1) {
		printf("Trap condition..... \n");
	}

	//printout(a, n);

	backsub(a, n);
}

// 역대입법 계산 함수
void backsub(matrix a, int n) {

	int i = 0, j = 0, k = 0;
	float sum;



	//미지수 n개에 식이 n-1 개
	if (a.a[n - 1][n - 1] < 0.1) {
		//차수가 3인 행렬에 대한 계산
		if (n == 3) {
			//x1, x2를 x3에대한 식으로 표현하기
			float x1, x2, x3;
			x3 = -7;
			x2 = ((-1) * a.a[1][2] / a.a[1][1]);
			x1 = (-1) * ((a.a[0][1] * x2 + a.a[0][2])) / a.a[0][0];
			x2 *= x3;
			x1 *= x3;

			printf(" | %.1lf |\n", x1);
			printf(" | %.1lf |\n", x2);
			printf(" | %.1lf |\n\n\n", x3);
		}
		//차수가 2인 행렬에 대한 계산
		else if (n == 2) {
			if (a.a[n - 1][n - 1] < 0.1) {
				float x1 = a.a[0][0], x2 = a.a[0][1];
				printf(" | %.1lf |\n", x2);
				printf(" | %.1lf |\n", -x1);

			}
		}
	}
}

int main(void) {
	int i = 0, j = 0;
	int n;

	matrix a;

	printf(" ***********************************************************\n");
	printf(" **                                                       **\n");
	printf(" **        행렬의 고유값과 고유벡터 계산 프로그램         **\n");
	printf(" **                                                       **\n");
	printf(" ***********************************************************\n");


	printf(" 행렬의 최대 차수: ");
	scanf("%d", &n);

	printf("\n");

	// 행렬 입력
	printf(" 행렬 입력 \n");
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			printf(" %d 행 %d 열 : ", i + 1, j + 1);
			scanf("%lf", &a.a[i][j]);
		}
	}

	printf("\n");

	eigenvalue e = eigen(a, n);	//고유값 구하기

	if (e.cnt == 0)	//고유값이 존재하지 않을 때
		return 0;
	matrix b;
	for (i = 0; i < e.cnt; i++) {
		b = eigensub(a, n, e.e[i]);	//행렬에서 고유값 빼기
		printf(" 고유값 %d \n", e.e[i]);
		printf(" 고유벡터 \n");
		gauss(b, n);
	}

	return 0;
}