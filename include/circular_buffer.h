#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct
{
    int head;
    int tail;
    int size;
    int capacity;
    uint8_t *contents;
} CircularBuffer;

CircularBuffer circular_buffer__create(int capacity);
void circular_buffer__destroy(CircularBuffer *buffer);
bool circular_buffer__is_empty(const CircularBuffer *buffer);
bool circular_buffer__is_full(const CircularBuffer *buffer);
int circular_buffer__put(CircularBuffer *buffer, uint8_t data);
int circular_buffer__get(CircularBuffer *buffer, uint8_t *data);

#endif