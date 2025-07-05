runtime_error_stub_lib = library(
    'runtime_error_stub',
    'runtime_error_stub.c',
    include_directories: incdir
)

led_driver_lib = library(
    'led_driver',
    'led_driver.c',
    include_directories: incdir,
    link_with: runtime_error_stub_lib
)

circular_buffer_lib = library(
    'circular_buffer',
    'circular_buffer.c',
    include_directories: incdir
)

led_driver_dep = declare_dependency(
    link_with: led_driver_lib,
    include_directories: incdir
)

circular_buffer_dep = declare_dependency(
    link_with: circular_buffer_lib,
    include_directories: incdir
)

runtime_error_stub_dep = declare_dependency(
    link_with: runtime_error_stub_lib,
    include_directories: incdir
)