set(S4_CORE_INCLUDE ${CMAKE_CURRENT_LIST_DIR})

# gather source files list
file(GLOB_RECURSE S4_CORE_SRCS RELATIVE ${CMAKE_CURRENT_LIST_DIR}
    ${S4_CORE_INCLUDE}/*.cpp 
    ${S4_CORE_INCLUDE}/*.hpp 
    ${S4_CORE_INCLUDE}/*.hpp)
GenerateSourceGoups("${S4_CORE_SRCS}")

add_library(${S4_CORE_TARGET} STATIC ${S4_CORE_SRCS})
target_compile_features(${S4_CORE_TARGET} PUBLIC cxx_std_20)
target_include_directories(${S4_CORE_TARGET} PUBLIC ${S4_CORE_INCLUDE})