//
//  Queue.c
//  TaskManager
//
//  Created by Cao Phuoc Thanh on 3/23/19.
//  Copyright © 2019 Cao Phuoc Thanh. All rights reserved.
//

#include "TaskQueue.h"

#define QUEUE_SIZE 10

static Task elements[QUEUE_SIZE];
static int front = -1;
static int rear = -1;

int isEmpty(void) {
    return rear == -1;
}

int isFull(void) {
    return rear == QUEUE_SIZE-1;
}

void enQueue(Task element) {
    if(!isFull()) {
        if(front == -1) {
            front = 0;
        }
        rear++;
        elements[rear] = element;
        //printf("inserted id: %lu - front:%i - rear:%i\n", element.id, front, rear);
    }
}

void deQueue(void) {
    if(!isEmpty()) {
        for (int i = front; i <= rear ; i++) {
            elements[i] = elements[i+1];
        }
        rear--;
        if(front > rear) {
            front = rear = -1;
        }
    }
}

Task frontTask(void) {
    return elements[0];
}

int lenght(void) {
    return rear;
}

void display() {
    if(!isEmpty()) {
        printf("\n------------------------\n");
        printf("queue elements:\n");
        for(int i = front; i<=rear; i++) {
            printf("%lu\t",elements[i].id);
        }
        printf("\n------------------------\n");
    }
}

//void dequeue

