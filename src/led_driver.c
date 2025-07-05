#include "led_driver.h"

enum
{
    ALL_LEDS_ON = ~0,
    ALL_LEDS_OFF = ~ALL_LEDS_ON
};

enum
{
    FIRST_LED = 1,
    LAST_LED = 16
};

static uint16_t *leds_address;
static uint16_t leds_image;

static uint16_t convert_led_number_to_bit(int led_number)
{
    return 1 << (led_number - 1);
}

static void update_hardware()
{
    *leds_address = leds_image;
}

static bool is_led_out_of_bounds(int led_number)
{
    return (led_number < FIRST_LED || led_number > LAST_LED);
}

static void set_led_image_bit(int led_number)
{
    leds_image |= convert_led_number_to_bit(led_number);
}

static void clear_led_image_bit(int led_number)
{
    leds_image &= ~convert_led_number_to_bit(led_number);
}

void led_driver__create(uint16_t *address)
{
    leds_address = address;
    leds_image = ALL_LEDS_OFF;
    update_hardware();
}

void led_driver__turn_on_led(int led_number)
{
    if (is_led_out_of_bounds(led_number))
    {
        RUNTIME_ERROR("LED Driver: out-of-bounds LED", led_number);
        return;
    }

    set_led_image_bit(led_number);
    update_hardware();
}

void led_driver__turn_off_led(int led_number)
{
    if (is_led_out_of_bounds(led_number))
    {
        return;
    }

    clear_led_image_bit(led_number);
    update_hardware();
}

void led_driver__turn_on_all_leds()
{
    leds_image = ALL_LEDS_ON;
    update_hardware();
}

void led_driver__turn_off_all_leds()
{
    leds_image = ALL_LEDS_OFF;
    update_hardware();
}

bool led_driver__led_is_on(int led_number)
{
    if (is_led_out_of_bounds(led_number))
    {
        return false;
    }

    return leds_image & (convert_led_number_to_bit(led_number));
}

bool led_driver__led_is_off(int led_number)
{
    return !led_driver__led_is_on(led_number);
}