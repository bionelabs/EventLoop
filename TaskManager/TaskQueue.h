//
//  Queue.h
//  TaskManager
//
//  Created by Cao Phuoc Thanh on 3/23/19.
//  Copyright © 2019 Cao Phuoc Thanh. All rights reserved.
//

#ifndef Queue_h
#define Queue_h

#include <stdio.h>
#include "Event.h"
#include "Task.h"

typedef void (*calback)(long);

void enQueue(Task task);
void deQueue(void);
void display(void);
int isEmpty(void);
int isFull(void);
Task frontTask(void);
int lenght(void);

#endif /* Queue_h */
