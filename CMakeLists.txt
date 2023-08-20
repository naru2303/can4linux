
# check the version of cmake 
cmake_minimum_required(VERSION 3.5)

set (PROJECT_NAME CAN)

set (LIB_NAME CAN4LINUX)
#create project 
project(${PROJECT_NAME})

add_definitions(-DBIG_MEM_PLATFORM)
add_definitions(-DRUNNING_OS)
#thread package is needed for some apps 
find_package (Threads)

#working with c++17
#et_property(TARGET tgt PROPERTY C_STANDARD 99)
# add static lib, in this case it will be the tftp lib
add_library(
    ${LIB_NAME} STATIC
    src/ring_buffer.c
)

# include the headers 
target_include_directories(${LIB_NAME}
PUBLIC
    ${PROJECT_SOURCE_DIR}/inc
)

# generate an executable 
add_executable(main_ring_buffer
            examples/ring_buffer_ex.c)       


# link the static lib with the executable 
target_link_libraries(main_ring_buffer
        PRIVATE
        ${LIB_NAME}
        ${CMAKE_THREAD_LIBS_INIT})

