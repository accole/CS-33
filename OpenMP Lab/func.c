#include "func.h"
#include "util.h"

void func0(double *weights, double *arrayX, double *arrayY, int xr, int yr, int n)
{
	int i;
	for(i = 0; i < n; i++){
		weights[i] = 1/((double)(n));
		arrayX[i] = xr;
		arrayY[i] = yr;
	}
}

void func1(int *seed, int *array, double *arrayX, double *arrayY,
			double *probability, double *objxy, int *index,
			int Ones, int iter, int X, int Y, int Z, int n)
{
	int m_Ones = Ones;
	double d = (double) Ones;
	int m_n = n;
	double p;
	
	int indx, val;

	int i, j;
   	int index_X, index_Y;
	int max_size = X*Y*Z;

#pragma omp parallel for num_threads(30) firstprivate(seed, m_n, arrayX, arrayY) private(i)

   	for(i = 0; i < m_n; i++){
   		arrayX[i] += 1 + 5*rand2(seed, i);
   		arrayY[i] += (rand2(seed, i)*2) - 2;
   	}
		
#pragma omp parallel for num_threads(30) firstprivate(m_Ones, m_n, iter, Y, Z, max_size, arrayX, arrayY, objxy, index, array) private(i, j, index_X, index_Y, indx, val)

	for(i = 0; i< m_n; i++){

		indx = i*m_Ones;
   		for(j = 0; j < m_Ones; j++){
			index_X = round(arrayX[i]) + objxy[(j << 1) + 1];
	   		index_Y = round(arrayY[i]) + objxy[j << 1];
	   		val = fabs(index_X*Y*Z + index_Y*Z + iter);
			index[indx + j] = ( val >= max_size ) ? 0 : val;
	   	}
		
		p = 0;
	
   		for(j = 0; j < m_Ones; j++) {
			val = array[index[indx + j]];
   			p += (pow((val-100),2) - pow((val-228),2))/50.0;
   		}
   		probability[i] = p / d;
   	}
}


void func2(double *weights, double *probability, int n)
{
	int i;
	double sumWeights = 0;
	double temp;	

#pragma omp parallel for num_threads(30) firstprivate(n, weights, probability) private(i, temp) reduction(+:sumWeights)

	for(i = 0; i < n; i++) {
		temp = weights[i] * exp(probability[i]);
		sumWeights += temp;
		weights[i] = temp;
	}

#pragma omp parallel for num_threads(30) firstprivate(n, weights, sumWeights) private(i)
	
	for(i = 0; i < n; i++)
		weights[i] /= sumWeights;
}


void func3(double *arrayX, double *arrayY, double *weights, double *x_e, double *y_e, int n)
{
	double estimate_x=0.0;
	double estimate_y=0.0;
    int i;

	for(i = 0; i < n; i++){
   		estimate_x += arrayX[i] * weights[i];
   		estimate_y += arrayY[i] * weights[i];
   	}

	*x_e = estimate_x;
	*y_e = estimate_y;

}

void func4(double *u, double u1, int n)
{
	int i;
	double d = (double) n;

#pragma omp parallel for num_threads(30) firstprivate(n, u, u1, d) private(i)

	for(i = 0; i < n; i++){
	   	u[i] = u1 + i/d;
	}
}

void func5(double *x_j, double *y_j, double *arrayX, double *arrayY, double *weights, double *cfd, double *u, int n)
{
	int i, j;

	for(j = 0; j < n; j++){
   		//i = findIndex(cfd, n, u[j]);
   		i = findIndexBin(cfd, 0, n, u[j]);
   		if(i == -1)
   			i = n-1;
   		x_j[j] = arrayX[i];
   		y_j[j] = arrayY[i];

   	}

	for(i = 0; i < n; i++){
		arrayX[i] = x_j[i];
		arrayY[i] = y_j[i];
		weights[i] = 1/((double)(n));
	}
}
