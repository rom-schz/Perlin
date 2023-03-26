add_executable(manualTest main.cpp)

target_compile_features(manualTest PRIVATE cxx_std_17)

target_link_libraries(manualTest PRIVATE perlin)
