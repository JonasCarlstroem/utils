cmake_minimum_required(VERSION 3.23)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
	add_compile_options(/Zc:__cplusplus)
endif()

#add_library(utils INTERFACE)
CREATE_LIB(utils INTERFACE)

target_include_directories(utils INTERFACE 
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:include/utils>
)

INSTALL_LIB(utils True utils)