#ifndef _COMMON_H_
#define _COMMON_H_

#include <iostream>
#include <initializer_list>
#include <climits>
#include <string>


class int_256 {
private:
	int* data;
	size_t _size,_cap;//maybe look into changing to a size_t?
public:
int_256(size_t __size): data(new int[__size]),_size(__size),_cap(__size){}	
int_256(std::initializer_list<int> list): data(new int[list.size()]), _size(list.size()),_cap(_size) {
	data+=_size;
	for (auto i : list){
		(*--data) = i;
		}
	}
int_256(const int_256& other): data(new int[other.size()]),_size(other.size()),_cap(other.size()){
	for(size_t i = 0; i < _size;++i)
		data[i] = other[i];
	
	}
void resize(){//Removes leading zeros
	int a = data[_size-1];//top of the data
	if(!a){
		for(;!a;_size--)
			a=data[_size-1];
		_size++;
		}
	}
int& operator[](int offset) const noexcept{
	return data[offset];
	}
~int_256(){}
size_t size() const noexcept {return _size;}

int_256 operator+ (int_256 other){
	
	int_256* larger;
	int_256* smallr;
	size_t maxVal;
	if(_size > other.size()){
		maxVal = _size;
		larger = &(*this);
		smallr = &other;
		}
	else{
		maxVal = other.size();
		larger = &other;
		smallr = &(*this);
		}


	int_256 Num(maxVal+1);//assume zero'd out. Ill worry about that at some point
	for(size_t i = 0; i < maxVal; ++i){
		long temp = (i<(*smallr).size())?(long)Num[i]+(long)(*larger)[i]+(long)(*smallr)[i]:(long)Num[i]+(long)(*larger)[i];
		Num[i] = (int)(temp&INT_MAX);
		Num[i+1] = (int)((temp >> 31)&INT_MAX);
		}
	Num.resize();
	return Num;
	}
	
int_256 operator+ (int other){
	int_256 newNum(*this);
	for(size_t i =0; i < _size; ++i){
		long otherD = !i?0L:(long)other;
		long temp = (long)newNum[i] + otherD;
		newNum[i] = (int)(temp&INT_MAX);
		newNum[i+1]=(int)((temp>>31)&INT_MAX);
	}
	newNum.resize();
	return newNum;
	}


int_256 operator* (int_256 other){
	int_256* larger;
	int_256* smallr;
	if(_size > other.size()){
		larger = &(*this);
		smallr = &other;
		}
	else{
		larger = &other;
		smallr = &(*this);
		}

	int_256 Num(_size+other.size()+2);//is this necessary
	for(size_t i = 0; i < larger->size();++i){
		for(size_t j = 0; j < smallr->size();++j){
			long temp = (long)(*larger)[i]*(long)(*smallr)[j] + (long)Num[i+j];
			Num[i+j] = (int)(temp&INT_MAX);
			Num[i+j+1] = (int)((temp >> 31)&INT_MAX);
			Num[i+j+2] = (int)((temp >> 62)&INT_MAX);
			}
		}
	Num.resize();
	return Num;
	}

int_256 operator* (int other){
	int_256 Num(_size+2);
	for(size_t i = 0; i < _size;++i){
		long temp = (long)data[i] * (long)other + Num[i];
		Num[i] = (int)(temp&INT_MAX);
		Num[i+1] = (int)((temp >> 31)&INT_MAX);
		Num[i+2] = (int)((temp >> 62)&INT_MAX);
		}
	Num.resize();
	return Num;
	}
	



};


std::ostream& operator<<(std::ostream& os,const int_256& l256){
	os << std::to_string(l256[l256.size()-1]);//No need for zero extension
	std::string zeroExtension,newLong;
	for(size_t i = 2; i <= l256.size();++i){
		newLong = std::to_string(l256[l256.size()-i]);
		zeroExtension.clear();
		zeroExtension.append(10-newLong.length(),'0');//TODO make digit length compile time found
		os << ","+zeroExtension + newLong;
	}
	return os;
}

#endif
