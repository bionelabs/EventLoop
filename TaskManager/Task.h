//
//  Task.h
//  TaskManager
//
//  Created by Cao Phuoc Thanh on 3/27/19.
//  Copyright © 2019 Cao Phuoc Thanh. All rights reserved.
//

#ifndef Task_h
#define Task_h

#include <stdio.h>

#endif /* Task_h */

typedef void (*task_calback)(long);

typedef struct Task {
    long id;
    void (*task_calback)(long);
} Task;

Task Task_init(long, task_calback);

