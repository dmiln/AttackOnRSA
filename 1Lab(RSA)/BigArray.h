#pragma once

extern "C"
{
#include "miracl.h"
}
#include "big.h"

class BigArray
{
	char* mem;
	int count;
public:
	BigArray(int);
	~BigArray() { memkill(mem, count); }
	Big& operator [] (int index);
};