#ifndef PCA_H
#define PCA_H

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define Err 1e-4

typedef double T;

void printArray2(T** a,int N,int M)
{
	for(int i = 0; i<N;i++)
	{
		for(int j = 0; j<M;j++)
		printf("%10.4f ",a[i][j]);
	printf("\n");
	}
}

T** multy_array(T** a,T** b,int n,int m,int k)
{
	T** c = (T**)malloc(n*sizeof(T*));
	for(int i = 0;i<n;i++)
		c[i] = (T*)malloc(k*sizeof(T));
	for(int i = 0;i<n;i++)
		for(int j = 0;j<n;j++)
			c[i][j] = (T)0;
	for(int i = 0;i<n;i++)
		for(int j = 0;j<k;j++)
			for(int q = 0;q<m;q++)
			{
				c[i][j] += a[i][q]*b[q][j];
			}
	return c;
}

T** invert_array(T** a,int n,int m)
{
	T** c = (T**)malloc(m*sizeof(T*));
	for(int i = 0;i<m;i++)
		c[i] = (T*)malloc(n*sizeof(T));
	for(int i = 0;i<m;i++)
		for(int j = 0;j<n;j++)
			c[i][j] = a[j][i];
	return c;
}

T* average_vecto(T** A_matrix,int N,int M)
{
	T* X =(T*) malloc(N*sizeof(T));
	for(int i = 0;i<N;i++) 
		X[i] = (T)0;
	for(int i = 0;i<N;i++){
		for(int j = 0;j<M;j++)
			X[i] += A_matrix[i][j];
		X[i]=X[i]/ M;
	}
	return X;
}

T** datanew_vecto(T** A_matrix,T* X,int N,int M)
{
	T** Tempdata = (T**) malloc(N*sizeof(T*));
	for(int i = 0;i<N;i++) 
		Tempdata[i] = (T*) malloc(M*sizeof(T));
	for(int i = 0;i<N;i++)
		for(int j = 0;j<M;j++)
			Tempdata[i][j] = A_matrix[i][j] - X[i];
	return Tempdata;
}

T** covar_matrix(T** A_matrix,T** At_matrix,int N,int M)
{
	T** c = (T**)malloc(N*sizeof(T*));
	for(int i = 0;i<N;i++)
		c[i] = (T*)malloc(N*sizeof(T));
	c = multy_array(A_matrix,At_matrix,N,M,N);
	for(int i = 0;i<N;i++)
		for(int j = 0;j<N;j++)
			c[i][j] =(T) c[i][j] / (M-1);
	return c;
}

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
	
	return C_matrix;
}

T** Eigenvecto_Eigenvalue(T** C_matrix,int M,T** Eigenvecto,T* Eigenvalue)
{
	int i,j;
	T rmax,rPhi;
	T** eVec =(T**) malloc(M*sizeof(T*));
	T** eTemp =(T**) malloc(M*sizeof(T*));
	T** eC   =(T**) malloc(M*sizeof(T*));
	for(int k = 0;k<M;k++)
	{
		eVec[k] = (T*)malloc(M*sizeof(T));
		eTemp[k] = (T*)malloc(M*sizeof(T));
		eC[k] = (T*)malloc(M*sizeof(T));
	}
	
	for( i = 0; i<M;i++)
		for( j = 0;j<M;j++)
		{
			eTemp[i][j] = (T)0;
			eVec[i][j] = (T)0;
			eC[i][j] = (T)0;
			if(i == j) eTemp[i][j] = (T)1;
		}
	while(1)
	{
		i=0,j=0;
		rmax = getMax(C_matrix,M,i,j);
		if(rmax <= Err) break;
		
		rPhi = atan((T)2*C_matrix[i][j]/(C_matrix[i][i]-C_matrix[j][j])) / (T)2;
		C_matrix = Jacobi(C_matrix,M,i,j,rPhi);
		for(int k = 0;k<M;k++)
			eC[k][k] = (T)1;
		eC[i][i] = cos(rPhi);
		eC[j][j] = eC[i][i];
		eC[j][i] = sin(rPhi);
		eC[i][j] = -eC[j][i];
		
		eVec = multy_array(eTemp,eC,M,M,M);
		for(int i = 0;i<M;i++)
			for(int j = 0;j<M;j++)
			{
				eTemp[i][j] = eVec[i][j];
				eVec[i][j] = (T)0;
				eC[i][j] = (T)0;
			}
	}
	for(int i = 0;i<M;i++)
		Eigenvalue[i] = C_matrix[i][i];
	for(int i = 0;i<M;i++)
		for(int j = 0;j<M;j++)
			Eigenvecto[i][j] = eTemp[i][j];
			
	T* TempEigenvecto =(T*) malloc(M*sizeof(T));
	for(int i = 0;i<M;i++)
		for(int j = M-1;j>i;j--)
			if(Eigenvalue[j]>Eigenvalue[j-1])
			{
				T TempEigenvalue = Eigenvalue[j-1];
				Eigenvalue[j-1] = Eigenvalue[j];
				Eigenvalue[j] = TempEigenvalue;
				for(int k = 0;k<M;k++)
					TempEigenvecto[k] = Eigenvecto[k][j-1];
				for(int k = 0;k<M;k++)
					Eigenvecto[k][j-1] = Eigenvecto[k][j];
				for(int k = 0;k<M;k++)
					Eigenvecto[k][j] = TempEigenvecto[k];
			}
	return Eigenvecto;
}

