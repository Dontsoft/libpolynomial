#include "polynomial.h"

UINT __quadratic_r00ts__(polynomial p, double * x);
UINT __cubics_r00ts__(polynomial p, double * x);
UINT __quartics_r00ts__(polynomial p, double * x);

double* d_ptr(int size) 
{
	return (double*)malloc(size * sizeof(double));
}

polynomial* p_ptr()
{
	return (polynomial*)malloc(sizeof(polynomial));
}

polynomial * new_polynomial(UINT number_of_coefficients, double* coefficients)
{
	polynomial *p;
	if((p = p_ptr()) != NULL && coefficients != NULL)
	{
		while(number_of_coefficients > 0 && round(coefficients[number_of_coefficients - 1]) == 0)
			number_of_coefficients--;
		if(number_of_coefficients == 0)
			return NULL;
		p->degree = number_of_coefficients - 1;
		p->coefficients = d_ptr(number_of_coefficients);
		memcpy(p->coefficients,coefficients,number_of_coefficients * sizeof(double));
	}
	return p;
}

void delete_polynomial(polynomial* polynomial)
{
	free(polynomial->coefficients);
	free(polynomial);
}

double value(polynomial p, double x)
{
	double y = 0;
	for(int i = (int)p.degree; i >= 0; i--)
		y += (pow(x,i) * p.coefficients[i]);
	return y;
}

polynomial * division(polynomial a, polynomial b)
{
	
}

polynomial * multiplication(polynomial a, polynomial b)
{
	UINT degree = a.degree + b.degree;
	double * coefficients = d_ptr(degree + 1);
	for(int i = 0; i <= a.degree; i++)
		for(int j = 0; j <= b.degree; j++)
			coefficients[i+j] += a.coefficients[i] * b.coefficients[j];
	return new_polynomial(degree+1,coefficients);
}

polynomial * addition(polynomial a, polynomial b)
{
	UINT degree = a.degree > b.degree ? a.degree : b.degree;
	double * coefficients = d_ptr(degree + 1);
	for(int i = 0; i <= degree; i++)
		coefficients[i] = (i <= a.degree ? a.coefficients[i] : 0) + (i <= b.degree ? b.coefficients[i] : 0);
	return new_polynomial(degree + 1,coefficients);
}

void add(polynomial * a, double x0)
{
	a->coefficients[0] -= x0;
}

polynomial * subtraction(polynomial a, polynomial b)
{
	UINT degree = a.degree > b.degree ? a.degree : b.degree;
	double * coefficients = d_ptr(degree + 1);
	for(int i = 0; i <= degree; i++)
		coefficients[i] = (i <= a.degree ? a.coefficients[i] : 0) - (i <= b.degree ? b.coefficients[i] : 0);
	return new_polynomial(degree + 1,coefficients);
}

void sub(polynomial * a, double x0)
{
	a->coefficients[0] -= x0;
}

polynomial * differentiate(polynomial p)
{
	UINT degree = p.degree - 1;
	double * coefficients = d_ptr(degree + 1);
	for(int i = 0; i <= degree; i++)
		coefficients[i] = p.coefficients[i+1] * (i+1);
	return new_polynomial(degree + 1, coefficients);
}

polynomial * integrate(polynomial p)
{
	UINT degree = p.degree + 1;
	double * coefficients = d_ptr(degree + 1);
	coefficients[0] = 0;
	for(int i = 1; i <= degree; i++)
		coefficients[i] = p.coefficients[i - 1] / i;
	return new_polynomial(degree + 1, coefficients);
}

polynomial * normalize(polynomial p)
{
	double an = p.coefficients[p.degree];
	for(int i = 0; i <= p.degree; i++)
		p.coefficients[0] /= an;
	return new_polynomial(p.degree,p.coefficients);
}

UINT roots(polynomial p, double * x)
{
	if(p.degree == 0)
	{
		return 0;
	}
	else if(p.degree == 1)
	{
		x[0] = -p.coefficients[0] / p.coefficients[1];
		return 1;
	}
	else if(p.degree == 2)
	{
		return __quadratic_r00ts__(p, x);
	}
	else if(p.degree == 3)
	{
		return __cubics_r00ts__(*normalize(p), x);
	}
	else if(p.degree == 4)
	{
		return __quartics_r00ts__(*normalize(p), x);
	}
	return 0;
}

UINT __quadratic_r00ts__(polynomial p, double * x)
{
	printf("%f\n",(pow(-p.coefficients[1],2) - 4*p.coefficients[2]*p.coefficients[0]));
	if((pow(-p.coefficients[1],2) - 4*p.coefficients[2]*p.coefficients[0]) < 0)
		return 0;
	x[0] = (-p.coefficients[1] + sqrt(pow(-p.coefficients[1],2) - 4*p.coefficients[2]*p.coefficients[0]))/(2*p.coefficients[2]);
	x[1] = (-p.coefficients[1] - sqrt(pow(-p.coefficients[1],2) - 4*p.coefficients[2]*p.coefficients[0]))/(2*p.coefficients[2]);
	return 2;
}

UINT __cubics_r00ts__(polynomial p, double * x)
{

}

UINT __quartics_r00ts__(polynomial p, double * x)
{

}

polynomial * polynomial_through_points(double *x, double *y)
{

}

void print_polynomial(polynomial p)
{
	if(p.degree < 0 || p.coefficients == NULL)
		return;
	bool first = true;
	for(int i = (int)p.degree; i >= 0; i--)
	{
		if(p.coefficients[i] != 0)
		{
			if(i == 0)
			{
				if(first)
					printf("%f",p.coefficients[i]);	
				else
					printf("+ %f",p.coefficients[i]);
			}
			else
			{
				if(first)
					printf("%f*x^%d",p.coefficients[i],i);	
				else
					printf("+ %f*x^%d",p.coefficients[i],i);
			}
			first = false;
		}
	}
	printf("\n");
}

void print_value_array(double * x, UINT size)
{
	for(UINT i = 0; i < size; i++)
		printf("%f ",x[i]);
	printf("\n");
}