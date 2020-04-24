//
//  TaskPool.h
//  TaskPool
//
//  Created by Cao Phuoc Thanh on 3/22/19.
//  Copyright © 2019 Cao Phuoc Thanh. All rights reserved.
//

#ifndef TaskPool_h
#define TaskPool_h

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "Event.h"

typedef void (*selector)(long, void*,...);

typedef struct EventLoop {
    Event (*setInterval)(calback, long);
    Event (*setTimeout)(calback, long);
    Event (*setImmedate)(calback);
    void (*emit)(long, void*,...);
    void (*listen)(long, selector);
    void (*add)(Event);
    void (*remove)(long);
    void (*loop)(void);
    void (*exit)(void);
    int (*count)(void);
    int (*max)(void);
} EventLoop;

EventLoop EventShared(void);

#endif /* TaskPool_h */
