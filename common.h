#ifndef _COMMON_H_
#define _COMMON_H_

#include <iostream>
#include <initializer_list>
#include <climits>
#include <string>


class int_256 {
private:
	int* data;
	size_t _size;//maybe look into changing to a size_t?
public:
int_256(size_t __size): data(new int[__size]),_size(__size){}	
int_256(std::initializer_list<int> list): data(new int[list.size()]), _size(list.size()) {
	data+=_size;
	for (auto i : list){
		(*--data) = i;
		}
	}
int& operator[](int offset) const noexcept{
	return data[offset];
	}
~int_256(){}
size_t size() const noexcept {return _size;}

int_256 operator+ (int_256 other){
	size_t maxVal = (_size > other.size())? _size:other.size();
	int_256 newNum(maxVal+1);//assume zero'd out. Ill get that working at some point
	for(size_t i = 0; i < maxVal; ++i){
		long temp = (long)newNum[i] + (long)other[i] + (long)data[i];//TODO SOLVE FOR NON SAME LENGTH
		newNum[i] = (int)(temp&INT_MAX);
		newNum[i+1] = (int)((temp >> 32)&INT_MAX);
		}
	return newNum;
	}
	
int_256 operator+ (int other){
	int_256 newNum(this);
	for(size_t i =0; i < maxVal; ++i){
		long otherD = !i?0L:(long)other;
		long temp = (long)newNum[i] + otherD;
		newNum[i] = (int)(temp&INT_MAX);
		newNum[i+1]=(int)((temp>>32)&INT_MAX);
	}



	return newNum;
	}


int_256 operator* (int_256 other);//TODO
	

};

std::ostream& operator<<(std::ostream& os,const int_256& l256){
	os << std::to_string(l256[l256.size()-1]);//No need for zero extension
	std::string zeroExtension,newLong;
	for(size_t i = 2; i <= l256.size();++i){
		newLong = std::to_string(l256[l256.size()-i]);
		zeroExtension.clear();
		zeroExtension.append(10-newLong.length(),'0');//TODO make digit length compile time found
		os << zeroExtension + newLong;
	}
	return os;
}

#endif
