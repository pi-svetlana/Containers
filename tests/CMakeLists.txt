
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


enable_testing()

add_executable(
        containers_test
        array_tests.cc
        vector_tests.cc
        deque_tests.cc
        queue_tests.cc
        stack_tests.cc
        # list_tests.cc
        # rb_tree_tests.cc
        # map_tests.cc
        # set_tests.cc
        # multiset_tests.cc
)
target_link_libraries(
        containers_test
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(containers_test)
target_link_libraries(containers_test containers_lib)
