#include <stdio.h>
#include "priority_queue.h"

define_priority_queue(int);

int condition(int a, int b) {
    return a - b;
}

void show_values(priority_queue(int) pq) {
    unsigned i;
    for(i = 1; i <= pq.no_elements; ++i) {
        printf("%d ", pq.values[i]);
    }
    puts("");
}

int main() {
    priority_queue(int) pq = new_priority_queue(int, &condition);
    enqueue_priority_queue(pq, 1);
    enqueue_priority_queue(pq, 2);
    enqueue_priority_queue(pq, 3);
    enqueue_priority_queue(pq, 4);
    enqueue_priority_queue(pq, 5);
    enqueue_priority_queue(pq, 6);
    
    printf("%d", 'Z' - 'A' + 1);


    dealloc_priority_queue(pq);
    return 0;
}