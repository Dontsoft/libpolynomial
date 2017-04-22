#ifndef _DONTSOFT_POLYNOMIAL_H
#define _DONTSOFT_POLYNOMIAL_H

#ifdef __cplusplus
	#include <vector>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef unsigned int UINT;
typedef int INT;

typedef struct polynomial_t
{
	UINT degree;
	double* coefficients;
} polynomial;

#ifdef __cplusplus
extern "C" {
#endif

polynomial * new_polynomial(UINT number_of_coefficients, double* coefficients);

void delete_polynomial(polynomial * polynomial);

double value(polynomial p, double x);

polynomial * division(polynomial a, polynomial b);
polynomial * multiplication(polynomial a, polynomial b);

polynomial * addition(polynomial a, polynomial b);
void add(polynomial * a, double x0);
polynomial * subtraction(polynomial a, polynomial b);
void sub(polynomial * a, double x0);

polynomial * differentiate(polynomial p);
polynomial * integrate(polynomial p);

polynomial *  normalize(polynomial p);

UINT roots(polynomial p, double * x);

polynomial * polynomial_through_points(double *x, double *y);

void print_polynomial(polynomial p);
void print_value_array(double* x, UINT size);

#ifdef __cplusplus
}
double* vector_to_array(std::vector<double> v)
	{
		double* a = &v[0];
		return a;
	}
polynomial * new_polynomial(std::vector<double> coefficients) 
{
	return new_polynomial(coefficients.size(),vector_to_array(coefficients));
}

polynomial * polynomial_through_points(std::vector<double> x, std::vector<double> y)
{
	return polynomial_through_points(vector_to_array(x),vector_to_array(y));
}

void print_value_array(std::vector<double> x)
{
	print_value_array(vector_to_array(x),x.size());
}
#else
	typedef unsigned int bool;
	#define false 0
	#define true !false
#endif

#endif