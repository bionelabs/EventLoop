# EventLoop
A simple C thread pool implementation with single core

## Include:
- setTimeOut
- setImmedate
- setInterval
- emit and listen

## Use
```c++
include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "EventLoop.h"

static int addTaskO = 0;

void calbackTaskA() {
    printf("A event calback\n");
}

void calbackTaskB() {
    printf("B event calback\n");
    if (addTaskO == 0) { // add more task when all stask runing
        addTaskO = 1;
    }
    EventShared().setImmedate(calbackTaskA);
    EventShared().emit(4555, "hjgjhgjhg", "df", 2342);
}

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

int main(int argc, const char * argv[]) {
    // add Tasks
    EventShared().setImmedate(calbackTaskA);
    EventShared().setInterval(calbackTaskB, 5*1000);
    EventShared().setTimeout(calbackTaskB, 10*1000);
    EventShared().setTimeout(calbackStopProcess, 120*1000);
    EventShared().setTimeout(calbackTaskA, 2*1000);
    EventShared().setTimeout(calbackTaskB, 2*1000);
    EventShared().setInterval(calbackTaskC, 2*1000);
    
    // run loop
    EventShared().loop();

    return 0;
}

```


## Contact
- Email: caophuocthanh@gmail.com
- Site: https://onebuffer.com
- Linkedin: https://www.linkedin.com/in/caophuocthanh/
