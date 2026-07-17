cmake_minimum_required(VERSION 3.16)

set(CMAKE_TOOLCHAIN_FILE "~/vcpkg/scripts/buildsystems/vcpkg.cmake")
set(VCPKG_MANIFEST_INSTALL ON CACHE BOOL "Включение автоматической установки vcpkg" FORCE)

project(weather_forecast LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

find_package(cpr CONFIG REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Widgets)

set(WEATHER_SOURCES
    src/main.cpp
    src/core/wttr_weather_provider.cpp
    src/app/weather_controller.cpp
    src/app/city_manager.cpp
    src/ui/weather_animation_widget.cpp
    src/ui/weather_widget.cpp
    src/ui/city_input_dialog.cpp
)

add_executable(weather_forecast ${WEATHER_SOURCES})

target_include_directories(weather_forecast PRIVATE src)

target_link_libraries(weather_forecast PRIVATE cpr::cpr Qt6::Widgets)
