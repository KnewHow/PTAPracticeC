/*
 * code.c
 *
 *  Created on: Jun 14, 2017
 *      Author: ygh
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ID_LENGTH 15
typedef char idType;
typedef int secondType;

/**
 * Define a node to store every one id and sign time and sign out time
 */
typedef struct node *ptrRecord;
typedef struct node {
	idType id[MAX_ID_LENGTH];
	secondType signInSeconds;
	secondType signOutSeconds;
	struct node *next;
};

/**
 * Transfer time into seconds
 */
int getSecondes() {
	int hour;
	int minutes;
	int seconds;
	scanf("%d:%d:%d", &hour, &minutes, &seconds);
	return (hour * 3600 + minutes + 60 + seconds);
}

/**
 * Build list from input data
 */
ptrRecord getInputData() {
	ptrRecord head = (ptrRecord) malloc(sizeof(struct node));
	head->next = NULL;
	int totalNum;
	scanf("%d", &totalNum);
	char id[MAX_ID_LENGTH];
	for (int i = 0; i < totalNum; i++) {
		scanf("%s", id);
		secondType signInSecondes = getSecondes();
		secondType signOutSeconds = getSecondes();
		ptrRecord newNode = (ptrRecord) malloc(sizeof(struct node));
		strcpy(newNode->id, id);
		newNode->signInSeconds = signInSecondes;
		newNode->signOutSeconds = signOutSeconds;
		newNode->next = head->next;
		head->next = newNode;
	}

	return head;
}

void toString(ptrRecord head) {
	ptrRecord p = head->next;
	while (p) {
		printf("id:%s inSeconds:%d outSeconds:%d\n", p->id, p->signInSeconds,
				p->signOutSeconds);
		p = p->next;
	}
}

/**
 * release list
 */
void destory(ptrRecord head) {
	ptrRecord p = head->next;
	while (p) {
		ptrRecord temp = p;
		p = p->next;
		free(temp);
	}
	free(head);
}

/**
 * Find the id of minimal in sigiIntime and maximal id in
 * signOutTime
 */
void getRequestId(ptrRecord head) {
	ptrRecord p = head->next;
	idType unlockId[MAX_ID_LENGTH];
	idType lockId[MAX_ID_LENGTH];
	strcpy(unlockId, p->id);
	strcpy(lockId, p->id);
	secondType unlockTime = p->signInSeconds;
	secondType lockTime = p->signOutSeconds;
	p = p->next;
	while (p) {
		if (p->signInSeconds < unlockTime) {
			unlockTime = p->signInSeconds;
			strcpy(unlockId, p->id);
		}
		if (p->signOutSeconds > lockTime) {
			lockTime = p->signOutSeconds;
			strcpy(lockId, p->id);
		}
		p = p->next;
	}

	printf("%s %s", unlockId, lockId);
}

int main() {
	ptrRecord head = getInputData();
	getRequestId(head);
	destory(head);
	return 0;
}
