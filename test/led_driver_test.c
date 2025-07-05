#include <unity.h>
#include "led_driver.h"
#include "runtime_error_stub.h"

static uint16_t virtual_leds;

void setUp(void)
{
    led_driver__create(&virtual_leds);
}
void tearDown(void) {}

void test_led_driver__create(void)
{
    virtual_leds = 0xffff;
    led_driver__create(&virtual_leds);
    TEST_ASSERT_EQUAL_HEX16(0x0000, virtual_leds);
}

void test_led_driver__turn_on_led_one(void)
{
    led_driver__turn_on_led(1);
    TEST_ASSERT_EQUAL_HEX16(1, virtual_leds);
}

void test_led_driver__turn_off_led_one(void)
{
    led_driver__turn_on_led(1);
    led_driver__turn_off_led(1);
    TEST_ASSERT_EQUAL_HEX16(0, virtual_leds);
}

void test_led_driver__turn_on_multiple_leds(void)
{
    led_driver__turn_on_led(9);
    led_driver__turn_on_led(8);
    TEST_ASSERT_EQUAL_HEX16(0x180, virtual_leds);
}

void test_led_driver__turn_off_any_led(void)
{
    led_driver__turn_on_all_leds();
    led_driver__turn_off_led(8);
    TEST_ASSERT_EQUAL_HEX16(0xff7f, virtual_leds);
}

void test_led_driver__turn_on_all_leds(void)
{
    led_driver__turn_on_all_leds();
    TEST_ASSERT_EQUAL_HEX16(0xffff, virtual_leds);
}

void test_led_driver__led_memory_not_readable(void)
{
    virtual_leds = 0xffff;
    led_driver__turn_on_led(8);
    TEST_ASSERT_EQUAL_HEX16(0x80, virtual_leds);
}

void test_led_driver__turn_on_leds_upper_and_lower_bounds(void)
{
    led_driver__turn_on_led(1);
    led_driver__turn_on_led(16);
    TEST_ASSERT_EQUAL_HEX16(0x8001, virtual_leds);
}

void test_led_driver__out_of_bounds_turn_on_changes_nothing(void)
{
    led_driver__turn_on_led(-1);
    led_driver__turn_on_led(0);
    led_driver__turn_on_led(17);
    led_driver__turn_on_led(3141);
    TEST_ASSERT_EQUAL_HEX16(0, virtual_leds);
}

void test_led_driver__out_of_bounds_turn_off_changes_nothing(void)
{
    led_driver__turn_on_all_leds();
    led_driver__turn_off_led(-1);
    led_driver__turn_off_led(0);
    led_driver__turn_off_led(17);
    led_driver__turn_off_led(3141);
    TEST_ASSERT_EQUAL_HEX16(0xffff, virtual_leds);
}

void test_led_driver__out_of_bounds_produces_runtime_error()
{
    led_driver__turn_on_led(-1);
    TEST_ASSERT_EQUAL_STRING("LED Driver: out-of-bounds LED", RuntimeErrorStub_GetLastError());
    TEST_ASSERT_EQUAL(-1, RuntimeErrorStub_GetLastParameter());
}

void test_led_driver__ignore_test()
{
    TEST_IGNORE();
}

void test_led_driver__led_is_on()
{
    TEST_ASSERT_FALSE(led_driver__led_is_on(11));
    led_driver__turn_on_led(11);
    TEST_ASSERT_TRUE(led_driver__led_is_on(11));
}

void test_led_driver__out_of_bounds_leds_always_off()
{
    TEST_ASSERT_TRUE(led_driver__led_is_off(0));
    TEST_ASSERT_TRUE(led_driver__led_is_off(17));
    TEST_ASSERT_FALSE(led_driver__led_is_on(0));
    TEST_ASSERT_FALSE(led_driver__led_is_on(17));
}

void test_led_driver__led_is_off()
{
    TEST_ASSERT_TRUE(led_driver__led_is_off(12));
    led_driver__turn_on_led(12);
    TEST_ASSERT_FALSE(led_driver__led_is_off(12));
}

void test_led_driver__turn_off_multiple_leds()
{
    led_driver__turn_on_all_leds();
    led_driver__turn_off_led(9);
    led_driver__turn_off_led(8);
    TEST_ASSERT_EQUAL_HEX16((~0x180) & 0xffff, virtual_leds);
}

void test_led_driver__turn_off_all_leds()
{
    led_driver__turn_on_all_leds();
    led_driver__turn_off_all_leds();
    TEST_ASSERT_EQUAL_HEX16(0, virtual_leds);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_led_driver__create);
    RUN_TEST(test_led_driver__turn_on_led_one);
    RUN_TEST(test_led_driver__turn_off_led_one);
    RUN_TEST(test_led_driver__turn_on_multiple_leds);
    RUN_TEST(test_led_driver__turn_off_any_led);
    RUN_TEST(test_led_driver__turn_on_all_leds);
    RUN_TEST(test_led_driver__led_memory_not_readable);
    RUN_TEST(test_led_driver__turn_on_leds_upper_and_lower_bounds);
    RUN_TEST(test_led_driver__out_of_bounds_turn_on_changes_nothing);
    RUN_TEST(test_led_driver__out_of_bounds_turn_off_changes_nothing);
    RUN_TEST(test_led_driver__out_of_bounds_produces_runtime_error);
    RUN_TEST(test_led_driver__ignore_test);
    RUN_TEST(test_led_driver__led_is_on);
    RUN_TEST(test_led_driver__out_of_bounds_leds_always_off);
    RUN_TEST(test_led_driver__led_is_off);
    RUN_TEST(test_led_driver__turn_off_multiple_leds);
    RUN_TEST(test_led_driver__turn_off_all_leds);
    return UNITY_END();
}
