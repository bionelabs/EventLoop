//
//  Task.h
//  TaskManager
//
//  Created by Cao Phuoc Thanh on 3/23/19.
//  Copyright © 2019 Cao Phuoc Thanh. All rights reserved.
//

#ifndef Task_h
#define Task_h

#include <unistd.h>
#include <stdio.h>
#include <time.h>

typedef void (*calback)(long);
typedef void (*selector)(long, void*,...);

typedef struct Event {
    long id;
    long interval;
    int loop;
    int is_done;
    int priority;
    clock_t beginTime;
    void (*calback)(long);
    void (*selector)(long, void*,...);
} Event;

Event Event_interval(long id, long interval, calback calback);
Event Event_after(long id, long afterTime, calback calback);
Event Event_listen(long id, selector selector);

#endif /* Task_h */
