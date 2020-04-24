//
//  TaskManager.c
//  TaskManager
//
//  Created by Cao Phuoc Thanh on 3/22/19.
//  Copyright © 2019 Cao Phuoc Thanh. All rights reserved.
//

#include <time.h>
#include "EventLoop.h"
#include "TaskQueue.h"

#define TASK_SIZE 50

static Event _events[TASK_SIZE];
static int _eventLastIndex = 0;
static int _iStarting = 0;
EventLoop* shared;

static long randomEventId() {
    return rand() % 1000000 + 1;
}

void addEvent(Event event) {
    if (_eventLastIndex <TASK_SIZE) {
        printf("*** Add Event id: %lu\n", event.id);
        _events[_eventLastIndex] = event;
        _eventLastIndex ++;
    } else {
        printf("ERROR: Task full");
    }
}

Event setInterval(calback calback, long interval) {
    Event event = Event_interval(randomEventId(), interval, calback);
    addEvent(event);
    return event;
}

Event setTimeout(calback calback, long after) {
    Event event = Event_after(randomEventId(), after, calback);
    addEvent(event);
    return event;
}

Event setImmedate(calback calback){
    Event event = Event_after(randomEventId(), 0, calback);
    addEvent(event);
    return event;
}

void emit(long id, void* value,...) {
    for (int i = 0; i <= _eventLastIndex; i++) {
        if (_events[i].id == id && _events[i].selector != NULL) {
            _events[i].selector(id, value);
            break;
        }
    }
}

void listenEvent(long id, selector value) {
    Event event = Event_listen(id, value);
    addEvent(event);
}

void removeEvent(long id) {
    printf("*** Remove Event id:%lu\n", id);
    int position = -1;
    for (int i = 0; i <= _eventLastIndex; i++) {
        Event event = _events[i];
        if (event.id == id) {
            position = i;
            break;
        }
    }
    if (position == -1) {
        return;
    }
    //printf("removeEvent: %i _eventLastIndex: %i\n", position, _tasks[position].id);
    for (int i = position; i <= _eventLastIndex; i++) {
        _events[i] = _events[i+1];
    }
    _eventLastIndex--;
    //printf("===> remove Task finded %i\n", _eventLastIndex);
}

int isFullTask() {
    return _eventLastIndex < TASK_SIZE;
}

void removeLastTask() {
    //_tasks[_eventLastIndex] = NULL;
    _eventLastIndex--;
}

static void poll() {
    clock_t current_clock = clock();
    for (int i = 0; i <= _eventLastIndex; i++) {
        if (NULL == _events[i].calback) {
            continue;
        }
        clock_t next_task_clock = _events[i].beginTime/1000 + _events[i].interval;
        if (current_clock/1000 > next_task_clock && _events[i].is_done == 0 && _events[i].interval != -1) {
            _events[i].beginTime = current_clock;
            Task task = Task_init(_events[i].id, _events[i].calback);
            printf("==> One Add Task: %lu : %lu : %lu\n", task.id, current_clock - next_task_clock*1000 , _events[i].interval);
            enQueue(task);
            if (_events[i].loop == 0) {
                _events[i].is_done = 1;
            }
        }
    }
    //display();
}

// clear task not use in feature
static void clear() {
    for (int i = 0; i <= _eventLastIndex; i++) {
        if (_events[i].is_done == 1) {
            removeEvent(_events[i].id);
            break;
        }
    }
}

static void executeTasks() {
    Task task = frontTask();
    if (isEmpty()) {
        return;
    }
    if (task.task_calback == NULL) {
        return;
    }
    //printf("rear task: %lu \n", a.id);
    //printf("==> Execute Task: %lu\n", task.id);
    clock_t timeFired = clock();
    task.task_calback(task.id);
    timeFired = clock() - timeFired;
    printf("=================================> task %lu time execute in: %lu\n\n", task.id, timeFired);
    deQueue();
}

static void setCurrentTimeEvent() {
    for (int i = 0; i <= _eventLastIndex; i++) {
        _events[i].beginTime = clock();
    }
}

void startLoop() {
    setCurrentTimeEvent();
    printf("******************* Start loop miliseconds *******************\n");
    _iStarting = 1;
    while (1 == _iStarting) {
        
        // create task next run
        poll();
        
        // run 1 task
        executeTasks();
        
        // clear event not use
        clear();
    }
}

void stopLoop() {
    if (_iStarting) {
        _iStarting = 0;
        printf("Start loop\n");
    }
}

int count() {
    return _eventLastIndex + 1;
}

int max() {
    return TASK_SIZE;
}

EventLoop EventLoop_init() {
    shared = malloc(sizeof(EventLoop));
    shared->add = &addEvent;
    shared->loop = &startLoop;
    shared->exit = &stopLoop;
    shared->remove = &removeEvent;
    shared->count = &count;
    shared->max = &max;
    shared->setInterval = &setInterval;
    shared->setTimeout = &setTimeout;
    shared->setImmedate = &setImmedate;
    shared->emit = &emit;
    shared->listen = &listenEvent;
    return *shared;
}

EventLoop EventShared(void) {
    if (shared != NULL) {
        return *shared;
    }
    return EventLoop_init();

}
