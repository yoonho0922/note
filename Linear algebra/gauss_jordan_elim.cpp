#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define MAX 5

//선형방정식의 행렬 배열 구조체  
typedef struct _matrix {
	double a[MAX][MAX];
}matrix;

//선형방정식 해의 행렬 배열 구조체 
typedef struct _column {
	double c[MAX];
}column;

// TRUE, FALSE 구조체  
typedef enum {
	E_FALSE, E_TRUE
}E_BOOL;

void printout(matrix a, column c, int n);
void gauss(matrix a, column c, int n);
void backsub(matrix a, column c, int n);

//연산결과 출력  
void printout(matrix a, column c, int n) {
	int i = 0, j = 0;

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			printf(" %+.lf\t", a.a[i][j]);
		}
		printf(" x%d ", i + 1);
		printf(" %+.lf \n", c.c[i]);
	}
	printf("\n");
}

//가우스 소거법으로 계산
void gauss(matrix a, column c, int n) {
	E_BOOL error;

	int i = 0, j = 0, k = 0, l = 0;
	double multi = 0, temp = 0;

	printf("\n 가우스-조단소거법 풀이 과정: \n");
	printf(" ******************************************************* \n\n");

	error = E_FALSE;
	k = 0;

	while (k < n && error != E_TRUE) {
		l = k;
		for (j = k + 1;j < n; j++) {
			if (fabs(a.a[j][k]) > fabs(a.a[l][k])) {
				l = j;
			}
			for (j = k; j < n; j++) {
				temp = a.a[k][j];
				a.a[k][j] = a.a[l][j];
				a.a[l][j] = temp;
			}
			temp = c.c[k];
			c.c[k] = c.c[l];
			c.c[l] = temp;
			if (a.a[k][k] != 0) {
				for (j = k + 1; j < n; j++) {
					multi = -1 * (a.a[j][k]) / a.a[k][k];
					for (i = k; i < n; i++) {
						if (multi != 0) {
							a.a[j][i] = a.a[j][i] + multi * a.a[k][i];
						}
					}
					c.c[j] = c.c[j] + multi * c.c[k];

					printout(a, c, n);
				}
			}
			else
			{
				error = E_TRUE;
			}
		}
		k = k + 1;
	}

	if (error == E_TRUE) {
		printf("Trap condition....");
	}
	printout(a, c, n);
	printf(" ************************************* \n\n");
	backsub(a, c, n);
}

// 역대입법 계산
void backsub(matrix a, column c, int n) {
	int i = 0, j = 0, k = 0;
	float sum;
	column mat = { 0. };

	printf(" a[n,n] = %.f\n\n", a.a[n - 1][n - 1]);

	if (fabs(a.a[n - 1][n - 1]) == 0 || fabs(a.a[n - 1][n - 1]) < 1 / 1000000) {
		printf(" This matrix is singular, does not have unique solution \n\n");
	}
	else {
		mat.c[n - 1] = c.c[n - 1] / (a.a[n - 1][n - 1]);

		for (i = n - 2; i > -1; i--) {
			sum = 0.0f;

			for (j = n - 1; j > i; j--) {
				sum = sum + a.a[i][j] * mat.c[j];
			}


			if (fabs(a.a[n - 1][n - 1]) == 0 || fabs(a.a[n - 1][n - 1]) < 1 / 1000000) {
				printf(" This matrix is singular, does not have unique solution \n\n");
			}
			else {
				mat.c[i] = (c.c[i] - sum) / a.a[i][i];
			}
		}

		printf(" 입력한 선형방정식의 해답\n");
		for (k = 0; k < n; k++) {
			printf("x%d = ", k + 1);
			printf("%.lf \t", mat.c[k]);
		}
		printf("\n\n");
	}
}

int main(void) {
	int i = 0, j = 0;
	int n;

	matrix a;
	column c;


	printf("************************************************************\n");
	printf("**                                                        **\n");
	printf("** 가우스-조단 소거법을 이용한 선형 방정식 계산 프로그램  **\n");
	printf("**                                                        **\n");
	printf("************************************************************\n");

	printf(" 선형방정식의 최대 차수: ");
	scanf("%d", &n);

	printf("\n");

	printf(" 선형방정식의 수식을 입력하세요. \n");
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			printf("%d 번째 선형방정시 x%d의 값: ", i + 1, j + 1);
			scanf("%lf", &a.a[i][j]);
		}
	}

	printf("\n 선형방정식의 값을 입력하세요. \n");
	for (i = 0; i < n; i++) {
		printf(" %d 번째 선형방정식의 결과 값: ", i + 1);
		scanf("%lf", &c.c[i]);
	}

	printf("\n");

	gauss(a, c, n);
}
