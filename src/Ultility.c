#include "../include/Ultility.h"
#include <stdint.h>
#include <stdio.h>



void ToBinary(uint32_t num, char* vect)
{
	const char bin[] = {'0', '1'};
	char buff[10] = {0};
	uint32_t temp;
	uint32_t i = 0;
	char *ptr;

	ptr = &buff[9];

	if(num == 0)
	{
		vect[0] = '0';
		vect[1] = '\0';
	}

	else
	{
		ptr--;
		while(num > 0)
		{
			temp = num % 2;
			*ptr = bin[temp];
			ptr--;
			num /= 2;
		}
		ptr++;
		while(ptr < (buff + 10))
		{
			*vect = *ptr;
			vect++;
			ptr++;
		}
	}
}