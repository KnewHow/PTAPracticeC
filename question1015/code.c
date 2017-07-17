/*
 * code.c
 *
 *  Created on: Jul 17, 2017
 *      Author: ygh
 */

#include <stdio.h>
#include <math.h>

int isPrime(int n) {
	if (n <= 1) {
		return 0;
	}
	int flag = 1;
	for (int i = 2; i <= (int) sqrt(n); i++) {
		if (n % i == 0) {
			flag = 0;
			break;
		}
	}
	return flag;
}

int transfer_D_radix(int n, int d, int temp[]) {
	int counter = 0;
	while (n != 0) {
		temp[counter++] = n % d;
		n = n / d;
	}
	return counter;
}

int getReverseDecimalNumber(int n, int d) {
	int temp[100];
	int counter = transfer_D_radix(n, d, temp);
	int number = 0;
	for (int i = 0; i < counter; i++) {
		number = number * d + temp[i];
	}
	return number;
}

void solve() {
	int n, d;
	scanf("%d %d", &n, &d);
	while (n >= 0) {
		if (!isPrime(n)) {
			printf("No\n");
		} else {
			int number = getReverseDecimalNumber(n, d);
			if (isPrime(number)) {
				printf("Yes\n");
			} else {
				printf("No\n");
			}
		}
		scanf("%d %d", &n, &d);
	}
}

int main(int argc, char **argv) {
	solve();
	return 0;
}

