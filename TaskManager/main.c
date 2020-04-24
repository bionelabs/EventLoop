//
//  main.c
//  TaskManager
//
//  Created by Cao Phuoc Thanh on 3/22/19.
//  Copyright © 2019 Cao Phuoc Thanh. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "EventLoop.h"

static int addTaskO = 0;

void calbackTaskA() {
    printf("A event calback\n");
}

void calbackTaskOOOOO() {
    printf("00000 event calback\n");
}

void calbackTaskB() {
    printf("B event calback\n");
    if (addTaskO == 0) { // add more task when all stask runing
        addTaskO = 1;
        EventShared().setInterval(&calbackTaskOOOOO, 9*1000);
    }
    EventShared().setImmedate(calbackTaskA);
    EventShared().emit(4555, "hjgjhgjhg", "df", 2342);
}

long int abc = 0;

void calbackTaskC() {
    printf("C event calback\n");
    EventShared().emit(4555, "6666666666ghfjghf", "9999999999999jhgfjhgfj", "2342");
}

void calbackTaskD() {
    printf("D event calback\n");
}

void calbackStopProcess() {
    printf("calbackStopProcess\n");
    EventShared().remove(4555);
    EventShared().exit();
}

void calbackUUUUU(long i, char* va, char* vb, int *iii) {
    printf("\n\nISTENER EMIT EVENT VALUES:%lu -- %s -- %s -- %i\n\n\n", i, va, vb, *iii);
}

int main(int argc, const char * argv[]) {
    // add Tasks
    EventShared().setImmedate(calbackTaskA);
    EventShared().setInterval(calbackTaskB, 5*1000);
    EventShared().setTimeout(calbackTaskB, 10*1000);
    EventShared().setTimeout(calbackStopProcess, 120*1000);
    EventShared().setTimeout(calbackTaskA, 2*1000);
    EventShared().setTimeout(calbackTaskB, 2*1000);
    EventShared().setInterval(calbackTaskC, 2*1000);
    EventShared().listen(4555, calbackUUUUU);
    
    // run loop
    EventShared().loop();

    return 0;
}
