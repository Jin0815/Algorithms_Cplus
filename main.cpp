#include "KMP.h"

int main()
{
	string t = "ababaaabcdedsdfefdfsd";
	string p = "edsd";
	int location = KMP(t,p);
	return 0;
}