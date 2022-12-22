#ifndef _COMMON_H_
#define _COMMON_H_

#include <iostream>
#include <initializer_list>
#include <climits>

class long_256 {
	private:
		long* data;
		int _size;//maybe look into changing to a size_t?
	public:
	long_256(int __size): data(new long[__size]),_size(__size){}	
	long_256(std::initializer_list<long> list): data(new long[list.size()]), _size(list.size()) {
		for (auto i : list){
			(*data) = i;
			data++;
		}
		data-=_size;
		for (int i = 0; i < _size; ++i)
			std::cout << data[i];
	}

	~long_256(){delete[] data;}
	
	int size(){return _size;}

	long_256 operator+ (long_256 other){
	int maxVal = (_size > other.size())? _size:other.size();
	long_256 newNum(maxVal);//assume zero'd out. Ill get that working at some point
	for(int i =0; i < _size; ++i){
		

	}

	return newNum;
	}

	long_256 operator* (long_256 other);//TODO
	

};

#endif
