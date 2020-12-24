#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define N 5		//행렬과 열의 최대값

double det(double (*A)[N], int n);	//행렬식을 구하는 자기호출함수  
void cramer(double (*A)[N], double C[N], int n, int c);
//크래머의 규칙을 이용한 선형방정식과 결과 값 계산함수

int main(void){
	int i = 0, j = 0;	//루프를 수행하기 위한 변수 선언
	int n;	// 선형 방정식의 최대 차수  
	double A[N][N] = {0, };	//크기가 5*5인 2차원 배열 A 선언 (좌측 행렬) 
	double C[N] = {0, };	//크기가 5인 배열 C 선언  (우측 행렬) 
	
	printf(" ***********************************************************\n");
	printf(" **                                                       **\n");
	printf(" **    크래머의 규칙을 이용한 선형방정식 계산 프로그램    **\n");
	printf(" **                                                       **\n");
	printf(" ***********************************************************\n");
	
	//행렬의 크기 값을 입력한다. 
	printf(" 선형방정식의 최대 차수를 입력하세요: ");
	scanf("%d", &n);
	
	printf("\n");
	
	//선형방정식의 수식을 입력한다. 
	printf(" 선형방정식의 수식을 입력하세요. \n");
	
	for(i=0; i<n; i++){
		for(j=0; j<n; j++){
			//i+1번째 선형방정식 x(j+1)의 계수는 A[i][j]에 저장된다.   
			printf(" %d 번째 선형방정식 x%d 의 값: ", i+1, j+1);
			scanf("%lf", &A[i][j]);
		}
	}
	printf("\n");
	
	//선형방정식의 결과 값을 입력한다.
	printf(" 선형방정식의 결과 값을 입력하세요. \n"); 
	
	for(i=0; i<n; i++){
		// i+1번째 선형방정식의 결과 값이 C[i]에 저장된다. 
		printf(" %d번째 선형방정식의 결과 값: ", i+1);
		scanf("%lf", &C[i]);
	}
	
	//입력한 행렬 값을 출력한다.
	printf("\n 입력한 선형방정식의 행렬= \n\n");
	
	for(i = 0; i<n; i++){	//i+1번째 선형방정식  
		printf(" |\t");	//tab으로 보기 편하도록 간격을  줌  
		for(j = 0; j<n; j++){  // i+1번째 선형방정식의 좌측 부분(변수와 계수들)  
			printf(" %.f x%d\t", A[i][j], j+1); //소수점을 없애고 보여주기위해 %.f  
		}
		printf("=\t");
		printf("%.f\t", C[i]); //i+1번째 선형방정식의 우측 부분(결과 값)  
		printf("|\n");
	}
	printf("\n");
	
	// 입력한 행렬 A(선형방정식)의 행렬식 값을 출력한다.
	printf(" 입력한 선형방정식의 행렬식 값\n");
	printf(" Det(A) = %.f \n\n", det(A, n));	//함수 det를 이용하여 행렬식 구함  
	
	// 입력한 행렬 A(선형방정식)의 행렬식 값을 출력한다.
	printf(" 입력한 선형방정식의 해답\n");
	
	for(i = 1; i<n+1; i++){
		cramer(A, C, n, i);
	}
	printf("\n\n");
}

// 행렬식 값을 구하는 자기호출함수  
//좌측행렬이 저장된 A와 행렬의 최대 차수 n을 받음 
double det(double A[][N], int n){ 
	int i,j,k,y;	//루프를 수행하기 위한 변수 선언
	
	double det_a = 0;	//결과 값 저장 변수
	double temp[N][N];	//행렬식 값 임시 저장 배열
	
	if(n != 1){
		for(i = 0; i<n; i++){	//i+1번째 행  
			for(j=1; j<n; j++){	//j+1번째 열  
				y = 0;
				
				for(k = 0; k<n; k++){	//행렬의 최대 차수만큼 반복  
					if(k != i)
						temp[j-1][y++] = *(A[0]+j*N + k);
					//소행렬식을 하기 위해 각 행렬의 원소들을 재배치한다. 
				}
			}
			
			det_a = det_a + *(A[0]+i) * (pow(-1,i)) * det(temp,n-1);
			// 소행렬식들의 전체합을 구한다. 
			
		}return det_a;
	}else return *A[0];
}

// 크래머의 규칙을 이용한 선형방정식 결과 값 계산함수
void cramer(double A[][N], double C[N], int n, int c){
	int i =0, j=0;	//루프를 수행하기 위한 변수 선언 
	
	double temp[N][N] = {0, };
	
	// 입력받은 행렬 A의 값을 임시 배열에 저장한다. 
	for(i=0; i<n; i++){
		for(j=0; j<n; j++){
			temp[i][j] = A[i][j];
		}
	}
	
	// 행렬 A의 값을 넘겨받은 임시 배열 temp의 각 열에 C의 값을 대입한다.
	for(i = 0; i<n; i++){
		for(j=c-1; j<c; j++){
			temp[i][j] = C[i];
		}
	}
	
	// 션형방정식의 해를 출력한다(부분행렬의 행렬식/전체행렬의 행렬식).
	printf(" x%d = %.f \t", c, (det(temp,n) / det(A,n)) );
}
	
