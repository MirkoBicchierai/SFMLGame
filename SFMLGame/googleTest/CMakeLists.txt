cmake_minimum_required(VERSION 3.12)

add_subdirectory(./lib/googletest)
set(gtest_SOURCE_DIR, ./lib/googletest/)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(TEST_SOURCE_FILES runAllTests.cpp GameCharacterTest.cpp)
add_executable(GoogleTests ${TEST_SOURCE_FILES})
target_link_libraries(GoogleTests gtest gtest_main core)

set(SFML_INCLUDE_DIR "../lib/SFML/include")
set(SFML_LIBRARY_DIR "../lib/SFML/lib")
set(SFML_DIR "../lib/SFML/lib/cmake/SFML")

link_directories(SFML_LIBRARY_DIR)
include_directories(SFML_INCLUDE_DIR)

find_package(SFML 2.5.1 COMPONENTS system window graphics network audio)

if(SFML_FOUND)
    message(STATUS "SFML_INCLUDE_DIR: ${SFML_INCLUDE_DIR}")
    message(STATUS "SFML_LIBRARIES: ${SFML_LIBRARIES}")
    message(STATUS "SFML_VERSION: ${SFML_VERSION}")
endif()
target_link_libraries (GoogleTests sfml-graphics sfml-window sfml-system sfml-audio core)
