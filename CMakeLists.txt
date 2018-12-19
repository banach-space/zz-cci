cmake_minimum_required(VERSION 3.4.3 FATAL_ERROR)

project(cci)

# I was getting warnings related to variadic macros and I think that it's
# related to this:
#   https://github.com/google/googletest/issues/1419
# Disabling "Wgnu-zero-variadic-macro-arguments" for now as I believe that the
# code is fine.
set(cci_COMPILER_OPTIONS_CLANG -fcolor-diagnostics -Wall -Werror -Wpedantic
  -Wno-gnu-zero-variadic-macro-arguments -std=c++17)
set(cci_COMPILER_OPTIONS_GNU -Wall -Werror -Wpedantic
  -Wno-gnu-zero-variadic-macro-arguments -std=c++17)

add_executable(cciUT
  ${CMAKE_CURRENT_SOURCE_DIR}/src/chapter_1.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/chapter_2.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/test/test-main.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/test/tests-ch1.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/test/tests-ch2.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/src/gtest-all.cc)

target_include_directories(cciUT PRIVATE SYSTEM
  ${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/
  ${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/include
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

set(executables cciUT)

target_compile_options(cciUT PRIVATE
  "$<$<CXX_COMPILER_ID:GNU>:${cci_COMPILER_OPTIONS_GNU}>"
  "$<$<CXX_COMPILER_ID:Clang>:${cci_COMPILER_OPTIONS_CLANG}>")

if(UNIX)
  target_link_libraries(cciUT PRIVATE pthread)
endif()
