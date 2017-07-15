/*
 * code.c
 *
 *  Created on: Jul 14, 2017
 *      Author: ygh
 */
#include <stdio.h>
#include <stdlib.h>

#define END_SECONDS 540

/**
 * Define a data structure for link list
 */
typedef struct node *ptrList;
struct node {
	int element;
	struct node *next;
};

/**
 * Define a data structure for queue
 */
typedef struct node2 *ptrQueue;
struct node2 {
	struct node *font;
	struct node *rear;
};

ptrQueue createEmptyQueue() {
	ptrQueue queue = (ptrQueue) malloc(sizeof(struct node2));
	queue->font = queue->rear = NULL;
	return queue;
}

int isQueueEmpty(ptrQueue queue) {
	return queue->font == NULL;
}

void addQueue(ptrQueue queue, int index) {
	if (isQueueEmpty(queue)) {
		ptrList node = (ptrList) malloc(sizeof(struct node));
		node->element = index;
		node->next = NULL;
		queue->font = queue->rear = node;
	} else {
		ptrList node = (ptrList) malloc(sizeof(struct node));
		node->element = index;
		node->next = queue->rear->next;
		queue->rear->next = node;
		queue->rear = node;
	}
}

int deleteQueue(ptrQueue queue) {
	if (!isQueueEmpty(queue)) {
		ptrList node = queue->font;
		int element = node->element;
		if (queue->font == queue->rear) {
			queue->font = queue->rear = NULL;
		} else {
			queue->font = queue->font->next;
		}
		free(node);
		return element;
	}
	return -1;
}

int initQueues(ptrQueue queues[], int n, int m, int k) {
	for (int i = 0; i < n; i++) {
		queues[i] = createEmptyQueue();
	}
	if (n * m < k) {
		int counter = 0;
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				addQueue(queues[j], counter++);
			}
		}
		return 1;
	} else {
		int counter = 0;
		while (counter < k) {
			for (int i = 0; i < m; i++) {
				for (int j = 0; j < n; j++) {
					if (counter < k) {
						addQueue(queues[j], counter++);
					}
				}
			}
		}
		return 0;
	}
}

void getInputArray(int a[], int length) {
	int value;
	for (int i = 0; i < length; i++) {
		scanf("%d", &value);
		a[i] = value;
	}
}

void getTime2(ptrQueue queues[], int customers[], int n, int m, int k, int flag,
		int time[], int start[], int origin[]) {
	int counter = n * m;
	for (int i = 0; i < END_SECONDS; i++) {
		for (int j = 0; j < n; j++) {
			ptrQueue queue = queues[j];
			if (isQueueEmpty(queue)) {
				continue;
			} else {
				if (customers[queue->font->element]
						== origin[queue->font->element]) {
					start[queue->font->element] = i + 1;
				}
				customers[queue->font->element]--;
				for (int q = 0; q < n; q++) {
					ptrQueue queue = queues[q];
					if (isQueueEmpty(queue)) {
						continue;
					} else {
						if (customers[queue->font->element] == 0) {
							time[queue->font->element] = i + 1;
							deleteQueue(queue);
							if (flag && counter < k) {
								addQueue(queue, counter++);
							}
						}
					}

				}
			}

		}
	}

}

int getDigital(int num) {
	int couter = 0;
	while (num) {
		num = num / 10;
		couter++;
	}
	return couter;
}

void formateString(int hour, int min) {
	if (getDigital(hour) == 1) {
		printf("0%d", hour);
	} else {
		printf("%d", hour);
	}
	printf(":");
	if (min == 0) {
		printf("00\n");
	} else {
		if (getDigital(min) == 1) {
			printf("0%d\n", min);
		} else {
			printf("%d\n", min);
		}
	}

}

void getQueries(int result[], int start[], int k, int queries[], int q,
		int origin[]) {
	for (int i = 0; i < q; i++) {
		int index = queries[i];
		index--;
		if (result[index] <= END_SECONDS) {
			int time = result[index];
			int hour = time / 60 + 8;
			int min = time % 60;
			formateString(hour, min);
		} else if (start[index] < END_SECONDS) {
			int time = start[index] + origin[index]-1;
			int hour = time / 60 + 8;
			int min = time % 60;
			formateString(hour, min);
		} else {
			printf("Sorry\n");
		}
	}
}


void initArray(int a[], int length, int value) {
	for (int i = 0; i < length; i++) {
		a[i] = value;
	}
}

int main() {
	int n, m, k, q;
	scanf("%d %d %d %d", &n, &m, &k, &q);
	int customers[k];
	int origin[k];
	int queries[q];
	ptrQueue queues[n];
	int result[k];
	int startTime[k];
	initArray(customers, k, 0);
	initArray(customers, k, 540);
	initArray(queries, q, 0);
	initArray(result, k, END_SECONDS + 1);
	getInputArray(customers, k);
	getInputArray(queries, q);
	for (int i = 0; i < k; i++) {
		origin[i] = customers[i];
	}
	int flag = initQueues(queues, n, m, k);
	getTime2(queues, customers, n, m, k, flag, result, startTime, origin);
	getQueries(result,startTime ,k, queries, q,origin);
	return 0;
}

