add_subdirectory (lib)

add_executable(demo demo.cpp)
target_link_libraries (demo LINK_PUBLIC libraytracing)
