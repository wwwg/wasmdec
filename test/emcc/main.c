#include <stdio.h>

int doubleValue(int value) {
	return value * 2;
}
int main() {
	// Loop testing
	int val;
	while (1) {
		val += 1;
		if (val < 10) {
			break;
		}
	}
	printf("%s\n", "Hello, wasmdec!");
	// Load / store testing
	val = 0 + 1 + 2 + 3;
	// Function call testing
	int secondVal = doubleValue(val);
	printf("secondVal: %d\n", secondVal);
	return 0;
}