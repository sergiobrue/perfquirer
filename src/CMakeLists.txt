cmake_minimum_required (VERSION 2.8.12)
project (PERFQUIRER)

set(PIN_VERSION_MAJOR 1)
set(PIN_VERSION_MINOR 0)

add_compile_options(-std=c++17 -Werror -Wall -pedantic -O2 -fomit-frame-pointer)

add_library (perfquirer STATIC PerfQuirer.cc TAnnotTable.cc)

set_target_properties(perfquirer PROPERTIES PUBLIC_HEADER "PerfQuirer.h")

INSTALL(TARGETS perfquirer
        ARCHIVE DESTINATION lib
        PUBLIC_HEADER DESTINATION include)


