/*
 * code.c
 *
 *  Created on: Jun 7, 2017
 *      Author: ygh
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ERROR -1
#define INFINITY 6553555

#define MAX_VERTEX 600
/**
 * The type of length between cities
 */
typedef int lengthType;

/**
 * The type of amount of the rescue teams
 */
typedef int amountType;

/**
 * The type of vertex
 */
typedef int vertex;

/**
 * Define a data structure for edge
 */
typedef struct edgeNode *ptrEdge;
typedef struct edgeNode {
	/**
	 * The starting point in this edge
	 */
	vertex startPoint;
	/**
	 * The end point in this edge
	 */
	vertex destination;
	/**
	 * The length between stating point and end point
	 */
	lengthType length;
};

/**
 * Define a data structure for table node in adjacent table
 */
typedef struct tableNode *ptrTNode;
typedef struct tableNode {
	/**
	 * The point the vertex can reach
	 */
	vertex destination;

	/**
	 * The length between vertex and destination
	 */
	lengthType length;

	/**
	 * A point to point next point
	 */
	struct tableNode *next;
};

/**
 * Define a data structure for head point in adjacent table
 */
typedef struct headNode {
	amountType teams;
	ptrTNode head;
} listHead[MAX_VERTEX];

/**
 * Define a data structure for graph overview
 */
typedef struct graphNode *ptrAdjLGraph;
typedef struct graphNode {
	/**
	 * The amount for vertexes
	 */
	int vertexNumber;
	/**
	 * The amount for edges
	 */
	int edgeNumber;
	/**
	 * The list for all head nodes
	 */
	listHead headList;
};

/**
 * Create a empty graph by vertex amounts,then return a point for graph
 * @param graphNode The amount of the vertex number
 * @return Return a point for graph
 */
ptrAdjLGraph createEmptyGraph(int vertexNumber) {
	ptrAdjLGraph graph = (ptrAdjLGraph) malloc(sizeof(struct graphNode));
	vertex v;
	graph->vertexNumber = vertexNumber;
	graph->edgeNumber = 0;
	for (v = 0; v < graph->vertexNumber; v++) {
		graph->headList[v].teams = 0;
		graph->headList[v].head = NULL;
	}
	return graph;
}

/**
 * Insert a edge into a graph
 * @param graph A point for graph
 * @param edge A edge will be inserted into this graph
 * @param isDirected Whether the graph is directed graph. True represent directed,otherwise non-directed
 */
void insertGraph(ptrAdjLGraph graph, ptrEdge edge, bool isDirected) {
	ptrTNode newNode = (ptrTNode) malloc(sizeof(struct tableNode));
	newNode->destination = edge->destination;
	newNode->length = edge->length;
	newNode->next = graph->headList[edge->startPoint].head;
	graph->headList[edge->startPoint].head = newNode;
	if (isDirected == false) {
		ptrTNode newNode = (ptrTNode) malloc(sizeof(struct tableNode));
		newNode->destination = edge->startPoint;
		newNode->length = edge->length;
		newNode->next = graph->headList[edge->destination].head;
		graph->headList[edge->destination].head = newNode;
	}
}

/**
 * Build a graph by input data
 * @return Return a point for graph
 * @param isDirected Whether the graph is directed graph. True represent directed,otherwise non-directed
 */
ptrAdjLGraph buildGraph(int vertexNumber, int edgeNumber, bool isDirected) {
	vertex v;
	ptrEdge edge;
	amountType teams;
	int i;
	ptrAdjLGraph graph = createEmptyGraph(vertexNumber);
	graph->edgeNumber = edgeNumber;
	for (v = 0; v < graph->vertexNumber; v++) {
		scanf("%d", &teams);
		graph->headList[v].teams = teams;
	}
	edge = (ptrEdge) malloc(sizeof(struct edgeNode));
	for (i = 0; i < graph->edgeNumber; i++) {
		scanf("%d %d %d", &edge->startPoint, &edge->destination, &edge->length);
		insertGraph(graph, edge, isDirected);
	}
	free(edge);
	return graph;
}

/*
 * Find the the index of point in the graph whose dist is minimal and has not been
 * accessed.
 * @param graph A graph which use adjacent matrix to store
 * @param isVisited A integer array to show whether the point has been accessed
 * 		0 indicates the point has not been accessed,`1 indicates the point has been accessed
 * 		the index in collection is same as the graph
 * @param dist A integer array to store the length from source to destination, it will be initialize with 65535 at first
 */
vertex findMinDist(ptrAdjLGraph graph, const bool isVisited[],
		const lengthType dist[]) {
	vertex v, minVertex;
	lengthType minLength = INFINITY;
	for (v = 0; v < graph->vertexNumber; v++) {
		if (isVisited[v] == false && dist[v] < minLength) {
			minVertex = v;
			minLength = dist[v];
		}
	}

	if (minLength == INFINITY) {
		return ERROR;
	} else {
		return minVertex;
	}
}

