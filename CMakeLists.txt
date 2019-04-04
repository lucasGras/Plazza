cmake_minimum_required(VERSION 3.10)

project(plazza CXX)

set(FLAG -Wall -Wextra -Wunused)
if(CMAKE_BUILD_TYPE MATCHES Debug)
    set(FLAG ${FLAG} -g3 -DDEBUG=1)
endif()

file(GLOB_RECURSE SRCS "Sources/*.cpp")
file(GLOB_RECURSE CLASSES "Class/*.cpp")

add_executable(plazza ${SRCS} ${CLASSES})
target_include_directories(plazza PRIVATE Headers Class)
target_link_libraries(plazza PRIVATE pthread rt)
target_compile_options(plazza PRIVATE ${FLAG})
set_target_properties(plazza PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)