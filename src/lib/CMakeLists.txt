set(LIBNAME libraytracing)

add_library (${LIBNAME} Image.cpp Render.cpp Vec.cpp)
target_include_directories (${LIBNAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
