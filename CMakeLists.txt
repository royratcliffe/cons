cmake_minimum_required(VERSION 3.25)
project(cons)

add_library(cons src/cons.c src/cons_node.c)
target_include_directories(cons PUBLIC inc)

# Add a CTest executable for running all tests.
# This will be used to run the tests defined in the test sources.
# The test sources will be compiled into a test executable.
include(CTest)
create_test_sourcelist(test_sources
    test_runner.c
    test/cons.c
    test/node.c
    test/nested_cons.c
    test/delete.c
    test/remove.c
    test/member.c
    test/append.c
)

# Add a test executable that links against the library.
# The test executable will be built from the test sources.
add_executable(test_runner
    ${test_sources}
)
target_link_libraries(test_runner cons)

add_test(NAME cons COMMAND test_runner test/cons)
add_test(NAME node COMMAND test_runner test/node)
add_test(NAME nested_cons COMMAND test_runner test/nested_cons)
add_test(NAME delete COMMAND test_runner test/delete)
add_test(NAME remove COMMAND test_runner test/remove)
add_test(NAME member COMMAND test_runner test/member)
add_test(NAME append COMMAND test_runner test/append)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(lcov)
if(LCOV)
    # Add the necessary compiler and linker flags to enable code coverage analysis.
    # Use generator expressions so coverage is only enabled for Debug configuration,
    # which works for both single- and multi-config generators.
    foreach(target IN ITEMS cons test_runner)
        target_compile_options(${target} PRIVATE $<$<CONFIG:Debug>:--coverage>)
        target_link_options(${target} PRIVATE $<$<CONFIG:Debug>:--coverage>)
    endforeach()
endif()
include(doxy)
include(cppcheck)
