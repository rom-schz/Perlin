
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Tests need to be added as executables first
add_executable(
    perlin_test 
    test.cpp
)

# Should be linked to the main library
target_link_libraries(
    perlin_test PRIVATE 
    perlin 
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(perlin_test)

