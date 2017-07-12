/*
 * code.c
 *
 *  Created on: 2017年6月4日
 *      Author: ygh
 * Algorithms thoughts:
 * we get the sum first,then use sum % 10 to get each digits and record
 * in a char array and add "," each tree times
 */
#include <stdio.h>
#include <stdlib.h>
#define MAX_LENGTH 50
/**
 * Implement format output
 */
void formatOutput(int sum) {
	char arr[MAX_LENGTH];
	int i = 0, j = 0;
	char ch;
	while (sum) {
		/**
		 * Transform 0~9 number into '0'~'9'
		 */
		ch = (sum % 10) + 48;
		arr[j++] = ch;
		i++;
		if (i % 3 == 0 && sum >= 10) {
			arr[j++] = ',';
		}
		sum = sum / 10;
	}
	arr[j] = '\0';
	/**
	 * Output array DESC
	 */
	for (j = j - 1; j >= 0; j--) {
		printf("%c", arr[j]);
	}
}

/**
 * Calculate two number sum and distribute it
 * If the sum smaller than zero,we will get its opposite number,then add
 * '-' before format out put
 * If the sum is a positive number,format input it
 * If the sum is a zero,output it directly.
 */
void sum(int a, int b) {
	int sum = a + b;
	if (sum < 0) {
		printf("-");
		formatOutput(sum * -1);
	} else if (sum > 0) {
		formatOutput(sum);
		printf("\n");
	} else {
		printf("0\n");
	}
}

int main() {
	int a, b;
	scanf("%d %d", &a, &b);
	sum(a, b);
	return 0;
}

