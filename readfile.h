#ifndef readfile_h
#define readfile_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef double T;

void readfile(T** &a,int &n,int &m)
{
	FILE *fptr;
	char x[10];
	printf("nhap case ban muon test: ");
	gets(x);
	strcat(x,".txt");
	fptr = fopen(x, "r");
	fscanf(fptr, "%d %d", &n, &m); 
	a = (T**)malloc(n*sizeof(T*));
	for(int i = 0;i<n;i++)
		a[i] = (T*)malloc(m*sizeof(T*));
	for (int i = 0; i < n; i++) 
        for (int j = 0; j < m; j++) 
        	fscanf(fptr, "%lf", &a[i][j]);
	fclose(fptr);
}

#endif
