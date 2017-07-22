/*
 * code.c
 *
 *  Created on: Jul 21, 2017
 *      Author: ygh
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_RECORD 1000
#define DAY_HOUR 24
#define MAX_NAME_LENGTH 20
#define MAX_STATUS_LENGTH 8

const char on_line[] = "on_line";
const char off_line[] = "off_line";

/**
 * A integer array to store toll
 * the value in index for 0 to 23 to store toll by 24 hour
 * the value in index 24 is store sum from 0 to 23
 */
int toll[DAY_HOUR + 1];

/**
 * A data structure to store the call recodes
 */
struct node {
	char name[MAX_NAME_LENGTH + 1];
	int month;
	int day;
	int hour;
	int minute;
	int flag;
};

struct node records[MAX_RECORD];

void getToll() {
	int value;
	int sumValue = 0;
	for (int i = 0; i < DAY_HOUR; i++) {
		scanf("%d", &value);
		toll[i] = value;
		sumValue = sumValue + value;
	}
	toll[DAY_HOUR] = sumValue;
}

void getRecords(int n) {
	char name[MAX_NAME_LENGTH + 1];
	char status[MAX_STATUS_LENGTH];
	for (int i = 0; i < n; i++) {
		scanf("%s", name);
		strcpy(records[i].name, name);
		scanf("%d:%d:%d:%d", &records[i].month, &records[i].day,
				&records[i].hour, &records[i].minute);
		scanf("%s", status);
		if (strcmp(status, on_line) == 0) {
			records[i].flag = 0;
		} else {
			records[i].flag = 1;
		}
	}
}

void toString(int n) {
	for (int i = 0; i < n; i++) {
		printf("%s", records[i].name);
		printf(" %d:%d:%d:%d", records[i].month, records[i].day,
				records[i].hour, records[i].minute);
		printf(" %d\n", records[i].flag);
	}
}

int main() {
	int n;
	getToll();
	scanf("%d", &n);
	getRecords(n);
	toString(n);
	printf("just test");
}

