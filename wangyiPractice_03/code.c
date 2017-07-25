/*
 * code.c
 *
 *  Created on: Jul 25, 2017
 *      Author: ygh
 */

#include <stdio.h>
#include <string.h>
#define MAX_LENGTH 65536

int main() {

	char child[MAX_LENGTH];
	scanf("%s", child);
	int n = strlen(child);
	/**
	 * Use boy to record boy amount
	 * boyCoubter to record move amout
	 * Girl use same method
	 */
	int boyCounter = 0, boy = 0;
	int girlCounter = 0, girl = 0;
	for (int i = 0; i < n; i++) {
		/**
		 * Let boy move to left
		 */
		if (child[i] == 'B') {
			boyCounter = boyCounter + i - boy;
			boy++;
		} else {
			/**
			 * let girl move to left
			 */
			girlCounter = girlCounter + i - girl;
			girl++;
		}
	}
	if (boyCounter > girlCounter) {
		printf("%d\n", girlCounter);
	} else {
		printf("%d\n", boyCounter);
	}
	return 0;
}

