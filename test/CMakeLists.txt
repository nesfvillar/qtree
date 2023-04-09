add_executable(qtree_test qtree_test.cpp)
target_link_libraries(qtree_test qtree)

add_test(qtree_test qtree_test)
