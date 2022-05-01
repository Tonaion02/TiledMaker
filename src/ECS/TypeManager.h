#pragma once






static unsigned int getIndexOfTypeCmps()
{
	static unsigned int i = 0;
	return i++;
}

template<typename Type>
static unsigned int getIndexFromType()
{
	static unsigned int i = getIndexOfTypeCmps();
	return i;
}