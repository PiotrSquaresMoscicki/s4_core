set(EXAMPLE_INCLUDE ${CMAKE_CURRENT_LIST_DIR})

# gather source files list
file(GLOB_RECURSE EXAMPLE_SRCS RELATIVE ${CMAKE_CURRENT_LIST_DIR}
    ${EXAMPLE_INCLUDE}/*.cpp 
    ${EXAMPLE_INCLUDE}/*.hpp 
    ${EXAMPLE_INCLUDE}/*.hpp)
GenerateSourceGoups("${EXAMPLE_SRCS}")

add_executable(${EXAMPLE_TARGET} ${EXAMPLE_SRCS})
target_compile_features(${EXAMPLE_TARGET} PUBLIC cxx_std_20)
target_include_directories(${EXAMPLE_TARGET} PUBLIC ${EXAMPLE_INCLUDE})
target_link_libraries(${EXAMPLE_TARGET} PUBLIC ${S4_CORE_TARGET})