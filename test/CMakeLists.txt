cmake_minimum_required(VERSION 3.20)

project(test)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_EXE_LINKER_FLAGS " -static")

if(MSVC)

    #管理员权限
    #set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /level='requireAdministrator' /uiAccess='false'")

    set(CMAKE_CXX_FLAGS_RELEASE ${CMAKE_CXX_FLAGS_RELEASE} "/MT")
    set(CMAKE_CXX_FLAGS_DEBUG ${CMAKE_CXX_FLAGS_DEBUG} "/MTd")
    
    set(COMPILE_IGNORE_WARNING
        /wd4828
    )

    add_compile_options(
        $<$<CONFIG:>:/MT>
        $<$<CONFIG:Debug>:/MTd>
        $<$<CONFIG:Release>:/MT>
        $<$<C_COMPILER_ID:MSVC>:/utf-8>
        $<$<CXX_COMPILER_ID:MSVC>:/utf-8>
        ${COMPILE_IGNORE_WARNING}
    )
endif()

#项目根目录
set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/)
set(BIN_DIR ${PROJECT_SOURCE_DIR}/bin)
set(SRC_DIR ${PROJECT_SOURCE_DIR}/)


set(CMAKE_PREFIX ${PROJECT_SOURCE_DIR})

#生成目录
set(LIBRARY_OUTPUT_PATH ${BIN_DIR})
set(EXECUTABLE_OUTPUT_PATH ${BIN_DIR})

#根路径
get_filename_component(DIR_ONE_ABOVE ../ ABSOLUTE) 
message(STATUS "DIR_ONE_ABOVE : ${DIR_ONE_ABOVE}")
include_directories(${INCLUDE_DIR})
include_directories(${DIR_ONE_ABOVE})


#exe配置
add_executable(test 
    ${SRC_DIR}/main.cpp
)

