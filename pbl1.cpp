#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "pca.h"

typedef double T;

int main()
{
	int N,M,K;
	FILE *fptr;
	char x[10];
	printf("nhap case ban muon test: ");
	gets(x);
	strcat(x,".txt");
	fptr = fopen(x, "r");
	fscanf(fptr, "%d %d", &N, &M); 
	T** data = (T**)malloc(N*sizeof(T*));
	for(int i = 0;i<N;i++)
		data[i] = (T*)malloc(M*sizeof(T*));
	for (int i = 0; i < N; i++) 
        for (int j = 0; j < M; j++) 
        	fscanf(fptr, "%lf", &data[i][j]);
    fclose(fptr);
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
