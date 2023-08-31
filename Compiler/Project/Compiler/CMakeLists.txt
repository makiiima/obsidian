# cmake_minimum_required(VERSION 3.13)



# project(MyCompiler)

# set(CMAKE_CXX_STANDARD 14)

# execute_process(WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/src
#                 COMMAND flex lexer.l
#                 COMMAND bison -d parser.y
#                 COMMAND  -DLLVM_DISABLE_ABI_BREAKING_CHECKS_ENFORCING=1)

# find_package(LLVM REQUIRED CONFIG)
# message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
# message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")
# message(STATUS "Using souce in: ${CMAKE_SOURCE_DIR}")
# include_directories(${LLVM_INCLUDE_DIRS})
# separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})

# add_definitions(${LLVM_DEFINITIONS})

# include_directories(${CMAKE_SOURCE_DIR}/include)
# #add_executable(mycompiler     src/AST.hpp src/AST.cpp src/main.cpp src/parser.cpp src/parser.hpp src/lexer.cpp)
# add_executable(mycompiler    src/visualization.cpp src/AST.hpp src/AST.cpp src/main.cpp src/parser.cpp src/parser.hpp src/lexer.cpp)
# #target_include_directories(mycompiler PRIVATE ${LLVM_INCLUDE_DIRS})
# #target_link_libraries(mycompiler LLVMSupport)
# #file(GLOB SOURCES ./src/*.hpp ./src/*.cpp)

# execute_process(COMMAND llvm-config-14 --libs all
# OUTPUT_VARIABLE llvm_libs)
# string(STRIP ${llvm_libs} llvm_libs)
# string(REPLACE " " ";" llvm_libs ${llvm_libs})
# target_link_libraries(${project_name} ${llvm_libs})

cmake_minimum_required(VERSION 3.13.4)

###############################################
# Set project_name as the directory name
###############################################

file(RELATIVE_PATH project_name ${CMAKE_CURRENT_LIST_DIR}/.. ${CMAKE_CURRENT_LIST_DIR})

project (${project_name})

###############################################
# Generate lexer and parser codes
###############################################

message("-- Generating lexer and parser codes")
execute_process(WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/src
				COMMAND flex lexer.l
				COMMAND bison -d parser.y)

###############################################
# Set dependencies
###############################################

# Set project compile flags.
set (CMAKE_CXX_STANDARD 14)

find_package(LLVM REQUIRED CONFIG)
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include_directories(${LLVM_INCLUDE_DIRS})

separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})

add_definitions(${LLVM_DEFINITIONS})

include_directories(${CMAKE_SOURCE_DIR}/include)

###############################################
# Set project files
###############################################

file(GLOB SOURCES ./src/*.hpp ./src/*.cpp)

add_executable(${project_name} ${SOURCES})

###############################################
# Link
###############################################
execute_process(COMMAND llvm-config-14 --libs all
					OUTPUT_VARIABLE llvm_libs)
string(STRIP ${llvm_libs} llvm_libs)
string(REPLACE " " ";" llvm_libs ${llvm_libs})
target_link_libraries(${project_name} ${llvm_libs})
