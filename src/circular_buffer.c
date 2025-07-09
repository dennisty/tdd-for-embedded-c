#include "circular_buffer.h"

CircularBuffer circular_buffer__create(int capacity)
{
    // TODO: Handle invalid capacity inputs
    CircularBuffer buffer = {
        .head = 0,
        .tail = 0,
        .size = 0,
        .capacity = capacity,
        .contents = calloc(capacity, sizeof(uint8_t)),
    };

    return buffer;
}

void circular_buffer__destroy(CircularBuffer *buffer)
{
    if (buffer->contents != NULL)
    {
        free(buffer->contents);
        buffer->contents = NULL;
    }
}

bool circular_buffer__is_empty(const CircularBuffer *buffer)
{
    return buffer->size == 0;
}

bool circular_buffer__is_full(const CircularBuffer *buffer)
{
    return buffer->size >= buffer->capacity;
}

int circular_buffer__put(CircularBuffer *buffer, uint8_t data)
{
    if (circular_buffer__is_full(buffer))
    {
        return -1;
    }

    buffer->contents[buffer->head] = data;

    buffer->head = ++buffer->head % buffer->capacity;
    buffer->size++;

    return 0;
}

int circular_buffer__get(CircularBuffer *buffer, uint8_t *data)
{
    if (circular_buffer__is_empty(buffer))
    {
        return -1;
    }

    *data = buffer->contents[buffer->tail];

    buffer->tail = ++buffer->tail % buffer->capacity;
    buffer->size--;

    return 0;
}