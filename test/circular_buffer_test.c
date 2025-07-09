#include <unity.h>
#include <stdio.h>

#include "circular_buffer.h"

#define BUFFER_CAPACITY 16

static CircularBuffer buffer;
static uint8_t data;

void setUp()
{
    buffer = circular_buffer__create(BUFFER_CAPACITY);
}

void tearDown()
{
    circular_buffer__destroy(&buffer);
}

void test_circular_buffer__empty_after_create()
{
    TEST_ASSERT_TRUE(circular_buffer__is_empty(&buffer));
}

void test_circular_buffer__not_empty_after_put()
{
    circular_buffer__put(&buffer, 1);
    TEST_ASSERT_FALSE(circular_buffer__is_empty(&buffer));
}

void test_circular_buffer__empty_after_get()
{
    circular_buffer__put(&buffer, 1);
    circular_buffer__get(&buffer, &data);
    TEST_ASSERT_TRUE(circular_buffer__is_empty(&buffer));
}

void test_circular_buffer__full_after_put()
{
    for (int i = 0; i < (BUFFER_CAPACITY - 1); i++)
    {
        circular_buffer__put(&buffer, 1);
    }
    TEST_ASSERT_FALSE(circular_buffer__is_full(&buffer));
    circular_buffer__put(&buffer, 1);
    TEST_ASSERT_TRUE(circular_buffer__is_full(&buffer));
}

void test_circular_buffer__full_after_put_wrapped()
{
    circular_buffer__put(&buffer, 1);
    circular_buffer__get(&buffer, &data);

    for (int i = 0; i < BUFFER_CAPACITY; i++)
    {
        circular_buffer__put(&buffer, i);
    }
    TEST_ASSERT_TRUE(circular_buffer__is_full(&buffer));
}

void test_circular_buffer__not_full_after_get()
{
    for (int i = 0; i < BUFFER_CAPACITY; i++)
    {
        circular_buffer__put(&buffer, 1);
    }

    circular_buffer__get(&buffer, &data);
    TEST_ASSERT_FALSE(circular_buffer__is_full(&buffer));
}

void test_circular_buffer__verify_fifo_values()
{

    for (int i = 0; i < BUFFER_CAPACITY; i++)
    {
        circular_buffer__put(&buffer, i);
    }

    for (int i = 0; i < BUFFER_CAPACITY; i++)
    {
        circular_buffer__get(&buffer, &data);
        TEST_ASSERT_EQUAL_HEX8(i, data);
    }
}

void test_circular_buffer__verify_fifo_values_wrapped()
{
    for (int i = 0; i < (BUFFER_CAPACITY / 2); i++)
    {
        circular_buffer__put(&buffer, 1);
        circular_buffer__get(&buffer, &data);
    }

    for (int i = 0; i < BUFFER_CAPACITY; i++)
    {
        circular_buffer__put(&buffer, i);
    }

    for (int i = 0; i < BUFFER_CAPACITY; i++)
    {
        circular_buffer__get(&buffer, &data);
        TEST_ASSERT_EQUAL_HEX8(i, data);
    }
}

void test_circular_buffer__put_to_full_and_get_to_empty()
{
    uint8_t expected_data;

    for (int i = 0; i < BUFFER_CAPACITY; i++)
    {
        TEST_ASSERT_EQUAL_INT(0, circular_buffer__put(&buffer, i));
    }

    TEST_ASSERT_EQUAL_INT(-1, circular_buffer__put(&buffer, 11));

    for (int i = 0; i < BUFFER_CAPACITY; i++)
    {
        circular_buffer__get(&buffer, &data);
        TEST_ASSERT_EQUAL_HEX8(i, data);
    }

    expected_data = data;

    TEST_ASSERT_EQUAL_INT(-1, circular_buffer__get(&buffer, &data));
    TEST_ASSERT_EQUAL_HEX8(expected_data, data);
}

void test_circular_buffer__put_to_full_and_get_to_empty_wrapped()
{
    uint8_t expected_data;

    for (int i = 0; i < (BUFFER_CAPACITY / 2); i++)
    {
        circular_buffer__put(&buffer, 1);
        circular_buffer__get(&buffer, &data);
    }

    for (int i = 0; i < BUFFER_CAPACITY; i++)
    {
        TEST_ASSERT_EQUAL_INT(0, circular_buffer__put(&buffer, i));
    }

    TEST_ASSERT_EQUAL_INT(-1, circular_buffer__put(&buffer, 11));

    for (int i = 0; i < BUFFER_CAPACITY; i++)
    {
        circular_buffer__get(&buffer, &data);
        TEST_ASSERT_EQUAL_HEX8(i, data);
    }

    expected_data = data;

    TEST_ASSERT_EQUAL_INT(-1, circular_buffer__get(&buffer, &data));
    TEST_ASSERT_EQUAL_HEX8(expected_data, data);
}

int main()
{
    UNITY_BEGIN();

    RUN_TEST(test_circular_buffer__empty_after_create);
    RUN_TEST(test_circular_buffer__not_empty_after_put);
    RUN_TEST(test_circular_buffer__empty_after_get);
    RUN_TEST(test_circular_buffer__full_after_put);
    RUN_TEST(test_circular_buffer__not_full_after_get);
    RUN_TEST(test_circular_buffer__verify_fifo_values);
    RUN_TEST(test_circular_buffer__verify_fifo_values_wrapped);
    RUN_TEST(test_circular_buffer__put_to_full_and_get_to_empty);
    RUN_TEST(test_circular_buffer__full_after_put_wrapped);
    RUN_TEST(test_circular_buffer__put_to_full_and_get_to_empty_wrapped);

    return UNITY_END();
}