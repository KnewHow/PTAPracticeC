/*
 * code.c
 *
 *  Created on: Jun 12, 2017
 *      Author: ygh
 */
#include <stdio.h>
#include <stdbool.h>

/**
 * Define the type of the index
 */
typedef int index;

/*
 * Fill a array with value
 * @param arr The array need to be filled
 * @param length The length of the array
 * @param filledValue The value the array will be filled
 */
void fullArray(int *arr, int length, int filledValue) {
	int i;
	for (i = 0; i < length; i++) {
		arr[i] = filledValue;
	}
}

/*
 * Fill a bool array with value
 * @param arr The array need to be filled
 * @param length The length of the array
 * @param filledValue The value the array will be filled
 */
void fullArrayBool(bool *arr, int length, int filledValue) {
	int i;
	for (i = 0; i < length; i++) {
		arr[i] = filledValue;
	}
}

/**
 * Build relationship between parents nodes and children nodes
 * @param relation A integer array to sore the relation
 * @param isLeaf A boolean array to indicate whether this element is leaf nodes,in order to reduce search times
 * @param The amount of the no-leaf nodes
 */
void buildRelation(int relation[], bool isLeaf[], int no_leafNodes) {
	int i, j, childMount;
	index parentId, childId;
	for (i = 0; i < no_leafNodes; i++) {
		scanf("%d %d", &parentId, &childMount);
		parentId--;
		isLeaf[parentId] = false;
		for (j = 0; j < childMount; j++) {
			scanf("%d", &childId);
			childId--;
			relation[childId] = parentId;
		}
	}
}

void findLevelLeaf(int relation[], bool isLeaf[], int totalNodes) {
	int i = 0, length = 0, counter = 0, j, newLength;
	/**
	 * @param tempParent An integer array to store parent index temporary
	 * @param tempChild An integer array to store children index temporary
	 */
	index tempParent[totalNodes], tempChild[totalNodes];
	length = 0;
	for (i = 0; i < totalNodes; i++) {
		if (relation[i] == -1) {
			tempParent[length++] = i;
		}
	}

	while (length != 0) {
		newLength = 0;
		counter = 0;
		/**
		 * Find the same level all children nodes
		 */
		for (i = 0; i < length; i++) {
			if (isLeaf[tempParent[i]]) {
				counter++;
				continue;
			}
			for (j = 0; j < totalNodes; j++) {
				if (relation[j] == tempParent[i]) {
					tempChild[newLength++] = j;
				}

			}
		}
		printf("%d", counter);
		length = newLength;
		if (length != 0) {
			printf(" ");
			for (i = 0; i < length; i++) {
				tempParent[i] = tempChild[i];
			}
		}
	}
}

/**
 * A toString method just to check
 */
void toString(int relation[], int size) {
	int i;
	for (i = 0; i < size; i++) {
		printf("%d %d\n", i, relation[i]);
	}
}

int main() {
	int totalNodes, no_leafNodes;
	scanf("%d %d", &totalNodes, &no_leafNodes);
	int relation[totalNodes];
	bool isLeaf[totalNodes];
	fullArray(relation, totalNodes, -1);
	fullArrayBool(isLeaf, totalNodes, true);
	buildRelation(relation, isLeaf, no_leafNodes);
	findLevelLeaf(relation, isLeaf, totalNodes);
	return 0;
}

