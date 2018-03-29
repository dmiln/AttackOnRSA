#include "BigArray.h"

BigArray::BigArray(int count)
{
	char *mem = (char *)memalloc(count);
	this->count=count;
}

Big& BigArray::operator[](int index)
{ 
	Big answer=NULL;
	if (index < count&&index>0) 
	{ 
		big x; 
		x = mirvar_mem(mem, index);
		answer = x;
	}
	return answer;
}