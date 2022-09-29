#include "../Include/Image.h"

#include <cstdlib>
#include <stdio.h>


int main(int argc, char **argv)
{
	Image test("Ressources/test.jpg");


	for(int i=0; i<test.w*test.channels; ++i)
	{
		test.data[i] = 255;
	}


	test.write("Ressources/new.png");

	return 0;
}