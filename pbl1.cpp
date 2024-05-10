#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "pca.h"
#include "work_with_file.h"

typedef double T;
int main()
{
	printf("<--------------------> PBL1: LAP TRINH TINH TOAN <-------------------->\n\n");
	printf("<---- De tai: Su dung Eigenface de phan tich cac thanh phan PCA ---->\n\n");
	printf("<----------- Giao vien huong dan: Nguyen Tan Khoi ------------------>\n\n");
	printf("<-------------------->                           <-------------------->\n\n\n\n");
	int N,M,K,random;
	T** data;
	readfile(data,N,M);
	printf("bo du lieu ban dau: \n");
	printArray2(data,N,M);
	
	T** newData = (T**)malloc(N*sizeof(T*));
	for(int i = 0;i<N;i++)
		newData[i] = (T*)malloc(N*sizeof(T*));
	newData = PCA(data,N,M,K);
	printf("\nbo du lieu sau khi bien doi la: \n");
	printArray2(newData,K,M);
	
}
