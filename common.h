#ifndef _COMMON_H_
#define _COMMON_H_

#include <iostream>
#include <initializer_list>
#include <climits>
#include <string>


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
	}

	long& operator[](int offset) const noexcept{
		return data[offset];
	}

	~long_256(){delete[] data;}
	
	int size() const noexcept {return _size;}

	long_256 operator+ (long_256 other){
	int maxVal = (_size > other.size())? _size:other.size();
	long_256 newNum(maxVal+1);//assume zero'd out. Ill get that working at some point
	for(int i = 0; i < maxVal; ++i){
		if(LONG_MAX - data[i] > other[i]){//TODO CHECKS FOR MAKING SURE THE NUMBERS LINE UP
			newNum[i+1] = 1;
			newNum[i] = LONG_MIN+data[i]+other[i] + newNum[i];
		}
		else
			newNum[i] = newNum[i] + data[i]+other[i];
	}

	return newNum;
	}
	

	long_256 operator* (long_256 other);//TODO
	

};
	

std::ostream& operator<<(std::ostream& os,const long_256& l256){
	os << std::to_string(l256[0]);//No need for zero extension
	std::string zeroExtension,newLong;
	for(int i = 1; i < l256.size();++i){
		newLong = std::to_string(l256[i]);
		zeroExtension.clear();
		zeroExtension.append(19-newLong.length(),'0');
		os << zeroExtension + newLong;
	}
	return os;
}

#endif
