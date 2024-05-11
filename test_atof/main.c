#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./libft/libft.h"
// Include your my_atof function here

int main()
{
	const char *test_cases[] = {
		"0",
		"123",
		"-123",
		"123.456",
		"-123.456",
		"   123.456",
		"123.456   ",
		"   123.456   ",
		".456",
		"-.456",
		"123.",
		"-123.",
		NULL  // End of test cases
	};

	for (int i = 0; test_cases[i] != NULL; i++)
	{
		const char *str = test_cases[i];
		double std_result = atof(str);
		double my_result = my_atof(str);
		printf("Test case \"%s\":\n", str);
		printf("   atof: %f\n", std_result);
		printf("my_atof: %f\n", my_result);
		printf("\n");
	}

	return 0;
}

