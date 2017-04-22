#include "polynomial.h"

int main(int argc, char** argv)
{
	std::vector<double>c ({1,2});
	std::vector<double>c2 ({2,1});
	
	polynomial * p = new_polynomial(c);
	print_polynomial(*p);

	polynomial * p2 = new_polynomial(c2);
	print_polynomial(*p2);
	printf("=========\n");
	polynomial * p3 = multiplication(*p,*p2);
	print_polynomial(*p3);
	printf("========\n");

	delete_polynomial(p);
	delete_polynomial(p2);
	delete_polynomial(p3);

	return 0;
}