#include <iostream>
#include <fstream>
#include <cmath>
#include <cassert>
#include "Matrix.h"

int main() {
	Matrix m11(3,4,0);
	m11.set(0,0,1);
	m11.set(0,1,2);
	m11.set(0,2,3);
	m11.set(0,3,4);

	m11.set(1,0,5);
	m11.set(1,1,6);
	m11.set(1,2,7);
	m11.set(1,3,8);

	m11.set(2,0,9);
	m11.set(2,1,10);
	m11.set(2,2,11);
	m11.set(2,3,12);

	m11.swap_row(1,2);
	std::cout<<m11<<std::endl;
	m11.resize(1,2,0);
	std::cout<<m11<<std::endl;
	m11.resize(5,1,0);
	std::cout<<m11<<std::endl;
	m11.resize(5,5,4);
	std::cout<<m11<<std::endl;
	m11.clear();
	return 0;

}