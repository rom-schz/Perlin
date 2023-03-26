set(HEADER_LIST "${Perlin_SOURCE_DIR}/include/perlin.hpp")

# Make a static library
add_library(perlin SHARED perlin.cpp ${HEADER_LIST})

# We need this directory, and users of our library will need it too
target_include_directories(perlin PUBLIC ../include)

# All users of this library will need at least C++11
target_compile_features(perlin PUBLIC cxx_std_11)