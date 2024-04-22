#ifndef jacobi_h
#define jacobi_h

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef double T;

T** Jacobi(T** C_matrix,int M,int ii,int jj,T rPhi)
{
	T** Temp = (T**)malloc(M*sizeof(T*));
	for(int i = 0;i<M;i++)
		Temp[i] = (T*)malloc(M*sizeof(T));
	for(int i = 0;i<M;i++)
		for(int j = 0; j<M;j++)
		{
			Temp[i][j] = C_matrix[i][j];
			C_matrix[i][j] = (T)0;
		}
	T rSp = sin(rPhi);
	T rCp = cos(rPhi);
//	 multy 3 matrix
	for(int i = 0;i<M;i++)
		for(int j = 0;j<M;j++)
			if(i == ii) // row i
				if(j == ii) 
					C_matrix[i][j] = Temp[ii][ii]*rCp*rCp + Temp[jj][jj]*rSp*rSp + 2*Temp[ii][jj]*rCp*rSp;
				else 
					if(j == jj) 
						C_matrix[i][j] = (Temp[jj][jj]-Temp[ii][ii])*rSp*rCp + Temp[ii][jj]*(rCp*rCp-rSp*rSp);
					else 
						C_matrix[i][j] = Temp[ii][j]*rCp+Temp[jj][j]*rSp;
					 
			else 
				if(i == jj)  // row j
					if(j == ii)  
						C_matrix[i][j] = (Temp[jj][jj]-Temp[ii][ii])*rSp*rCp + Temp[ii][jj]*(rCp*rCp-rSp*rSp);
					else 
						if(j == jj) 
							C_matrix[i][j] = Temp[ii][ii]*rSp*rSp + Temp[jj][jj]*rCp*rCp - 2*Temp[ii][jj]*rCp*rSp;
					 	else 
						 	C_matrix[i][j] = Temp[jj][j]*rCp-Temp[ii][j]*rSp;
				else	// row l!=i,j
					if(j == ii) 
						C_matrix[i][j] = Temp[ii][i]*rCp+Temp[jj][i]*rSp;
					else 
						if(j ==jj) 
							C_matrix[i][j] = Temp[jj][i]*rCp-Temp[ii][i]*rSp;
						else 
							C_matrix[i][j] = Temp[i][j];
	
	for(int k = 0;k<M;k++)
		free(Temp[k]);
	free(Temp);
	
	return C_matrix;
}

#endif
