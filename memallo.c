#include <stdio.h>
#include <stdlib.h>
typedef struct Block {
    int start_address;
    int size;
    struct Block* next;
    struct Block* prev;
} Block;

Block* head = NULL; // Global head pointer

//  COMMON BLOCKS

Block* create_block(int start, int size) {
    Block* new_block = (Block*)malloc(sizeof(Block));
    new_block->start_address = start;
    new_block->size = size;
    new_block->next = NULL;
    new_block->prev = NULL;
    return new_block;
}


void add_block(int start, int size) {
    Block* new_block = create_block(start, size);

    if (head == NULL) {
        head = new_block;
        return;
    }

    Block* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = new_block;
    new_block->prev = temp;
}


void display_free_blocks() {
    Block* temp = head;
    printf("Free Memory Blocks:\n");
    while (temp != NULL) {
        printf("Start: %d, Size: %d\n", temp->start_address, temp->size);
        temp = temp->next;
    }
    printf("\n");
}


void reset_blocks() {
    Block* temp = head;
    while (temp != NULL) {
        Block* to_free = temp;
        temp = temp->next;
        free(to_free);
    }
    head = NULL;
}

// FIRST FIT ALLOCATION 
void first_fit_allocate(int request_size) {
    Block* temp = head;

    while (temp != NULL) {
        if (temp->size >= request_size) {
            printf("Memory allocated at: %d\n", temp->start_address);

            if (temp->size == request_size) {
                if (temp->prev == NULL && temp->next == NULL) {
                    head = NULL;
                } else if (temp->prev == NULL) {
                    head = temp->next;
                    head->prev = NULL;
                } else if (temp->next == NULL) {
                    temp->prev->next = NULL;
                } else {
                    temp->prev->next = temp->next;
                    temp->next->prev = temp->prev;
                }
                free(temp);
            } else {
                temp->start_address += request_size;
                temp->size -= request_size;
            }

            printf("\n");
            return;
        }
        temp = temp->next;
    }

    printf("Allocation failed: No sufficient memory block available\n\n");
}

//  BEST FIT ALLOCATION 
void best_fit_allocate(int request_size) {
    Block* temp = head;
    Block* best_block = NULL;

    while (temp != NULL) {
        if (temp->size >= request_size) {
            if (best_block == NULL || temp->size < best_block->size) {
                best_block = temp;
            }
        }
        temp = temp->next;
    }

    if (best_block == NULL) {
        printf("Allocation failed: No sufficient memory block available\n\n");
        return;
    }

    printf("Memory allocated at: %d\n", best_block->start_address);

    if (best_block->size == request_size) {
        if (best_block->prev == NULL && best_block->next == NULL) {
            head = NULL;
        } else if (best_block->prev == NULL) {
            head = best_block->next;
            head->prev = NULL;
        } else if (best_block->next == NULL) {
            best_block->prev->next = NULL;
        } else {
            best_block->prev->next = best_block->next;
            best_block->next->prev = best_block->prev;
        }
        free(best_block);
    } else {
        best_block->start_address += request_size;
        best_block->size -= request_size;
    }

    printf("\n");
}

//  WORST FIT ALLOCATION 
void worst_fit_allocate(int request_size) {
    Block* temp = head;
    Block* worst_block = NULL;

    while (temp != NULL) {
        if (temp->size >= request_size) {
            if (worst_block == NULL || temp->size > worst_block->size) {
                worst_block = temp;
            }
        }
        temp = temp->next;
    }

    if (worst_block == NULL) {
        printf("Allocation failed: No sufficient memory block.\n\n");
        return;
    }

    printf("Memory allocated at: %d\n", worst_block->start_address);

    if (worst_block->size == request_size) {
        if (worst_block->prev == NULL && worst_block->next == NULL) {
            head = NULL;
        } else if (worst_block->prev == NULL) {
            head = worst_block->next;
            head->prev = NULL;
        } else if (worst_block->next == NULL) {
            worst_block->prev->next = NULL;
        } else {
            worst_block->prev->next = worst_block->next;
            worst_block->next->prev = worst_block->prev;
        }
        free(worst_block);
    } else {
        worst_block->start_address += request_size;
        worst_block->size -= request_size;
    }

    printf("\n");
}

int main() {
   
    printf(" FIRST FIT ALLOCATION\n");
    add_block(1000, 200);
    add_block(1200, 500);
    add_block(1700, 300);
    add_block(2000, 600);

    display_free_blocks();

    printf("Allocate Process of size 250:\n");
    first_fit_allocate(250);
    

    printf("Allocate Process of size 100:\n");
    first_fit_allocate(100);
   

    printf("Allocate Process of size 500:\n");
    first_fit_allocate(500);
   

    printf("Allocate Process of size 700:\n");
    first_fit_allocate(700);
    

    reset_blocks();  

    
    printf("\n BEST FIT ALLOCATION\n");
    add_block(1000, 200);
    add_block(1200, 500);
    add_block(1700, 300);
    add_block(2000, 600);

    display_free_blocks();

    printf("Allocate Process of size 250:\n");
    best_fit_allocate(250);
    

    printf("Allocate Process of size 100:\n");
    best_fit_allocate(100);
   

    printf("Allocate Process of size 700:\n");
    best_fit_allocate(700);
   

    reset_blocks();  


    printf("\n WORST FIT ALLOCATION\n");
    add_block(1000, 200);
    add_block(1200, 500);
    add_block(1700, 300);
    add_block(2000, 600);

    display_free_blocks();

    printf("Allocate Process of size 250:\n");
    worst_fit_allocate(250);
  

    printf("Allocate Process of size 100:\n");
    worst_fit_allocate(100);
   

    printf("Allocate Process of size 700:\n");
    worst_fit_allocate(700);

    return 0;
}
