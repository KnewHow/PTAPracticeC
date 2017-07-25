/*
 * code.c
 *
 *  Created on: Jul 25, 2017
 *      Author: ygh
 */
#include <stdio.h>
#include <math.h>
int getDistanceTwoPoint(int x0, int y0, int x1, int y1) {
	return abs(x0 - x1) + abs(y0 - y1);
}

int main() {

	int n;
	scanf("%d", &n);
	int hengIndex[n];
	int zongIndex[n];
	for (int i = 0; i < n; i++) {
		scanf("%d", &hengIndex[i]);
	}
	for (int i = 0; i < n; i++) {
		scanf("%d", &zongIndex[i]);
	}
	int gx, gy;
	scanf("%d %d", &gx, &gy);
	int walkTime, taxiTime;
	scanf("%d %d", &walkTime, &taxiTime);
	int walkDistance = getDistanceTwoPoint(0, 0, gx, gy);
	int walkTotalTime = walkTime * walkDistance;
	int min = 65536;
	for (int i = 0; i < n; i++) {
		int distance = getDistanceTwoPoint(0, 0, hengIndex[i], zongIndex[i]);
		int time = distance * walkTime;
		int distance2 = getDistanceTwoPoint(hengIndex[i], zongIndex[i], gx, gy);
		time = taxiTime * distance2 + time;
		if (time < min) {
			min = time;
		}
	}
	if (walkTotalTime > min) {
		printf("%d\n", min);
	} else {
		printf("%d\n", walkTotalTime);
	}
	return 0;
}

