#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "pca.h"

typedef double T;

int main()
{
	system("color 70");
	printf("\n<--------------------> PBL1: LAP TRINH TINH TOAN <-------------------->\n\n");
	printf("<---- De tai: Su dung Eigenface de phan tich cac thanh phan PCA ---->\n\n");
	printf("<----------- Giao vien huong dan: Nguyen Tan Khoi ------------------>\n\n");
	printf("<-------------------->                           <-------------------->\n\n\n\n");
	int N,M,K;
	T** data;
	readfile(data,N,M);
	printf("\nBo du lieu ban dau: \n");
	printArray2(data,N,M);
	
	T** newData = (T**)malloc(N*sizeof(T*));
	for(int i = 0;i<N;i++)
		newData[i] = (T*)malloc(N*sizeof(T*));
	newData = PCA(data,N,M,K);
	printf("\nBo du lieu sau khi bien doi la: \n\n");
	printArray2(newData,K,M);
}
