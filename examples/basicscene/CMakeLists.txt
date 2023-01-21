add_executable ("basicscene" "basicscene.cpp" "gl.c")
target_link_libraries ("basicscene" "glfw" "GLHelper")

configure_file ("${CMAKE_CURRENT_SOURCE_DIR}/monkey.obj" "${CMAKE_CURRENT_BINARY_DIR}" COPYONLY)
configure_file ("${CMAKE_CURRENT_SOURCE_DIR}/monkey_texture.bmp" "${CMAKE_CURRENT_BINARY_DIR}" COPYONLY)
configure_file ("${CMAKE_CURRENT_SOURCE_DIR}/vertex_shader_textured.glsl" "${CMAKE_CURRENT_BINARY_DIR}" COPYONLY)
configure_file ("${CMAKE_CURRENT_SOURCE_DIR}/frag_shader_textured.glsl" "${CMAKE_CURRENT_BINARY_DIR}" COPYONLY)