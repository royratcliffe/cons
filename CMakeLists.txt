cmake_minimum_required(VERSION 3.25)
project(cons)

add_library(cons src/cons.c)
target_include_directories(cons PUBLIC inc)

# Coverage
#
# To enable code coverage, set the CMAKE_BUILD_TYPE to "Coverage" when
# configuring the project:
#
#  cmake -DCMAKE_BUILD_TYPE=Coverage ..
#
# Only add coverage flags if we're building in Coverage mode.
# This allows us to build in other modes (e.g., Debug, Release) without the
# overhead of coverage instrumentation.
#
# --coverage is a shorthand for -fprofile-arcs -ftest-coverage, but include
# them explicitly for clarity. Note: If you want to enable coverage in Debug
# mode as well, you can modify the condition to include Debug builds.
if(CMAKE_BUILD_TYPE STREQUAL "Debug" OR CMAKE_BUILD_TYPE STREQUAL "Coverage")
    target_compile_options(cons PRIVATE --coverage)
    target_link_options(cons PRIVATE --coverage)
endif()

include(CTest)
enable_testing()

file(GLOB TestsToRun tests/*.c)
set(TestNames)
foreach(test_to_run ${TestsToRun})
    get_filename_component(TestName ${test_to_run} NAME_WE)
    if(NOT TestName MATCHES ".+_test$")
        continue()
    endif()
    list(APPEND TestNames ${TestName})
    add_test(NAME ${TestName} COMMAND test_cons ${TestName})
endforeach()
create_test_sourcelist(Tests test_driver.c ${TestNames})

add_executable(test_cons test_driver.c ${TestsToRun})
target_link_libraries(test_cons PRIVATE cons)

# Add coverage flags to test executable if building in Debug or Coverage mode
if(CMAKE_BUILD_TYPE STREQUAL "Debug" OR CMAKE_BUILD_TYPE STREQUAL "Coverage")
    target_compile_options(test_cons PRIVATE -fprofile-arcs -ftest-coverage --coverage)
    target_link_options(test_cons PRIVATE -fprofile-arcs -ftest-coverage --coverage)
endif()

# Coverage target
# To generate a coverage report, run the following command after building the project:
# sudo apt install lcov genhtml
add_custom_target(precoverage
    COMMAND lcov --capture --directory . --output-file coverage.info
    COMMAND lcov --remove coverage.info '/usr/*' '*/test*' --output-file coverage_filtered.info
    DEPENDS test_cons
)
add_custom_target(coverage
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
    COMMAND lcov --capture --directory . --output-file coverage.info
    COMMAND lcov --remove coverage.info '/usr/*' '*/test*' --output-file coverage_filtered.info
    COMMAND genhtml coverage_filtered.info --output-directory coverage_report
    COMMAND ${CMAKE_COMMAND} -E echo "Coverage report generated in: ${CMAKE_BINARY_DIR}/coverage_report/index.html"
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running tests and generating coverage report..."
    DEPENDS test_cons
)
add_custom_target(postcoverage
    COMMAND genhtml coverage_filtered.info --output-directory coverage_report
    COMMAND ${CMAKE_COMMAND} -E echo "Coverage report generated in: ${CMAKE_BINARY_DIR}/coverage_report/index.html"
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running tests and generating coverage report..."
    DEPENDS test_cons
)
