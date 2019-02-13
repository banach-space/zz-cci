cmake_minimum_required(VERSION 3.4.3 FATAL_ERROR)

project(cci)

set(CMAKE_CXX_STANDARD 17)

set(cci_COMPILER_OPTIONS_CLANG -fcolor-diagnostics -Wall -Werror -std=c++17)
set(cci_COMPILER_OPTIONS_GNU -Wall -fdiagnostics-color=always -Werror -std=c++17)


add_executable(cciUT
  ${CMAKE_CURRENT_SOURCE_DIR}/src/chapter_1.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/chapter_2.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/chapter_3.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/chapter_4.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/chapter_4_binary_tree.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/chapter_5.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/test/test-main.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/test/tests-ch1.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/test/tests-ch2.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/test/tests-ch3.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/test/tests-ch4.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/test/tests-ch5.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/test/tests-binary_tree.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/test/tests-List.cpp
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
