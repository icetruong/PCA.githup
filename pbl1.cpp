#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "pca.h"
#include "readfile.h"

typedef double T;
int main()
{
	int N,M,K;
	T** data;
	readfile(data,N,M);
	T** newData = (T**)malloc(N*sizeof(T*));
	for(int i = 0;i<N;i++)
		newData[i] = (T*)malloc(N*sizeof(T*));
	newData = PCA(data,N,M,K);
	for(int i = 0; i<K;i++){
			for(int j = 0; j<M;j++)
			printf("%.4f ",newData[i][j]);
	printf("\n");
	}
}
