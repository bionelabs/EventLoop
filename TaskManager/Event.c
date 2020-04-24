//
//  Task.c
//  TaskManager
//
//  Created by Cao Phuoc Thanh on 3/23/19.
//  Copyright © 2019 Cao Phuoc Thanh. All rights reserved.
//

#include "Event.h"
#include <time.h>

Event Event_interval(long id, long interval, calback calback) {
    Event event;
    event.id = id;
    event.loop = 1;
    event.interval = interval;
    event.calback = calback;
    event.is_done = 0;
    event.beginTime = clock();
    return event;
}

Event Event_after(long id, long afterTime, calback calback) {
    Event event;
    event.id = id;
    event.loop = 0;
    event.interval = afterTime;
    event.calback = calback;
    event.is_done = 0;
    event.beginTime = clock();
    event.priority = 1;
    return event;
}

Event Event_listen(long id, selector selector){
    Event event;
    event.id = id;
    event.loop = 0;
    event.interval = -1;
    event.calback = NULL;
    event.is_done = 0;
    event.beginTime = clock();
    event.priority = 1;
    event.selector = selector;
    return event;
}

