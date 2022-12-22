#ifndef _COMMON_H_
#define _COMMON_H_

#include <iostream>
#include <initializer_list>
#include <climits>

class long_256 {
	private:
		long* data;
		int size;
	public:
	long_256(std::initializer_list<long> list): data(new long[list.size()]), size(list.size()) {
		for (auto i : list){
			(*data) = i;
			data++;
		}
		data-=size;
		for (int i = 0; i < size; ++i)
			std::cout << data[i];
	}
	~long_256(){delete[] data;}
	long_256 operator* (long_256 other);//TODO

};

#endif