/**
 * Solve problem.
 * @param graph A point for graph
 * @param startPoint The starting point
 * @param shortestPathNumber The shortest path amount will record in this array.If there shortest equal,
 * 	we update it
 *
 * @param dist A array to record the length of shortest path,we will initialize it to INFINITY
 * 	If we find a shorter path than previous ,we will update it.
 *
 * @param teamNumber A array to record most teams we can gather,we will initialize it to zero
 */
void save(ptrAdjLGraph graph, vertex startPoint, int shortestPathNumber[],
		lengthType dist[], amountType teamNumber[]) {
	/**
	 * A array to flag whether the vertex has been access
	 */
	bool isVisited[graph->vertexNumber];
	ptrTNode w;
	vertex v;
	/**
	 * Initialize isVisited to false
	 */
	for (v = 0; v < graph->vertexNumber; v++) {
		isVisited[v] = false;
	}
	/**
	 * Setting starting point gather teams is itself
	 */
	teamNumber[startPoint] = graph->headList[startPoint].teams;
	w = graph->headList[startPoint].head;
	while (w) {
		/**
		 * update the adjacent distance
		 */
		dist[w->destination] = w->length;
		/**
		 * Update the shortest path into 1
		 */
		shortestPathNumber[w->destination] = 1;
		/**
		 * Update teams amount into starting point adding itself
		 */
		teamNumber[w->destination] = teamNumber[startPoint]
				+ graph->headList[w->destination].teams;
		w = w->next;
	}

	isVisited[startPoint] = true;
	dist[startPoint] = 0;
	shortestPathNumber[startPoint] = 1;
	while (1) {
		v = findMinDist(graph, isVisited, dist);
		if (v == ERROR) {
			break;
		}
		isVisited[v] = true;
		w = graph->headList[v].head;
		while (w) {
			if (isVisited[w->destination] == true) {
				w = w->next;
				continue;
			}
			if (dist[v] + w->length < dist[w->destination]) {
				/**
				 * If shortest is not equal,update teamNumber into add and shortestPathNumber into parent vertex
				 */
				dist[w->destination] = dist[v] + w->length;
				teamNumber[w->destination] = teamNumber[v]
						+ graph->headList[w->destination].teams;
				shortestPathNumber[w->destination] = shortestPathNumber[v];
			} else if (dist[v] + w->length == dist[w->destination]) {
				/**
				 * If the shortest equal,update the shortestPathNumber into sum of the itself and current point
				 *
				 */
				shortestPathNumber[w->destination] =
						shortestPathNumber[w->destination]
								+ shortestPathNumber[v];
				/**
				 * Update the bigger teams between of two equal paths
				 */
				if (teamNumber[v] + graph->headList[w->destination].teams
						> teamNumber[w->destination]) {
					teamNumber[w->destination] = teamNumber[v]
							+ graph->headList[w->destination].teams;
				}
			}
			w = w->next;
		}
	}
}

/**
 * Release graph
 */
void releaseGraph(ptrAdjLGraph graph) {
	vertex v;
	ptrTNode temp = NULL, head = NULL;
	for (v = 0; v < graph->vertexNumber; v++) {
		head = graph->headList[v].head;
		while (head) {
			temp = head;
			head = head->next;
			free(temp);
		}
	}
	free(head);
	free(graph);

}

void toString(ptrAdjLGraph graph) {
	printf("vertexNumber:%d\n", graph->vertexNumber);
	printf("edgeNumber:%d\n", graph->edgeNumber);
	vertex v;
	for (v = 0; v < graph->vertexNumber; v++) {
		ptrTNode head = graph->headList[v].head;
		printf("source:%d,teams:%d\n", v, graph->headList[v].teams);
		while (head) {
			printf("destination:%d length:%d ", head->destination,
					head->length);
			head = head->next;
		}
		printf("\n");
	}
}

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

int main() {
	int vertexNumber, edgeNumber;
	vertex source, destination;
	scanf("%d %d %d %d", &vertexNumber, &edgeNumber, &source, &destination);
	ptrAdjLGraph graph = buildGraph(vertexNumber, edgeNumber, false);
	int shortestPathNumber[graph->vertexNumber];
	lengthType dist[graph->vertexNumber];
	amountType teamNumber[graph->vertexNumber];
	fullArray(shortestPathNumber, graph->vertexNumber, 0);
	fullArray(dist, graph->vertexNumber, INFINITY);
	fullArray(teamNumber, graph->vertexNumber, 0);
	save(graph, source, shortestPathNumber, dist, teamNumber);
	printf("%d %d\n", shortestPathNumber[destination], teamNumber[destination]);
	releaseGraph(graph);
	return 0;
}