T** normalize(T** Eigenvecto,int N,int M)
{
	T* temp = (T*) malloc(M*sizeof(T));
	for(int i = 0;i<M;i++)
		temp[i] = (T)0;
	for(int j = 0;j<M;j++)
	{
		for(int i = 0;i<N;i++)
			temp[j] += Eigenvecto[i][j]*Eigenvecto[i][j];
		temp[j] = sqrt(temp[j]);
	}
	for(int i = 0;i<N;i++)
		for(int j = 0;j<M;j++)
			Eigenvecto[i][j] = Eigenvecto[i][j] / temp[j];
	return Eigenvecto;
}

int shorteneigenvalue(T* Eigenvalue,int M)
{
	T sumM = (T)0,sumK = (T)0;
	for(int i = 0;i<M;i++)
		sumM += Eigenvalue[i];
	for(int i = 0;i<M;i++)
	{
		sumK+=Eigenvalue[i];
		if(sumK/sumM > (T)0.95) return i+1;
	}
}


T** PCA(T** Data,int N,int M,int &K)
{
	T* X =(T*) malloc(N*sizeof(T));// vecto_average;
	T** TempData = (T**) malloc(N*sizeof(T*));
	T** TempDatat = (T**) malloc(M*sizeof(T*));
	T** C_matrix = (T**) malloc(N*sizeof(T*));// matrix covariance
	T** A_At_matrix = (T**) malloc(M*sizeof(T*));
	T** Eigenvecto = (T**) malloc(N*sizeof(T*));
	T** Eigenvectot = (T**) malloc(M*sizeof(T*));
	T* Eigenvalue = (T*) malloc(N*sizeof(T));
	T** Temp_Eigenvecto = (T**) malloc(M*sizeof(T*));
	for(int i = 0;i<N;i++)
	{
		TempData[i] = (T*)malloc(M*sizeof(T));
		C_matrix[i] = (T*)malloc(N*sizeof(T));
		Eigenvecto[i] = (T*)malloc(N*sizeof(T));
	}
	for(int i = 0;i<M;i++)
	{
		TempDatat[i] = (T*)malloc(N*sizeof(T));
		Eigenvectot[i] = (T*)malloc(M*sizeof(T));
		A_At_matrix[i] = (T*)malloc(M*sizeof(T));
		Temp_Eigenvecto[i] = (T*)malloc(M*sizeof(T));
	}
		
	
	// initialize data 
	for(int i = 0;i<N;i++)
		for(int j = 0;j<M;j++)
		{
			TempData[i][j] = Data[i][j];
			C_matrix[i][j] = (T)0;
			Eigenvecto[i][j] = (T)0;
		}
	for(int i = 0;i<N;i++)
	{
		X[i] = (T)0;
		Eigenvalue[i] = (T)0;
	}
	//calculation
	X = average_vecto(Data,N,M);
	TempData = datanew_vecto(Data,X,N,M);
	TempDatat = invert_array(TempData,N,M);
	C_matrix = covar_matrix(TempData,TempDatat,N,M);
	if(N>M) 
	{	
		A_At_matrix = covar_matrix(TempDatat,TempData,M,N);
		Temp_Eigenvecto = Eigenvecto_Eigenvalue(A_At_matrix,M,Temp_Eigenvecto,Eigenvalue);
		Eigenvecto = multy_array(TempData,Temp_Eigenvecto,N,M,M);
		Eigenvecto = normalize(Eigenvecto,N,M);
	}
	else
		Eigenvecto = Eigenvecto_Eigenvalue(C_matrix,N,Eigenvecto,Eigenvalue);
	K = shorteneigenvalue(Eigenvalue,N);
	T** NewData = (T**) malloc(K*sizeof(T*));
	for(int i = 0;i<K;i++)
		NewData[i] = (T*) malloc(M*sizeof(T));
	Eigenvectot = invert_array(Eigenvecto,N,M);
	NewData = multy_array(Eigenvectot,TempData,K,N,M);
	return NewData;
}


#endif
