//
//  Task.c
//  TaskManager
//
//  Created by Cao Phuoc Thanh on 3/27/19.
//  Copyright © 2019 Cao Phuoc Thanh. All rights reserved.
//

#include "Task.h"

Task Task_init(long id, task_calback task_calback) {
    Task task;
    task.id = id;
    task.task_calback = task_calback;
    return task;
}

