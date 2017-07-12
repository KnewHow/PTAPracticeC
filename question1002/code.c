/*
 * code.c
 *
 *  Created on: 2017年6月5日
 *      Author: ygh
 *  Algorithms thoughts:
 *  We will use tow linked lists for polynomial A
 *  and B,then traversal them to get sum
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct node *ptrPoly;
typedef struct node {
	/**
	 * The exponents for the polynomial
	 */
	int exponents;
	/**
	 * The coefficient for polynomial
	 */
	double coefficient;

	/**
	 * A point to point next polynomial term
	 */
	struct node *next;
};

ptrPoly buildPoly(int size) {
	ptrPoly head = (ptrPoly) malloc(sizeof(struct node));
	ptrPoly rear = head;
	int exponents;
	double coefficient;
	int i;
	head->next = NULL;
	for (i = 0; i < size; i++) {
		scanf("%d %lf", &exponents, &coefficient);
		ptrPoly p = (ptrPoly) malloc(sizeof(struct node));
		p->exponents = exponents;
		p->coefficient = coefficient;
		p->next = rear->next;
		rear->next = p;
		rear = p;
	}
	return head;
}

void release(ptrPoly head) {
	ptrPoly p = head->next;
	ptrPoly temp;
	while (p) {
		temp = p;
		p = p->next;
		free(temp);
	}
	free(head);
}

void add(ptrPoly *rear, ptrPoly p) {
	ptrPoly temp = (ptrPoly) malloc(sizeof(struct node));
	temp->exponents = p->exponents;
	temp->coefficient = p->coefficient;
	temp->next = (*rear)->next;
	(*rear)->next = temp;
	(*rear) = temp;
}

/**
 * A method implement two polynomials add
 */
ptrPoly getSum(ptrPoly a, ptrPoly b) {
	ptrPoly head = (ptrPoly) malloc(sizeof(struct node));
	ptrPoly rear = head;
	ptrPoly p = a->next;
	ptrPoly q = b->next;
	while (p && q) {
		if (p->exponents > q->exponents) {
			add(&rear, p);
			p = p->next;
		} else if (p->exponents < q->exponents) {
			add(&rear, q);
			q = q->next;
		} else {
			ptrPoly temp = (ptrPoly) malloc(sizeof(struct node));
			/**
			 * If the coefficient add is equal 0,we will not to
			 * add it
			 */
			if (p->coefficient + q->coefficient != 0) {
				temp->exponents = p->exponents;
				temp->coefficient = p->coefficient + q->coefficient;
				temp->next = NULL;
				add(&rear, temp);
				free(temp);
			}
			p = p->next;
			q = q->next;
		}
	}
	while (p) {
		add(&rear, p);
		p = p->next;
	}
	while (q) {
		add(&rear, q);
		q = q->next;
	}
	return head;
}

void toString(ptrPoly head) {
	ptrPoly p = head->next;
	int cnt = 0, i = 0;
	while (p) {
		cnt++;
		p = p->next;
	}
	if (cnt == 0) {
		printf("%d", cnt);
	} else {
		printf("%d ", cnt);
	}
	p = head->next;
	while (p) {
		i++;
		if (i == cnt) {
			printf("%d %.1lf", p->exponents, p->coefficient);
		} else {
			printf("%d %.1lf ", p->exponents, p->coefficient);
		}

		p = p->next;
	}
	printf("\n");
}

int main() {
	int aSize, bSize;
	ptrPoly aPloy, bPloy, sum;
	scanf("%d", &aSize);
	aPloy = buildPoly(aSize);
	scanf("%d", &bSize);
	bPloy = buildPoly(bSize);
	sum = getSum(aPloy, bPloy);
	toString(sum);
	release(aPloy);
	release(bPloy);
	release(sum);
	return 0;
}
