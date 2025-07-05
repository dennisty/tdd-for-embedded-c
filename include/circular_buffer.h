#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include <stdint.h>

#define BUFFER_SIZE 10

typedef struct
{
    uint8_t contents[BUFFER_SIZE];
} CircularBuffer;

void circular_buffer__init(CircularBuffer *buffer);
void circular_buffer__put(CircularBuffer *buffer, uint8_t data);
void circular_buffer__get(CircularBuffer *buffer);

#endif