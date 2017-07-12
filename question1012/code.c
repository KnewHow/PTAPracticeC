/*
 * code.c
 *
 *  Created on: Jul 10, 2017
 *      Author: ygh
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_ID_LENGTH 6

#define MAX_STUDENT 2000

/**
 * Define a data structure for student
 */
struct node {
	/**
	 * The id of student
	 */
	int id;
	/**
	 * The best subject
	 */
	int best;
	/**
	 * A integer to store the scores,three is subject,the last is the average
	 */
	int score[4];
	/**
	 * A integer to store the ranks,three is subject,the last is the average
	 */
	int rank[4];
} studentList[MAX_STUDENT], student;

int flag = -1;

/**
 * Quick sort implement for constructor
 */
int compare(const void *a, const void *b) {
	if (((const struct node*) a)->score[flag]
			< ((const struct node*) b)->score[flag]) {
		return 1;
	} else {
		return -1;
	}
}

void toString(int flag, int n) {
	for (int i = 0; i < n; i++) {
		printf("%d ", studentList[i].score[flag]);
	}
	printf("\n");
}
/**
 * A relation array,the index is the id,the value is the <code>studentList</code> index
 */
int exsit[2000000] = { 0 };

int main() {
	int m, n;
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++) {
		scanf("%d %d %d %d", &studentList[i].id, &studentList[i].score[1],
				&studentList[i].score[2], &studentList[i].score[3]);
		studentList[i].score[0] = (int) (studentList[i].score[1]
				+ studentList[i].score[2] + studentList[i].score[3]) / 3.0;
	}
	/**
	 * Sort for four scores
	 */
	for (flag = 0; flag <= 3; flag++) {
		qsort(studentList, n, sizeof(struct node), compare);
		studentList[0].rank[flag] = 1;
		for (int i = 1; i < n; i++) {
			if (studentList[i].score[flag] == studentList[i - 1].score[flag]) {
				studentList[i].rank[flag] = studentList[i - 1].rank[flag];
			} else {
				studentList[i].rank[flag] = i + 1;
			}
		}
	}

	/**
	 * Get best rank
	 */
	for (int i = 0; i < n; i++) {
		int min = studentList[i].rank[0];
		/**
		 * Build a relation between number and id
		 */
		exsit[studentList[i].id] = i + 1;
		studentList[i].best = 0;
		for (int j = 1; j <= 3; j++) {
			if (studentList[i].rank[j] < min) {
				studentList[i].best = j;
				min = studentList[i].rank[j];
			}

		}
	}
	char s[] = { 'A', 'C', 'M', 'E' };
	for (int i = 0; i < m; i++) {
		int id;
		scanf("%d", &id);
		int temp = exsit[id];
		if (temp) {
			int best = studentList[temp - 1].best;
			printf("%d %c\n", studentList[temp - 1].rank[best], s[best]);
		} else {
			printf("N/A\n");
		}
	}
	return 0;
}
