file(GLOB_RECURSE ARGUMENT_PARSER_SOURCE ${CMAKE_SOURCE_DIR}/src/*.cc)
add_library(ArgumentParser STATIC ${ARGUMENT_PARSER_SOURCE})
target_include_directories(ArgumentParser PUBLIC 
    ${CMAKE_SOURCE_DIR}/include
)