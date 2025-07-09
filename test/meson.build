unity_dep = dependency('unity')

e_led_driver = executable(
    'led_driver_test_suite',
    'led_driver_test.c',
    dependencies: [unity_dep, led_driver_dep, runtime_error_stub_dep],
)

# test('LED Driver Test', e_led_driver)

e_circular_buffer = executable(
    'circular_buffer_test_suite',
    'circular_buffer_test.c',
    dependencies: [unity_dep, circular_buffer_dep],
)

test('Circular Buffer Test', e_circular_buffer)