#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "pca.h"
#include "readfile.h"

typedef double T;
int main()
{
	printf("<--------------------> PBL1: LAP TRINH TINH TOAN <-------------------->\n\n");
	printf("<---- De tai: Su dung Eigenface de phan tich cac thanh phan PCA ---->\n\n");
	printf("<----------- Giao vien huong dan: Nguyen Tan Khoi ------------------>\n\n");
	printf("<-------------------->                           <-------------------->\n\n\n\n");
	int N,M,K;
	T** data;
	readfile(data,N,M);
	T** newData = (T**)malloc(N*sizeof(T*));
	for(int i = 0;i<N;i++)
		newData[i] = (T*)malloc(N*sizeof(T*));
	newData = PCA(data,N,M,K);
	for(int i = 0; i<K;i++){
			for(int j = 0; j<M;j++)
			printf("%10.4f ",newData[i][j]);
	printf("\n");
	}
}
