set(LIBNAME libraytracing)

add_library (${LIBNAME} Image.cpp Object.cpp Scene.cpp Camera.cpp)
target_include_directories (${LIBNAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

find_package(OpenMP)
target_link_libraries(libraytracing PRIVATE OpenMP::OpenMP_CXX)