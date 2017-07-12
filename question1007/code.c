/*
 * code.c
 *
 *  Created on: Jun 15, 2017
 *      Author: ygh
 */

#include <stdio.h>

void getData(int a[], int size) {
	int number = 0;
	for (int i = 0; i < size; i++) {
		scanf("%d", &number);
		a[i] = number;
	}
}
int main() {
	int amount;
	scanf("%d", &amount);
	int a[amount];
	getData(a, amount);
	int number = 0;
	int maxSum = 0, currentSum = 0;
	int endIndex = amount - 1;
	int currentCounter = 0, counter = 0;
	for (int i = 0; i < amount; i++) {
		number = a[i];
		currentCounter++;
		currentSum += number;
		if (currentSum > maxSum) {
			maxSum = currentSum;
			counter = currentCounter;
			endIndex = i;
		} else if (currentSum < 0) {
			currentSum = 0;
			currentCounter = 0;
		}
	}

	if (counter == 0) {
		printf("%d %d %d", 0, a[0], a[amount - 1]);
	} else {
		printf("%d %d %d", maxSum, a[endIndex - counter + 1], a[endIndex]);
	}
	return 0;
}
