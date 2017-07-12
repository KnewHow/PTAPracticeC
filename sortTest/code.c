/*
 * code.c
 *
 *  Created on: Jul 10, 2017
 *      Author: ygh
 */
#include <stdlib.h>
#include <stdio.h>

int compare(const void *a,const void *b){
	return *((int *)a)-*((int*)b);
}


void toString(int a[],int len){
	for(int i=0;i<len;i++){
		printf("%d ",a[i]);
	}
}

int main(){
	int a[5]={5,4,3,2,1};
	toString(a,5);
	qsort(a,sizeof(a)/sizeof(a[0]),sizeof(int),compare);
	toString(a,5);
	return 0;
}

