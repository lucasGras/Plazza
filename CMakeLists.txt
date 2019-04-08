cmake_minimum_required(VERSION 3.10)

project(plazza CXX)

set(FLAG -Wall -Wextra -Wunused)
if(CMAKE_BUILD_TYPE MATCHES Debug)
    set(FLAG ${FLAG} -g3 -DDEBUG=1)
endif()

set(COMMON_HEADERS "Commons/Classes")
file(GLOB_RECURSE COMMONS "Commons/*.cpp")

file(GLOB_RECURSE SRCS_PLAZZA "Plazza/Sources/*.cpp")
file(GLOB_RECURSE CLASSES_PLAZZA "Plazza/Classes/*.cpp")

file(GLOB_RECURSE SRCS_KITCHEN "Kitchen/Sources/*.cpp")
file(GLOB_RECURSE CLASSES_KITCHEN "Kitchen/Sources/Class/*.cpp")

add_executable(plazza ${COMMONS} ${SRCS_PLAZZA} ${CLASSES_PLAZZA})
target_include_directories(plazza PRIVATE Plazza/Headers Plazza/Classes ${COMMON_HEADERS})
target_link_libraries(plazza PRIVATE pthread rt)
target_compile_options(plazza PRIVATE ${FLAG})
set_target_properties(plazza PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

add_executable(kitchen ${COMMONS} ${SRCS_KITCHEN} ${CLASSES_KITCHEN})
target_include_directories(kitchen PRIVATE Kitchen/Headers ${COMMON_HEADERS})
target_link_libraries(kitchen PRIVATE pthread rt)
target_compile_options(kitchen PRIVATE ${FLAG})
set_target_properties(kitchen PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)