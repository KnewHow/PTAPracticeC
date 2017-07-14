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
					addQueue(queues[j], counter++);
				}
			}
		}
		return 0;
	}
}

void getInputArray(int a[], int length) {
	for (int i = 0; i < length; i++) {
		scanf("%d", &a[i]);
	}
}

void getTime(ptrQueue queues[], int customers[], int n, int m, int k, int flag,
		int time[]) {
	int counter = n * m;
	for (int i = 0; i < END_SECONDS + 1; i++) {
		for (int j = 0; j < n; j++) {
			ptrQueue queue = queues[j];
			if (isQueueEmpty(queue)) {
				continue;
			} else {
				if (customers[queue->font->element] != 0) {
					customers[queue->font->element]--;
				} else {
					time[queue->font->element] = i;
					deleteQueue(queue);
					if (!isQueueEmpty(queue)) {
						customers[queue->font->element]--;
					}
					if (flag && counter < k) {
						addQueue(queue, counter++);
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
	}else{
		printf("%d",hour);
	}
	printf(":");
	if (min == 0) {
		printf("00\n");
	} else {
		if (getDigital(min) == 1) {
			printf("0%d\n", min);
		}else{
			printf("%d\n",min);
		}
	}

}

void getQueries(int result[], int k, int queries[], int q) {
	for (int i = 0; i < q; i++) {
		int index = queries[i];
		index--;
		if (result[index] <= END_SECONDS) {
			int time = result[index];
			int hour = time / 60 + 8;
			int min = time % 60;
			formateString(hour, min);
//			printf("%d:%d\n",hour,min);
		} else {
			printf("Sorry\n");
		}
	}
}

int main() {
	int n, m, k, q;
	scanf("%d %d %d %d", &n, &m, &k, &q);
	int customers[k];
	int queries[q];
	ptrQueue queues[n];
	int result[k];
	getInputArray(customers, k);
	getInputArray(queries, q);
	int flag = initQueues(queues, n, m, k);
	for (int i = 0; i < k; i++) {
		result[i] = END_SECONDS + 1;
	}
	getTime(queues, customers, n, m, k, flag, result);
	getQueries(result, k, queries, q);
	return 0;
}

