/*
 * code.c
 *
 *  Created on: Jul 18, 2017
 *      Author: ygh
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENTH 20
#define  MAX_CALL_RECORD 1000
#define  MAX_FLAG_LENGTH 8
#define MAX_TOLL_LENGTH 24

const char ON_LINE[] = "on_line";
const char OFF_LINE[] = "off_line";

struct node {
	char name[MAX_NAME_LENTH + 1];
	int on_line[MAX_CALL_RECORD];
	int off_line[MAX_CALL_RECORD];
	int on_line_length;
	int off_line_lenth;
	int sum_charges;

} userList[MAX_CALL_RECORD];

void tranformMinutesIntoTime(int minutes, int time[]) {

	int t = 24 * 60;
	int day = minutes / t;
	int hour = (minutes - day * t) / 60;
	int min = minutes % 60;
	time[0] = day;
	time[1] = hour;
	time[2] = min;
}

void getInputData() {
	int month;
	int day;
	int hour;
	int minutes;
	char name[MAX_NAME_LENTH + 1];
	char flag[MAX_FLAG_LENGTH];
	scanf("%s", name);
	scanf("%d:%d:%d:%d", &month, &day, &hour, &minutes);
	scanf("%s", flag);
}

void getToll(int toll[]) {
	int value;
	for (int i = 0; i < MAX_TOLL_LENGTH; i++) {
		scanf("%d", &value);
		toll[i] = value;
	}
}

int main(int argc, char **argv) {
	int toll[MAX_TOLL_LENGTH];
	char map[MAX_NAME_LENTH + 1];
	getToll(toll);
	printf("\njust test\n");
	return 0;
}
