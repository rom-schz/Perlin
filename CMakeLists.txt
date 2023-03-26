cmake_minimum_required(VERSION 3.16)

project(Perlin 
    VERSION 1.0
    DESCRIPTION "Perlin noise generation in any dimension"
    LANGUAGES CXX)

#################################################
# Create a library
#################################################

add_subdirectory(src)

#################################################
# Create unit tests
#################################################

add_subdirectory(test)

#################################################
# Create the manual tests
#################################################

add_subdirectory(apps)