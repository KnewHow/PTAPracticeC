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

const char on_line[] = "on-line";
const char off_line[] = "off-line";

int visited[MAX_RECORD] = { 0 };

const int trans = 24 * 60;
int flag = 0;

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
	int time;
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
		int time = records[i].day * trans + records[i].hour * 60
				+ records[i].minute;
		records[i].time = time;
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
		printf(" %d", records[i].time);
		printf(" %d\n", records[i].flag);
	}
}

int cmp(const void*a, const void *b) {
	if (strcmp(((struct node*) a)->name, ((struct node*) b)->name) != 0) {
		return strcmp(((struct node*) a)->name, ((struct node*) b)->name);
	} else {
		return ((struct node*) a)->time - ((struct node*) b)->time;
	}
}

int getSingleMonery(int index) {
	int sumMoney = records[index].day * toll[24] * 60;
	for (int i = 0; i < records[index].hour; i++) {
		sumMoney = sumMoney + toll[i] * 60;
	}
	sumMoney = sumMoney + toll[records[index].hour] * records[index].minute;
	return sumMoney;
}

double getMonery(int index) {
	int m1 = getSingleMonery(index);
	int m2 = getSingleMonery(index + 1);
	return (m2 - m1) / 100.0;
}

void printformate(int i) {
	printf("%02d:%02d:%02d %02d:%02d:%02d", records[i].day, records[i].hour,
			records[i].minute, records[i + 1].day, records[i + 1].hour,
			records[i + 1].minute);
	printf(" %d", records[i + 1].time - records[i].time);
}

void getResult(int n) {
	char currentName[MAX_NAME_LENGTH + 1];
	double sumCherge = 0.0;
	for (int i = 0; i < n - 1; i++) {
		if (!visited[i] && strcmp(records[i].name, records[i + 1].name) == 0
				&& records[i].flag == 0 && records[i + 1].flag == 1) {
			visited[i] = 1;
			visited[i + 1] = 1;
			if (n == 0) {
				break;
			}
			if (flag == 0) {
				strcpy(currentName, records[i].name);
				printf("%s", currentName);
				printf(" %02d\n", records[i].month);
				flag = 1;
			}
			if (strcmp(currentName, records[i].name) == 0) {
				double currentCherge = getMonery(i);
				sumCherge = sumCherge + currentCherge;
				printformate(i);
				printf(" $%.2f\n", currentCherge);
			} else if (strcmp(currentName, records[i].name) != 0) {
				strcpy(currentName, records[i].name);
				printf("Total amount: $%.2f\n", sumCherge);
				sumCherge = 0.0;
				printf("%s", currentName);
				printf(" %02d\n", records[i].month);
				double currentCherge = getMonery(i);
				sumCherge = sumCherge + currentCherge;
				printformate(i);
				printf(" $%.2f\n", currentCherge);
			}

		}
	}
	printf("Total amount: $%.2f\n", sumCherge);

}

int main() {
	int n;
	getToll();
	scanf("%d", &n);
	getRecords(n);
	qsort(records, n, sizeof(struct node), cmp);
//	toString(n);
//	printf("just test");
	getResult(n);
	return 0;
}

