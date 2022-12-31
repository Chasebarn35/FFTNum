#include "common.h"


int main(){

	int_256 test4({123,456,789,101112,INT_MAX});
	int_256 test5({8,INT_MAX});
	std::cout << test4 << " * " << test5 << " = " << std::endl;
	std::cout << test4*test5 << std::endl;

}
