/*
 * code.c
 *
 *  Created on: Jun 13, 2017
 *      Author: ygh
 */
#include <stdio.h>
#include <math.h>
#define  MAX_LENGTH 100
/**
 * get sum from input data
 */
long long getSum() {
	long long sum = 0;
	char ch = getchar();
	while (ch != '\n') {
		int a = ch - '0';
		sum = sum + a;
		ch = getchar();
	}
	return sum;
}

/**
 * Get all digit by a number and store them in an array
 */
int getDigit(long long sum, int arr[]) {
	int length = 0;
	while (sum) {
		int digit = sum % 10;
		arr[length++] = digit;
		sum = sum / 10;
	}
	return length;
}

int main() {
	long long sum = getSum();
	if(sum==0){
		printf("zero");
		return 0;
	}
	int array[MAX_LENGTH];
	int length = getDigit(sum, array);
	char *a[] = { "zero", "one", "two", "three", "four", "five", "six", "seven",
			"eight", "nine" };
	int i;
	for (i = length - 1; i >= 0; i--) {
		if(i!=0){
			printf("%s ",a[array[i]]);
		}else{
			printf("%s",a[array[i]]);
		}
	}
	return 0;
}

