#ifndef LED_DRIVER_H
#define LED_DRIVER_H

#include <stdbool.h>
#include <stdint.h>

#include "runtime_error.h"

void led_driver__create(uint16_t *address);
void led_driver__turn_on_led(int led_number);
void led_driver__turn_off_led(int led_number);
void led_driver__turn_on_all_leds();
void led_driver__turn_off_all_leds();
bool led_driver__led_is_on(int led_number);
bool led_driver__led_is_off(int led_number);

#endif