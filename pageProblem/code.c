/*
 * code.c
 *
 *  Created on: Jul 24, 2017
 *      Author: ygh
 */

#include <stdio.h>

int main() {
	int n, c;
	scanf("%d %d", &n, &c);
	int v[n];
	int w[n];
	int d[n + 1][c + 1];

	for (int i = 0; i < n; i++) {
		scanf("%d %d", &v[i], &w[i]);
	}
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= c; j++) {
			d[i][j] = (i == 0 ? 0 : d[i - 1][j]);
			if (i > 0 && j >= v[i - 1]) {
				if (d[i][j] < (d[i - 1][j - v[i - 1]] + w[i - 1])) {
					d[i][j] = d[i - 1][j - v[i - 1]] + w[i - 1];
				}
			}
		}
	}

	int x[n];
	int j = c;
	for (int i = n; i > 0; i--) {
		if (d[i][j] > d[i - 1][j]) {
			x[i - 1] = 1;
			j = j - v[i - 1];
		}
	}
	for (int i = 0; i < n; i++) {
		printf("%d ", x[i]);
	}

	printf("\n");
	printf("%d\n", d[n][c]);
	return 0;
}

