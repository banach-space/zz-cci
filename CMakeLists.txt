cmake_minimum_required(VERSION 3.4.3 FATAL_ERROR)

project(cci)

set(cci_COMPILER_OPTIONS_CLANG -fcolor-diagnostics -std=c++17)

add_executable(cci-chapter1-UnitTest
  ${CMAKE_CURRENT_SOURCE_DIR}/src/chapter_1.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/chapter_2.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/test/test-main.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/test/tests-ch1.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/test/tests-ch2.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/src/gtest-all.cc)

target_include_directories(cci-chapter1-UnitTest PRIVATE SYSTEM
  ${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/
  ${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/include
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

set(executables cci-chapter1-UnitTest)

target_compile_options(cci-chapter1-UnitTest PRIVATE
  "$<$<CXX_COMPILER_ID:Clang>:${cci_COMPILER_OPTIONS_CLANG}>")

if(UNIX)
  target_link_libraries(cci-chapter1-UnitTest PRIVATE pthread)
endif()
