#include "common.h"


int main(){

	int_256 test1({123,INT_MAX,789,INT_MAX,INT_MAX,INT_MAX});
	
	int_256 test2({1,2,3});
	std::cout << test1 << std::endl;
	std::cout << test2 << std::endl;
	int_256 test3 = test2 + test2;
	std::cout << test3 << std::endl;	



}
