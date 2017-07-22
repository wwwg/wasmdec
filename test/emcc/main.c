#include <stdio.h>

int main() {
	int val;
	while (1) {
		val += 1;
		if (val < 10) {
			break;
		}
	}
	printf("%s\n", "Hello, wdis!");
	return 0;
}