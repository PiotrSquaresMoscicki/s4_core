cmake_minimum_required(VERSION 3.10)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

##
# Function that generates source groups from directories
##
function(GenerateSourceGoups Sources)
	foreach(Source ${Sources})
		get_filename_component(SourcePath "${Source}" PATH)
		if (WIN32)
			string(REPLACE "/" "\\" SourcePath "${SourcePath}")
		endif()
		source_group("${SourcePath}" FILES "${Source}")
	endforeach()
endfunction()

##
# Start
##
project(s4_core VERSION "1.0.0")
enable_testing()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(S4_CORE_ROOT_DIR ${CMAKE_SOURCE_DIR})
set(DIST_DIR "${S4_CORE_ROOT_DIR}/dist")
set(COMMON_BUILD_DIR "${S4_CORE_ROOT_DIR}/common_build")

if(MSVC)
add_compile_options(/W4 /WX)
else()
add_compile_options(-Wall -Wextra -Wpedantic -Werror -Wno-unused-variable)
endif()

# Output dirs
if (WIN32)
	set(FULL_DIST_DIR "${DIST_DIR}") # Config name is added autmatically on windows
else()
	set(FULL_DIST_DIR "${DIST_DIR}/${CONFIGURATION}")
	message(dupaaaa)
endif()
message(${FULL_DIST_DIR})
	
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${FULL_DIST_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${FULL_DIST_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${FULL_DIST_DIR})

configure_file(
	"${PROJECT_SOURCE_DIR}/config/CmakeConfig.hpp.in" 
	"${PROJECT_BINARY_DIR}/config/CmakeConfig.hpp"
)
include_directories("${PROJECT_BINARY_DIR}/config")

# Fetch dependencies
include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY "https://github.com/catchorg/Catch2.git"
  GIT_TAG "v3.0.0-preview3"
)

FetchContent_MakeAvailable(Catch2)
list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)

# Target names
set(S4_CORE_TARGET s4_core)
set(S4_CORE_TEST_TARGET s4_core_test)
set(S4_CORE_TEST_INTERFACE_TARGET s4_core_test_interface)
set(S4_CORE_TEST_LIB_TARGET s4_core_test_lib)
set(S4_CORE_EXAMPLE_TARGET s4_core_example)

# Subdirectories
add_subdirectory(src)
add_subdirectory(example)
add_subdirectory(test)