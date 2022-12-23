#include "common.h"


int main(){

	long_256 test1({123,LONG_MAX,789,LONG_MAX,LONG_MAX,LONG_MAX});
	
	long_256 test2({1,2,3});
	std::cout << test1 << std::endl;
	std::cout << test2 << std::endl;

}
