#include <stdio.h>
#include <time.h>
#include "work_with_file.h"

#define MIN 0
#define MAX 255

void make_random_array(int** a,int n,int m)
{
	srand((int) time(0));
	for(int i = 0;i<n;i++)
		for(int j = 0;j<m;j++)
			a[i][j] = MIN + rand() % (MAX - MIN +1);
}

int main()
{
	int n,m;
	int **a;
	printf("nhap n: ");scanf("%d",&n);
	printf("nhap m: ");scanf("%d",&m);
	a =(int **) malloc(n*sizeof(int *));
	for(int i = 0;i<n;i++)
		a[i] =(int *) malloc(m*sizeof(int));
	make_random_array(a,n,m);
	writefile(a,n,m);
	printf("bo du lieu duoc tao ra la: \n");
	for(int i = 0;i<n;i++)
	{
		for(int j = 0;j<m;j++)
			printf("%d ",a[i][j]);
		printf("\n");
	}			
}
