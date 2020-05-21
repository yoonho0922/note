#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define N 4

double det(double (*A)[N], int n);

int main(void){
	int i=0, j=0;
	int n;
	double A[N][N] = {0,};
	
	printf("*********************************************\n");
	printf("**                                         **\n");
	printf("**          행렬식 계산 프로그램           **\n");
	printf("**                                         **\n");
	printf("*********************************************\n");
	
	//행렬의 크기 값 입력
	printf("행렬의 크기 입력: ");
	scanf("%d", &n);
	
	printf("\n");
	printf("행렬의 값을 입력하세요. \n");
	
	//각각의 행렬 값 입력
	for(i=0; i<n; i++){
		for(j=0; j<n; j++){
			printf("%d X %d 행렬의 값을 입력하세요: ", i+1, j+1);
			scanf("%lf", &A[i][j]);
		}
	}
	
	//입력한 행렬 값 출력
	printf("\n 입력한 행렬 A = \n");
	for(i=0; i<n; i++){
		printf("\t|\t");
		for(j=0; j<n; j++){
			printf("%.f\t",A[i][j]);
		}
		printf("|\n");
	}
	
	//행렬식 값을 출력
 	printf("입력한 행렬의 행렬식 값\n");
	printf("Det(A) = %.f\n\n", det(A,n));
	
}

double det(double (*A)[N], int n){
	int i,j,k,y;
	double det_a = 0;
	double temp[N][N];
	
	if(n!=1){
		for(i=0; i<n; i++){
			for(j=1; j<n; j++){
				y=0;
				
				for(k=0; k<n; k++){
					if(k != i){
						temp[j-1][y++] = *(A[0]+j*N+k);
					}
				}
			}
			det_a = det_a + *(A[0]+i)*(pow(-1,i))*det(temp,n-1);	
		}
		return det_a;		
	}
	else{
		return *A[0];
	}
	
}
