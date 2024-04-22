#ifndef getMax_h
#define getMax_h

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef double T;

T getMax(T** C_matrix,int M,int &ii,int &jj)
{
	T rmax = C_matrix[0][1];
	ii = 0;
	jj = 1;
	for(int i = 0;i<M;i++)
		for(int j =0;j<M;j++)
			if(i!=j)
				if(fabs(C_matrix[i][j])>rmax)
				{
					rmax = fabs(C_matrix[i][j]);
					ii = i;
					jj = j;
				}
	return rmax;
}

#endif
