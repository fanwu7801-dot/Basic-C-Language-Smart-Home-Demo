cmake_minimum_required(VERSION 3.16)

project(SmartHomeDemo C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(SMART_HOME_SOURCES
    app/main.c
    app/smart_home.c
    BSP/bsp_console.c
    BSP/bsp_storage.c
    driver/device.c
    driver/light.c
    driver/air_conditioner.c
    driver/security_alarm.c
    middleware/basic_ui.c
)

add_executable(smart_home ${SMART_HOME_SOURCES})

target_include_directories(smart_home
    PRIVATE
        app
        BSP
        driver
        middleware
)

if(MSVC)
    target_compile_options(smart_home PRIVATE /W4)
else()
    target_compile_options(smart_home PRIVATE -Wall -Wextra -Wpedantic)
endif()
