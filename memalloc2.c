#include <stdio.h>
#include <stdlib.h>

typedef struct Block {
    int start, size;
    struct Block *next, *prev;
} Block;

Block* head = NULL;

Block* create_block(int start, int size) {
    Block* b = malloc(sizeof(Block));
    b->start = start;
    b->size = size;
    b->next = b->prev = NULL;
    return b;
}

void add_block(int start, int size) {
    Block* b = create_block(start, size);

    if (!head) {
        head = b;
    } else {
        Block* t = head;
        while (t->next)
            t = t->next;

        t->next = b;
        b->prev = t;
    }
}

void remove_block(Block* b) {
    if (b->prev)
        b->prev->next = b->next;
    else
        head = b->next;

    if (b->next)
        b->next->prev = b->prev;

    free(b);
}

void display() {
    printf("Free Memory Blocks:\n");
    for (Block* t = head; t; t = t->next) {
        printf("Start: %d, Size: %d\n", t->start, t->size);
    }
    printf("\n");
}

void reset() {
    while (head)
        remove_block(head);
}

void allocate(Block* b, int req) {
    printf("Memory allocated at: %d\n\n", b->start);

    if (b->size == req) {
        remove_block(b);
    } else {
        b->start += req;
        b->size -= req;
    }
}

void first_fit(int req) {
    for (Block* t = head; t; t = t->next) {
        if (t->size >= req) {
            allocate(t, req);
            return;
        }
    }
    printf("Allocation failed.\n\n");
}

void best_fit(int req) {
    Block* best = NULL;

    for (Block* t = head; t; t = t->next) {
        if (t->size >= req && (!best || t->size < best->size)) {
            best = t;
        }
    }

    if (!best)
        printf("Allocation failed.\n\n");
    else
        allocate(best, req);
}

void worst_fit(int req) {
    Block* worst = NULL;

    for (Block* t = head; t; t = t->next) {
        if (t->size >= req && (!worst || t->size > worst->size)) {
            worst = t;
        }
    }

    if (!worst)
        printf("Allocation failed.\n\n");
    else
        allocate(worst, req);
}

void setup() {
    add_block(1000, 200);
    add_block(1200, 500);
    add_block(1700, 300);
    add_block(2000, 600);
}

int main() {
    printf(" FIRST FIT\n");
    setup();
    display();
    first_fit(250);
    first_fit(100);
    first_fit(500);
    first_fit(700);
    reset();

    printf("\n BEST FIT\n");
    setup();
    display();
    best_fit(250);
    best_fit(100);
    best_fit(700);
    reset();

    printf("\n WORST FIT\n");
    setup();
    display();
    worst_fit(250);
    worst_fit(100);
    worst_fit(700);

    return 0;
}
