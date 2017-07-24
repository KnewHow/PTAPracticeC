/*
 * code.c
 *
 *  Created on: Jul 24, 2017
 *      Author: ygh
 */

#include <stdio.h>
#include <stdlib.h>
int getInputData(int arr[], int n) {
	int value;
	int sum = 0;
	for (int i = 0; i < n; i++) {
		scanf("%d", &value);
		arr[i] = value / 1024;
		sum = sum + arr[i];
	}
	return sum;
}

/**
 * Packet problem
 */
int packetProblem(int n, int sum, int arr[]) {
	int c = sum / 2;
	int d[n + 1][c + 1];
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= c; j++) {
			d[i][j] = (i == 0 ? 0 : d[i - 1][j]);
			if (i > 0 && j >= arr[i - 1]) {
				if (d[i][j] < d[i - 1][j - arr[i - 1]] + arr[i - 1]) {
					d[i][j] = d[i - 1][j - arr[i - 1]] + arr[i - 1];
				}
			}
		}
	}
	return d[n][c];
}

int main() {
	int n;
	scanf("%d", &n);
	int arr[n];
	int sum = getInputData(arr, n);
	int max1 = packetProblem(n, sum, arr);
	int max2 = sum - max1;
	if (max1 > max2) {
		printf("%d\n", max1 * 1024);
	} else {
		printf("%d\n", max2 * 1024);
	}
	return 0;
}

