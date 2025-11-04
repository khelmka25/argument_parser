# test for indexable arg parser
add_executable(test_index test_index.cc)
target_link_libraries(test_index PRIVATE
    engine
    Catch2WithMain
)

add_test(NAME IndexTest COMMAND test_index)

# test for chain arg parser
add_executable(test_chain test_chain.cc)
target_link_libraries(test_chain PRIVATE 
    engine
    Catch2WithMain
)

add_test(NAME ChainTest COMMAND test_chain)