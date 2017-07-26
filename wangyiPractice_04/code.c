/*
 * code.c
 *
 *  Created on: Jul 26, 2017
 *      Author: ygh
 */
#include <stdio.h>

int main() {
	int n, k;
	scanf("%d %d", &n, &k);
	int arr[50];
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}

	for (int i = 0; i < k; i++) {
		int first = arr[0];
		for (int j = 0; j < n - 1; j++) {
			int value = arr[j] + arr[j + 1];
			if (value > 100) {
				value = value % 100;
			}
			arr[j] = value;
		}
		int value = first + arr[n - 1];
		if (value > 100) {
			value = value % 100;
		}
		arr[n - 1] = value;

	}
	for (int k = 0; k < n; k++) {
		printf("%d ", arr[k]);
	}

}

