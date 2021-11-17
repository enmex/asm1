#include "asm1.h"
#include "asm2.h"
#include <assert.h>
#include <stdio.h>

void test_asm1() {

	char* result1 = concat("", 5, 0);

	assert(result1 != NULL);
	//result = ""
	printf("%s\n", result1);

	char* result2 = concat("a", 5, 1);

	assert(result2 != NULL);
	//result = "aaaaa"
	printf("%s\n", result2);

	char* result3 = concat("ab", 5, 2);

	assert(result3 != NULL);
	//result = "ababababab"
	printf("%s\n", result3);

	char* result4 = concat("text", 1, 4);

	assert(result4 != NULL);
	//result = "text"
	printf("%s\n", result4);

	char* result5 = concat("text", 0, 4);

	assert(result5 != NULL);
	//result = ""
	printf("%s\n", result5);

	char* result6 = concat("text", 1, 0);

	assert(result6 != NULL);
	//result = ""
	printf("%s\n", result6);

	printf("%f", ctg(5));
}

int main() {
	test_asm1();
	return 0;
}
