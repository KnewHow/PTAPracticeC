/*
 * code.c
 *
 *  Created on: Jul 12, 2017
 *      Author: ygh
 */
#include <stdio.h>
#include <stdlib.h>

#define INFINITE 65535
#define MAX_NODE_NUM 1000

/**
 * Use a adjacent matrix to store a graph
 */
typedef struct node *ptrGraph;
struct node {
	int node_num;
	int edge_num;
	int matrix[MAX_NODE_NUM][MAX_NODE_NUM];
};

ptrGraph createGraph(int n, int m) {
	ptrGraph graph = (ptrGraph) malloc(sizeof(struct node));
	graph->node_num = n;
	graph->edge_num = m;
	/**
	 * Initialize adjacent matrix
	 */
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			graph->matrix[i][j] = INFINITE;
		}
	}
	return graph;
}

void construtGraph(ptrGraph graph) {
	int source, destination;
	for (int i = 0; i < graph->edge_num; i++) {
		scanf("%d %d", &source, &destination);
		source--;
		destination--;
		graph->matrix[source][destination] = 1;
		graph->matrix[destination][source] = 1;
	}
}

/*=======================Define a queue==========================*/
typedef struct node2 *ptrList;
struct node2 {
	int element;
	struct node2 *next;
};

typedef struct node3 *ptrQueue;
struct node3 {
	struct node2 *font;
	struct node2 *rear;
};

ptrQueue createEmptyQueue() {

	ptrQueue queue = (ptrQueue) malloc(sizeof(struct node3));
	queue->font = queue->rear = NULL;
	return queue;
}

int isQueueEmpty(ptrQueue queue) {
	return (queue->font == NULL);
}

void insertQueue(ptrQueue queue, int nodeIndex) {
	if (isQueueEmpty(queue)) {
		ptrList list = (ptrList) malloc(sizeof(struct node2));
		list->element = nodeIndex;
		list->next = NULL;
		queue->rear = list;
		queue->font = list;
	} else {
		ptrList list = (ptrList) malloc(sizeof(struct node2));
		list->element = nodeIndex;
		list->next = queue->rear->next;
		queue->rear->next = list;
		queue->rear = list;
	}

}

int deleteFromQueue(ptrQueue queue) {
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
	} else {
		return -1;
	}
}

int isAllVisited(int visited[], int length) {
	for (int i = 0; i < length; i++) {
		if (!visited[i]) {
			return i;
		}
	}
	return -1;
}

void BFS(ptrGraph graph, int startPoint, int visited[]) {
	ptrQueue queue = createEmptyQueue();
	visited[startPoint] = 1;
	for (int i = 0; i < graph->node_num; i++) {
		if (graph->matrix[startPoint][i] != INFINITE) {
			insertQueue(queue, i);
		}
	}
	while (!isQueueEmpty(queue)) {
		int index = deleteFromQueue(queue);
		visited[index] = 1;
		for (int i = 0; i < graph->node_num; i++) {
			if (graph->matrix[index][i] != INFINITE && !visited[i]) {
				insertQueue(queue, i);
			}
		}
	}
}
/**
 * Use DFS will be more effective
 */
void DFS(ptrGraph graph, int startPoint, int visited[]) {
	visited[startPoint] = 1;
	for (int i = 0; i < graph->node_num; i++) {
		if (graph->matrix[startPoint][i] != INFINITE && !visited[i]) {
			DFS(graph, i, visited);
		}
	}
}

int findNumberOfConnectedGraph(ptrGraph graph, int lostPoint) {
	int visited[graph->node_num];
	for (int i = 0; i < graph->node_num; i++) {
		visited[i] = 0;
	}
	visited[lostPoint] = 1;
	int startPoint = isAllVisited(visited, graph->node_num);
	int counter = 0;
	while (startPoint != -1) {
		DFS(graph, startPoint, visited);
		counter++;
		startPoint = isAllVisited(visited, graph->node_num);
	}
	return counter;
}

void getNeedleRaepairedRoad(ptrGraph graph, int k) {
	int roads[k];
	int record[graph->node_num];
	int node;
	for (int i = 0; i < k; i++) {
		scanf("%d", &node);
		node--;
		for (int j = 0; j < graph->node_num; j++) {
			record[j] = graph->matrix[j][node];
			graph->matrix[j][node] = INFINITE;
		}
		roads[i] = findNumberOfConnectedGraph(graph, node);
		for (int j = 0; j < graph->node_num; j++) {
			graph->matrix[j][node] = record[j];
		}
	}

	for (int i = 0; i < k; i++) {
		printf("%d\n", roads[i] - 1);
	}
}

int main() {
	int n, m, k;
	scanf("%d %d %d", &n, &m, &k);
	ptrGraph graph = createGraph(n, m);
	construtGraph(graph);
	getNeedleRaepairedRoad(graph, k);
	return 0;
}

