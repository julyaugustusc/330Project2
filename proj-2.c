//Name: Augustus Crosby 

#include "sem.h"

#define SIZE_BUFF 10

struct sem* empty;
struct sem* full;

int buff[SIZE_BUFF];
int in = 0;
int out = 0;

void buffStart() {
	for(int i = 0; i < SIZE_BUFF; i++){
		buff[i] = 0;
	}
	return;
}

void producer1() {
	for(;;) {
		P(empty);
		buff[in] = 1;
		in = (in + 1) % SIZE_BUFF;
		printf("Producer 1:\nBUFFER:");
		for (int i = 0; i < SIZE_BUFF; i++) {
			printf("\n1: %d", buff[i]);
		}
		printf("\n");
		sleep(1);
		V(full);
		return;
	}
} 

void producer2() {
	for(;;) {
		P(empty);
		buff[in] = 1;
		in = (in + 1) % SIZE_BUFF;

		printf("Producer 2:\nBUFFER:");
		for (int i = 0; i < SIZE_BUFF; i++) {
			printf("\n1: %d", buff[i]);
		}
		printf("\n");
		sleep(1);
		V(full);
		return;
	}
} 

void consumer1() {
	for(;;) {
		P(full);
		buff[out] = 0;
		out = (out + 1) % SIZE_BUFF;
		
		printf("Consumer 1:\nBUFFER:");
		for (int i = 0; i < SIZE_BUFF; i++) {
			printf("\n1: %d", buff[i]);
		}
		printf("\n");
		sleep(1);
		V(empty);
	}
}

void consumer2() {
	for(;;) {
		P(full);
		buff[out] = 0;
		out = (out + 1) % SIZE_BUFF;
		
		printf("Consumer 2:\nBUFFER:");
		for (int i = 0; i < SIZE_BUFF; i++) {
			printf("\n1: %d", buff[i]);
		}
		printf("\n");
		sleep(1);
		V(empty);
	}
}
		

//method 2
int main() {
	full = (struct sem*) malloc(sizeof(struct sem));
	empty = (struct sem*) malloc(sizeof(struct sem));
	RunQ = (struct queue*) malloc(sizeof(struct queue));

	InitQueue(RunQ);
	InitSem(empty, SIZE_BUFF);
	InitSem(full, 0);
	buffStart();
	
	start_thread(producer1);
	start_thread(producer2);
	start_thread(consumer1);
	start_thread(consumer2);
	run();
	
	return 0;
}