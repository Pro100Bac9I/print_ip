cmake_minimum_required(VERSION 3.2)

add_executable(
    print_ip

    main.cpp
)

set_target_properties(
    print_ip

    PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS -Wpedantic -Wall -Wextra
)

install(TARGETS print_ip RUNTIME DESTINATION bin)