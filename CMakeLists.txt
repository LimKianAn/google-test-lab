cmake_minimum_required(VERSION 3.14)

project(
    google_test_lab

#    VERSION 0.1
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(framework)

set(TEST_NAME ${PROJECT_NAME})

file(
    GLOB_RECURSE 
    SOURCES 
    CONFIGURE_DEPENDS
    "${PROJECT_SOURCE_DIR}/tests/*.cpp"
    )

message(${PROJECT_SOURCE_DIR})

add_executable(${TEST_NAME} ${SOURCES})

#target_include_directories()
#target_compile_definitions()

target_link_libraries(
    ${TEST_NAME}

    PRIVATE
        gmock_main
)
