# test for indexable arg parser
add_executable(test_index test_index.cc)
target_link_libraries(test_index PRIVATE
    ArgumentParser
    Catch2WithMain
)

add_test(NAME IndexTest COMMAND test_index)

set(COMPILER_OPTIONS
    -g
    -Wall 
    -Wextra 
    -Wshadow 
    -Wconversion 
    -Wpedantic 
    -Wfloat-equal
    -Wcast-align
    -Wunused
    -Wformat
    -Wuninitialized
    -Wduplicated-cond
    -Wlogical-op
)

target_compile_options(test_index
    PRIVATE 
    ${COMPILER_OPTIONS}
)

# test for chain arg parser
add_executable(test_chain test_chain.cc)
target_link_libraries(test_chain PRIVATE 
    ArgumentParser
    Catch2WithMain
)

add_test(NAME ChainTest COMMAND test_chain)

target_compile_options(test_chain
    PRIVATE 
    ${COMPILER_OPTIONS}
)